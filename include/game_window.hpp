#ifndef __GAME_WINDOW_H__
#define __GAME_WINDOW_H__

#include <UberCasino.h>

#include "player.hpp"
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

        Player m_player;

        net::Player* m_partial_response = nullptr;

        fltk::Window m_window{ 30, 30, 800, 600, "Black Jack" };

        std::unique_ptr< fltk::Box > m_box{ 
            new fltk::Box{ 250, 5, 300, 100, "Black Jack!" }
        };

        fltk::Button m_btn_hit{     600, 470, 60, 60, "HIT" };
        fltk::Button m_btn_stand{   650, 420, 60, 60, "STAND" };
        fltk::Button m_btn_double{  700, 470, 60, 60, "DBL\nDOWN" };

        fltk::RadioButton m_btn_manual{         625, 150, 20, 20, "Manual" };
        fltk::RadioButton m_btn_conservative{   625, 175, 20, 20, "Conservative" };
        fltk::RadioButton m_btn_reckless{       625, 200, 20, 20, "Reckless" };
        fltk::RadioButton m_btn_basic{          625, 225, 20, 20, "Traditional" };

        fltk::Label m_balance{  600, 300, 160, 50, std::to_string( m_player.balance() ) };
        fltk::Label m_bet{      315, 255, 160, 50, std::to_string( m_player.bet() ) };

        fltk::Button m_btn_bet_1{       295, 315, 45, 30, "$1" };
        fltk::Button m_btn_bet_5{       345, 315, 45, 30, "$5" };
        fltk::Button m_btn_bet_10{      395, 315, 45, 30, "$10" };
        fltk::Button m_btn_bet_50{      445, 315, 45, 30, "$50" };
        fltk::Button m_btn_bet_clear{   345, 355, 90, 45, "CLEAR BET" };

        fltk::Label m_dealer_display{ 315, 133, 175, 65 };
        fltk::Label m_player_display{ 315, 453, 175, 65 };
        std::vector< fltk::Label > m_player_displays;

        std::vector< fltk::StyleEntry > m_style_table = {
            { FL_BOLD,      FL_HELVETICA, 18, 0u },
            { FL_ITALIC,    FL_HELVETICA, 18, 0u },
            { FL_BLACK,     FL_HELVETICA, 18, 0u }, 
            { FL_BLACK,     FL_HELVETICA, 34, 0u },
            { FL_BLACK,     FL_HELVETICA, 12, 0u },
        };

        //
        // Con- / De- Structors
        //

    public:

        GameWindow();

        ~GameWindow();

        //
        // UI Actions
        //

    private:

        void change_bet( int delta );

        void send_action( net::Action action );

        void on_game_update( net::Game game );

        void on_dealer_update( net::Dealer dealer );

    };

}

#endif // __GAME_WINDOW_H__
