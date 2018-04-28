#include <title_window.hpp>
#include <game_window.hpp>
#include <help_window.hpp>
#include <game.hpp>

namespace uc
{

    TitleWindow::TitleWindow()
    {
        m_window.begin();
        m_window.color( 0x00500000 );

        m_box->box( FL_NO_BOX );
        m_box->labelfont( FL_BOLD + FL_ITALIC + FL_HELVETICA );
        m_box->labelsize( 90 );
        m_box->labeltype( FL_SHADOW_LABEL );

        m_btn_howto.box( FL_DIAMOND_UP_BOX )
            .background( FL_BLACK )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
		HelpWindow help;
            } );

        m_btn_play.box( FL_DIAMOND_UP_BOX )
            .background( FL_DARK_RED )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                Game game;
                GameWindow game_win{ game };
            } );

        m_btn_exit.box( FL_DIAMOND_UP_BOX )
            .background( FL_BLACK )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                exit( 0 );
            } );

        m_window.end();
        m_window.show();
        Fl::run();
    }

}

