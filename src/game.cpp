#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <thread>

#include <game.hpp>
#include <network.hpp>
#include <misc.hpp>

namespace uc
{

    // This is honestly absurd
    typedef std::lock_guard< std::mutex > LockGuard;

    std::map< GameState, std::string > STATE_NAMES = {
        { GameState::SearchingForGame,  "Searching for Game" },
        { GameState::JoiningGame,       "Joining Game" },
        { GameState::WaitingForStart,   "Waiting for Start" },
        { GameState::WaitingForTurn,    "Waiting for Turn" },
        { GameState::Playing,           "Playing" },
        { GameState::Standing,          "Standing" },
        { GameState::HandOver,          "Hand Over" },
    };

    std::map< net::GameState, std::string > NET_STATE_NAMES = {
        { net::GameState::waiting_to_join, "Waiting to join" },
        { net::GameState::waiting,         "Waiting" },
        { net::GameState::playing,         "Playing" },
        { net::GameState::end_hand,        "End Hand" },
    };

    Game::Game()
      : m_state{ GameState::SearchingForGame }
    {
    }

    void
    Game::delay_timeout()
    {
        using namespace std::chrono;

        // update the last delay time
        m_last_response_mtx.lock();
        
        m_last_response = steady_clock::now();
        TimePoint last_response = m_last_response;

        m_last_response_mtx.unlock();

        // make another thread!
        new std::thread{
            [ this, last_response ]() {

                std::this_thread::sleep_for( seconds{ 10 } );

                LockGuard lock{ m_last_response_mtx };

                // if the response times are the same then we haven't
                // been delayed, so we'll timeout the game
                if ( last_response == this->m_last_response )
                {
                    this->on_timeout();
                }
            }
        };
    }

    void
    Game::record_hands( const net::Game& game )
    {
        // record the dealer's cards into element -1
        m_hands[ -1 ] = to_hand( game.dealer_cards );

        auto index = game.active_player;   

        // if we're the active player, then we'll update the player's hand
        if ( index == m_player_index )
        {
            LockGuard lock{ m_player_mtx };
            m_player.from( game );
            return;
        }
        // if it's a player after us, then we have to shift down one position
        else if ( index > m_player_index )
        {
            index--;
        }

        m_hands[ index ] = to_hand( game.p[ game.active_player ].cards );
    }

    const Player&
    Game::player() const
    {
        // because this is a const function, this can't lock the mutex, so
        // lets just hope that it works out
        return m_player;
    }

    const std::map< long int, net::Hand >&
    Game::hands() const
    {
        return m_hands;
    }

    bool
    Game::in_game() const
    {
        switch ( m_state )
        {
            case GameState::WaitingForStart:
            case GameState::WaitingForTurn:
            case GameState::Playing:
            case GameState::Standing:
            case GameState::HandOver:
                return true;

            default:
                return false;
        }
    }

    bool
    Game::cards_dealt() const
    {
        return m_player.game() != nullptr;
    }

    void 
    Game::on_bet_changed( int difference )
    {
        LockGuard lock{ m_player_mtx };
        m_player.bet( m_player.bet() + difference );
    }

    void
    Game::on_action_picked( net::Action action )
    {
        LockGuard lock{ m_partial_response_mtx };

        // if there's no response, then the player isn't actually supposed
        // to be doing this, so we'll just ignore it entirely
        if ( m_partial_response == nullptr )
            return;

        // send the full response over the network with the given action
        m_partial_response->A = action;
        Network::get().send( *m_partial_response );

        // delete this response after we've finished that
        delete m_partial_response;
        m_partial_response = nullptr;

        // if we chose to stand, then we'll transition to that sink state, but
        // otherwise we'll just go back to waiting for our turn
        if ( action == net::Action::standing )
        {
            transition( GameState::Standing );
        }
        else
        {
            transition( GameState::WaitingForTurn );
        }

        // We sent a packet over the network, so that should prevent the
        // timeout for just a little bit longer
        delay_timeout();
    }

    void
    Game::on_dealer_update( net::Dealer dealer )
    {
#ifdef DEBUG
        std::cout << "[D] State = " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ]
            << " || Name = " << std::string{ dealer.name, 32 }
            << std::endl;
#endif

        LockGuard lock{ m_player_mtx };
        switch ( m_state )
        {
            // if we're looking for a game, we'll just try to join it
            case GameState::SearchingForGame:

                // tell the player that they should try to join the game that
                // the dealer has going on
                m_player.join( dealer );

                // we've transitioned to joining the game
                transition( GameState::JoiningGame );

                // reset any previous state from any previous game
                m_player_index = -1;
                m_hands.clear();

                delete m_partial_response;
                m_partial_response = nullptr;

                break;

            // otherwise, don't do anything
            default:
                break;
        }
    }

    void
    Game::on_game_update( net::Game game )
    {
        // First, let's make sure that this is the correct game
        // because we don't want to respond to games with differnt UUIDs
        auto* current_game = m_player.game();
        if ( current_game == nullptr )
            return;

        auto* old_uid = current_game->game_uid;
        auto* new_uid = game.game_uid;

        // if the game UIDs don't match, then we'll just ignore the
        // packet entirely
        if ( strncmp( old_uid, new_uid, net::UUID_LENGTH ) != 0 )
            return;

        // we've received one of our events, so let's time let this time out!
        delay_timeout();

        // From here on out is the actual state machine

#ifdef DEBUG
        std::cout << "[G] State = " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ]
            << " || NetState = " << NET_STATE_NAMES[ game.gstate ] 
            << std::endl;
