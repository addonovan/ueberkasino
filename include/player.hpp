#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include <string>
#include <memory>
#include <iostream>

#include <UberCasino.h>

#include "strategy.hpp"
#include "serialize.hpp"
#include "types.inl"

namespace uc
{
    class Player : public Serializeable<net::Game, net::Player>
    {
        //
        // Members
        //

    private:

        std::string m_uid;

        std::string m_name;

        float m_balance;

        int m_bet;

        std::unique_ptr< Strategy > m_strategy;

        net::Card m_cards[ net::MAX_CARDS ];

        /** A copy of the last game we deserialized from. */
        net::Game* m_game;

        //
        // Con- & De- structors
        //

    public:

        Player();

        //
        // Interface Actions
        //

    public:

        template< class T >
        void strategy( T* strategy )
        {
            m_strategy = std::unique_ptr< Strategy >{ strategy };
        }

        float balance() const;

        void balance( float balance );

        int bet() const;

        void bet( int bet );

        const net::Game* game() const;

        //
        // Network Interfact
        //

    public:

        void join( net::Dealer dealer );

        void leave();

        //
        // Serialize Implementation
        //   

    public:

        void from( net::Game state ) override;

        net::Player to() const override;

        //
        // Operators
        //

    public:

        bool operator == ( const net::PlayerState& other ) const;


    };
}

#endif // __PLAYER_HPP__
