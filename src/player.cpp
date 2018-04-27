#include <player.hpp>
#include <stdexcept>
#include <cstdlib>
#include <network.hpp>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


namespace uc
{

    Player::Player()
        : m_uid{ boost::lexical_cast< std::string >( boost::uuids::random_generator()() ) },
          m_name{ "Austin Donovan" },
          m_balance{ 200.0f },
          m_bet{ 0 },
          m_strategy{ nullptr }
    {
        // make sure it's the correct length for the uid
        m_uid.erase( 0, net::UUID_LENGTH );
    }


    float
    Player::balance() const
    {
        return m_balance;
    }

    void
    Player::balance( float balance )
    {
        m_balance = balance;
    }

    int
    Player::bet() const
    {
        return m_bet;
    }

    void
    Player::bet( int bet )
    {
        int diff = bet - m_bet;
        m_balance -= diff;
        m_bet = bet;
    }

    const net::Game*
    Player::game() const
    {
        return m_game;
    }

    void 
    Player::join( net::Dealer dealer )
    {
        // create a new game that we'll be joining
        delete m_game;
        m_game = new net::Game;

        // copy the game uid from that, then we'll need to publish our
        // updated selves to the network
        memcpy( m_game->game_uid, dealer.game_uid, net::UUID_LENGTH );

        net::Player packet = to();
        packet.A = net::Action::idle;

        Network::get().send( packet );
    }

    void
    Player::from( net::Game state )
    {
        // if we aren't in a game, then completely ignore this
        if ( m_game == nullptr )
            return;

        // we're guaranteed to be looking at the right game, but let's just check
        if ( strncmp( state.game_uid, m_game->game_uid, net::UUID_LENGTH ) )
            throw new runtime_error{ "Game UID does not match expected UID!" };

        // try to find our player's uid in the list
        for ( auto i = 0u; i < net::MAX_PLAYERS; i++ )
        {
            // if our uid doesn't match, then we'll just this entry
            std::string player_uid{ state.p[ i ].uid, net::UUID_LENGTH };
            if ( player_uid != m_uid )
                continue;

            // => we found the player!
            // so we'll just copy the cards out of the player state and save
            // the game state
            memcpy( m_cards, state.p[i].cards, net::MAX_CARDS );
            *m_game = state;
            return;
        }

        // => we looked in the right game, but we couldn't find ourselves
        // that's REALLY bad!
        // throw std::runtime_error{ "failed to find ourselves in the correct game :(" };
    }

    net::Player
    Player::to() const
    {
        if ( m_strategy == nullptr )
            throw std::runtime_error{ "Cannot calculate move without a strategy set!" };

        net::Player copy;
        copy.count = 0; // TODO figure out what this actually means
        memcpy( copy.name, m_name.c_str(), net::UUID_LENGTH );
        memcpy( copy.uid, m_uid.c_str(), net::UUID_LENGTH );
        memcpy( copy.game_uid, m_game->game_uid, net::UUID_LENGTH );
        copy.balance = m_balance;

        // let the strategy determine what we should do
        copy.A = m_strategy->process( m_uid.c_str(), *m_game );

        return copy;
    }

    bool 
    Player::operator == ( const net::PlayerState& other ) const
    {
        return strncmp( other.uid, m_uid.c_str(), net::UUID_LENGTH ) == 0;
    }

}
