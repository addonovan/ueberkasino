#include <string>
#include <map>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <iomanip>

#include <game.hpp>
#include <network.hpp>

namespace uc
{

    std::map< GameState, std::string > STATE_NAMES = {
        { GameState::SearchingForGame, "Searching for Game" },
        { GameState::JoiningGame,      "Joining Game" },
        { GameState::WaitingForStart,  "Waiting for Start" },
        { GameState::WaitingForTurn,   "Waiting for Turn" },
        { GameState::Playing,          "Playing" },
        { GameState::HandOver,         "Hand Over" },
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

    const Player&
    Game::player() const
    {
        return m_player;
    }

    void 
    Game::on_bet_changed( int difference )
    {
        m_player.bet( m_player.bet() + difference );
    }

    void
    Game::on_action_picked( net::Action action )
    {
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
    }

    void
    Game::on_dealer_update( net::Dealer dealer )
    {
        std::cout << "[D] State = " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ]
            << " || Name = " << std::string{ dealer.name, 32 }
            << std::endl;

        switch ( m_state )
        {
            // if we're looking for a game, we'll just try to join it
            case GameState::SearchingForGame:

                // tell the player that they should try to join the game that
                // the dealer has going on
                m_player.join( dealer );

                // we've transitioned to joining the game
                transition( GameState::JoiningGame );
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

        // From here on out is the actual state machine

        std::cout << "[G] State = " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ]
            << " || NetState = " << NET_STATE_NAMES[ game.gstate ] 
            << std::endl;

        switch ( m_state )
        {
            // if we're trying to join a game and it's the same game we were
            // trying to join earlier, and we found ourselves in it, then we'll
            // transition to the state where we're waiting for our turn
            case GameState::JoiningGame:

                // if we were able to join the game, then we'll call ourselves
                // again so that the game will actually be processed, if need
                // be
                if ( check_join_game( game ) )
                {
                    transition( GameState::WaitingForStart );
                    on_game_update( game );
                }
                else
                {
                    transition( GameState::SearchingForGame );
                }

                break;

            // If we're waiting for the game to start, we'll just trap here
            // until we get a game whose state is "playing"
            case GameState::WaitingForStart:
                if ( game.gstate == net::GameState::playing )
                {
                    transition( GameState::WaitingForTurn );
                    on_game_update( game );
                }
                break;

            // If we're waiting for a turn, then we need to update our count
            // of cards and such of other players
            case GameState::WaitingForTurn:
                break;

            // If we're playing the game, then we'll let the player sort out
            // what the need to do by using strategies and such, or whatever.
            // It's not my problem anymore, I wrote the abstraction for a 
            // reason.
            case GameState::Playing:
                break;

            // When the game is over, then we should leave and revert back to
            // trying to join the next game we find
            case GameState::HandOver:
                transition( GameState::SearchingForGame );
                break;

            // Just ignore it if we're in a different state, we probably
            // didn't want to see it anyways
            default:
                break;
        }
    }

    bool
    Game::check_join_game( net::Game game )
    {
        for ( auto i = 0u; i < net::MAX_PLAYERS; i++ )
        {
            // if we find ourselves in the game, then that means that
            // we were accepted into the game!
            if ( m_player == game.p[ i ] )
            {
                // we transition to the next state, and halt acceptingly
                return true;
            }
        }

        // => we couldn't find our player's uid in the game, so that
        // means the dealer didn't accept us :(
        return false;
    }

    void
    Game::transition( GameState tag )
    {
        std::cout << "TRANSITION  " 
            << std::setw( 20 ) << STATE_NAMES[ m_state ] 
            << " => "
            << STATE_NAMES[ tag ] << std::endl;

        m_state = tag;
    }


}

