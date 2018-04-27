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

    void 
    Player::join( net::Dealer dealer )
    {
        // copy the game uid from that, then we'll need to publish our
        // updated selves to the network
        m_game_uid = std::string{ dealer.game_uid, net::UUID_LENGTH };

        net::Player packet = to();
        packet.A = net::Action::idle;

        Network::get().send( packet );
    }

    void
    Player::from( net::Game state )
    {
        // copy the game uid out of the structure
        std::string game_uid{ state.game_uid, net::UUID_LENGTH };

        // if this is a message for another game, then let's ignore it
        if ( game_uid != m_game_uid )
            return;

        // try to find our player's uid in the list
        for ( auto i = 0u; i < net::MAX_PLAYERS; i++ )
        {
            // if our uid doesn't match, then we'll just this entry
            std::string player_uid{ state.p[i].uid, net::UUID_LENGTH };
            if ( player_uid != m_uid )
                continue;

            // => we found the player!
            // so we'll just copy the cards out of the player state and save
            // the game state
            memcpy( m_cards, state.p[i].cards, net::MAX_CARDS );
            m_game = state;
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
        memcpy( copy.game_uid, m_game_uid.c_str(), net::UUID_LENGTH );
        copy.balance = m_balance;

        // let the strategy determine what we should do
        copy.A = m_strategy->process( m_uid.c_str(), m_game );

        return copy;
    }

}
