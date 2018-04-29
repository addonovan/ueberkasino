#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <UberCasino.h>

#include "player.hpp"
#include "game.hpp"
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    /**
     * A window which displays the current state of the game and allows the
     * user to interact with it.
     */
    class GameWindow
    {
        //
        // Members
        //

    private:

        /** The game state machine being used to process this game. */
        Game& m_game;

        //
        // Static 
        //

    public:

        /**
         * Shows the game window which will display the given `game` and allow
         * the user to interact with the application.
         */
        static void show( Game& game );

        //
        // Constructor
        //

    private:

        /**
         * Constructs a game window which will allow the user to interace with
         * the `game`.
         */
        GameWindow( Game& game );

        //
        // UI Actions
        //

    private:

        /**
         * Changes the player's bet by the given `delta`, and updates the
         * `bet` and `balance` labels on the UI.
         */
        void change_bet( int delta, fltk::Label* bet, fltk::Label* balance );

        /**
         * Sends the `action` the user click on across the network, but only
         * if the current strategy is set to manual.
         */
        void send_action( net::Action action );

        /**
         * Updates the state of the game and UI when a `game` OSPL event occurs.
         */
        void on_game_update( net::Game game );

        /**
         * Updates the state of the game and UI when a `dealer` event occurs.
         */
        void on_dealer_update( net::Dealer dealer );

    };

}

#endif // __GAME_WINDOW_H__
