#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <UberCasino.h>

#include "player.hpp"
#include "game.hpp"
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    class GameWindow
    {
        //
        // Members
        //

    private:

        Game& m_game;

        //
        // Con- / De- Structors
        //

    public:

        static void show( Game& game );

    private:

        GameWindow( Game& game );

        //
        // UI Actions
        //

    private:

        void change_bet( int delta, fltk::Label* bet, fltk::Label* balance );

        void send_action( net::Action action );

        void on_game_update( net::Game game );

        void on_dealer_update( net::Dealer dealer );

    };

}

#endif // __GAME_WINDOW_H__