#endif

        // if we're trying to join a game and it's the same game we were
        // trying to join earlier, and we found ourselves in it, then we'll
        // transition to the state where we're waiting for our turn
        if ( m_state == GameState::JoiningGame )
        {
            on_join_game( game );
        }

        // If we're waiting for the game to start, we'll just trap here
        // until we get a game whose state is "playing"
        if ( m_state == GameState::WaitingForStart )
        {
            on_waiting_for_start( game );
        }

        // If we're waiting for a turn, then we need to update our count
        // of cards and such of other players
        if ( m_state == GameState::WaitingForTurn )
        {
            on_waiting_for_turn( game );
        }

        // If we're playing the game, then we'll let the player sort out
        // what the need to do by using strategies and such, or whatever.
        // It's not my problem anymore, I wrote the abstraction for a 
        // reason.
        if ( m_state == GameState::Playing )
        {
            on_playing( game );
        }

        // If playing resulted in our busting, then we'll just go into
        // this sink state until the game ends
        if ( m_state == GameState::Standing )
        {
            on_standing( game );
        }

        // When the game is over, then we should leave and revert back to
        // trying to join the next game we find
        if ( m_state == GameState::HandOver )
        {
            on_hand_over();
        }
    }

    void
    Game::on_join_game( net::Game game )
    {
        LockGuard lock{ m_player_mtx };

        for ( auto i = 0u; i < net::MAX_PLAYERS; i++ )
        {
            // if we find ourselves in the game, then that means that
            // we were accepted into the game!
            if ( m_player == game.p[ i ] )
            {
                // save the player index of ourselves so we can skip this
                // index when saving player states later
                m_player_index = i;

                // we transition to the next state, and halt acceptingly
                transition( GameState::WaitingForStart );
                return;
            }
        }

        // => we couldn't find our player's uid in the game, so that
        // means the dealer didn't accept us :(
        transition( GameState::SearchingForGame );
    }

    void
    Game::on_waiting_for_start( net::Game game )
    {
        if ( game.gstate == net::GameState::playing )
        {
            transition( GameState::WaitingForTurn );
        }
    }

    void
    Game::on_waiting_for_turn( net::Game game )
    {
        record_hands( game );

        if ( game.gstate == net::GameState::end_hand )
        {
            transition( GameState::HandOver );
            return;
        }

        // if we're the current player, then we'll transition into 
        // the playing state
        if ( m_player_index == game.active_player )
        {
            transition( GameState::Playing );
        }
    }

    void
    Game::on_playing( net::Game game )
    {
        record_hands( game );

        if ( game.gstate == net::GameState::end_hand )
        {
            // calculate the score of our hand vs the dealer's
            auto dealer = value_of( to_hand( game.dealer_cards ) );
            auto player = value_of( m_player.hand() );

            // we busted :(
            if ( player > 21 )
            {
                transition( GameState::Standing );
            }
            // we beat the dealer!
            else if ( player >= dealer )
            {
                m_player.on_win();
                transition( GameState::HandOver );
            }
            // we lost :(
            else
            {
                m_player.on_lose();
                transition( GameState::HandOver );
            }
            return;
        }

        // if it's our turn, but we busted, then we'll stop early
        // and just transition to the busted state
        if ( value_of( m_player.hand() ) > 21 )
        {
            m_player.on_lose();
            transition( GameState::Standing );
            return;
        } 
        // If we got a black jack, then we'll instantly win and start standing
        else if ( value_of( m_player.hand() ) == 21 )
        {
            m_player.on_win();
            transition( GameState::Standing );
            return;
        }

        {
            LockGuard lock{ m_partial_response_mtx };
            delete m_partial_response;
        }

        net::Player response;
        {
            LockGuard lock{ m_player_mtx };
            response = m_player.to();
        }

        // if there's an action here, then we'll send it across the network
        if ( response.A != net::Action::idle )
        {
            Network::get().send( response );

            // if we chose to stand, then we'll move to that sink state
            if ( response.A == net::Action::standing )
            {
                transition( GameState::Standing );
            }
            else
            {
                transition( GameState::WaitingForTurn );
            }
        }
        else
        {
            m_partial_response = new net::Player;
            memcpy( m_partial_response, &response, sizeof( response ) );
        }
    }

    void
    Game::on_standing( net::Game game )
    {
        record_hands( game );

        if ( game.gstate == net::GameState::end_hand )
        {
            transition( GameState::HandOver );
            return;
        }

        LockGuard lock{ m_player_mtx };

        // if it's our turn, then we'll just repsond with "standing"
        if ( m_player == game.p[ game.active_player ] )
        {
            auto response = m_player.to();
            response.A = net::Action::idle;
            Network::get().send( response );
        }
    }

    void
    Game::on_hand_over()
    {
        transition( GameState::SearchingForGame );
        {
            LockGuard lock{ m_player_mtx };
            m_player.leave();
        }
       
        { 
            LockGuard lock{ m_partial_response_mtx };
            delete m_partial_response;
            m_partial_response = nullptr;
        }
    }

    void
    Game::transition( GameState state )
    {
        LockGuard lock{ m_state_mtx };

#ifdef DEBUG
        std::cout << "TRANSITION  " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ] 
            << " => "
            << STATE_NAMES[ state ] << std::endl;
#endif

        m_state = state;
    }

    void
    Game::on_timeout()
    {
#ifdef DEBUG
        std::cout << "TIMEOUT" << std::endl;
#endif

        transition( GameState::HandOver );
        on_hand_over();
    }

}
