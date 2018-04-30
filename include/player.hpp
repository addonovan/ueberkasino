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

    /**
     * A player object in the game.
     *
     * This can be deserialized from a `net::Game` structure, and reserialized
     * into a `net::Player` structure.
     */
    class Player : public Serializeable< net::Game, net::Player >
    {
        //
        // Members
        //

    private:

        /** This player's unique identifier */
        std::string m_uid;

        /** The name of this player, a constant as "Austin Donovan" */
        std::string m_name;

        /** The player's current balance */
        float m_balance;

        /** The player's current bet */
        int m_bet;

        /** A managed pointer to the current strategy the player is employing */
        std::unique_ptr< Strategy > m_strategy;

        /** This player's current hand */
        net::Hand m_hand;

        /** A copy of the last game we deserialized from. */
        net::Game* m_game;

        //
        // Constructor
        //

    public:

        /**
         * Constructs a new player with `200` as a balance and `0` as a bet.
         */
        Player();

        //
        // Interface Actions
        //

    public:

        /**
         * Changes this player's `strategy`.
         *
         * This should be an unmanaged pointer, as this will be wrapped in
         * a `unique_ptr`.
         */
        template< class T >
        void strategy( T* strategy )
        {
            m_strategy = std::unique_ptr< Strategy >{ strategy };
        }

        /**
         * Gets the current `balance` of the player.
         */
        float balance() const;

        /**
         * Sets the player's `balance`.
         */
        void balance( float balance );

        /**
         * Gets the current `bet` of the player.
         */
        int bet() const;

        /**
         * Sets the player's `bet`.
         */
        void bet( int bet );

        /**
         * Updates the balance of the player to reflect losing :( 
         */
        void on_lose();

        /**
         * Updates the balance of the player to reflect victory!
         */
        void on_win();

        /**
         * A possibly null constant pointer to the current game.
         *
         * This is managed by this class, so DO NOT delete this.
         */
        const net::Game* game() const;

        /**
         * Accesses the current hand of the player.
         */
        const net::Hand& hand() const;

        //
        // Network Interface
        //

    public:

        /**
         * Joins a `dealer`'s table.
         */
        void join( net::Dealer dealer );

        /**
         * Leave's the current table, if the player is even seated at one.
         */
        void leave();

        //
        // Serialize Implementation
        //   

    public:

        /**
         * Deserializes a player from the given game `state`, under the
         * assumption that the game corresponds to one where the player
         * *is* seated.
         */
        void from( net::Game state ) override;

        /**
         * Converts this player to a network packet, after using the
         * current strategy to determine what action should be taken.
         */
        net::Player to() const override;

        //
        // Operators
        //

    public:

        /**
         * Checks if `this` player and the `other` player-like object (i.e.
         * a net::Player or net::PlayerState) have the same UID.
         */
        template< typename T >
        bool operator == ( const T& other ) const
        {
            return strncmp( other.uid, m_uid.c_str(), net::UUID_LENGTH ) == 0;
        }


    };
}

#endif // __PLAYER_HPP__
