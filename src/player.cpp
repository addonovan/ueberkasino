#include <stdexcept>
#include <cstdlib>
#include <iostream>

#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <player.hpp>
#include <network.hpp>
#include <misc.hpp>

namespace uc
{

    Player::Player()
      : m_uid{ 
            boost::lexical_cast< std::string >( 
                boost::uuids::random_generator()()
            )
        },
        m_name{ "Austin Donovan" },
        m_balance{ 200.0f },
        m_bet{ 0 },
        m_strategy{ nullptr },
        m_game{ nullptr }
    {
        // make sure it's the correct length for the uid
        m_uid.erase( 0, net::UUID_LENGTH );

#if defined(DEBUG_ALL) || defined(DEBUG_PLAYER)
        std::cout << "[Player]"
            << "  .name = " << m_name
            << "  .uuid = " << m_uid << std::endl;
#endif
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

        // make sure we don't go into debt (TOTALLY UNREALISTIC, LET'S BE REAL)
        if ( m_balance < diff )
        {
            diff = m_balance;
        }

        m_balance -= diff;
        m_bet += diff;
    }

    void
    Player::on_lose()
    {
        // we don't need to remove ANYTHING here, because the money has
        // already been removed
        m_bet = 0;
    }

    void
    Player::on_win()
    {
        // I'm not really sure, but I think you're supposed to be able to get
        // money back through gambling, not just lose it (?)
        m_balance += m_bet + m_bet;
        m_bet = 0;
    }

    const net::Game*
    Player::game() const
    {
        return m_game;
    }

    const net::Hand&
    Player::hand() const
    {
        return m_hand;
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
    Player::leave()
    {
        delete m_game;
        m_game = nullptr;
    }

    void
    Player::from( net::Game state )
    {
        // if we aren't in a game, then completely ignore this
        if ( m_game == nullptr )
            return;

        // we are TRUSTING that the call-site guarantees that this function
        // will only be called under the following conditions:
        // 1. `state` is a game the player is in
        // 2. `state`'s `active_player` is this player

        m_hand = to_hand( state.p[ state.active_player ].cards );
        *m_game = state;
    }

    net::Player
    Player::to() const
    {
        if ( m_strategy == nullptr )
            throw std::runtime_error{ "Cannot calculate move without a strategy set!" };

        net::Player copy;
        copy.count = value_of( m_hand ); 
        memcpy( copy.name, m_name.c_str(), net::UUID_LENGTH );
        memcpy( copy.uid, m_uid.c_str(), net::UUID_LENGTH );
        memcpy( copy.game_uid, m_game->game_uid, net::UUID_LENGTH );
        copy.balance = m_balance;

        // let the strategy determine what we should do
        copy.A = m_strategy->process( *m_game );

        return copy;
    }

}
