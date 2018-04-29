#include <title_window.hpp>
#include <game_window.hpp>
#include <help_window.hpp>
#include <game.hpp>

namespace uc
{

    void
    TitleWindow::show()
    {
        //
        // Initialize all Components 
        //

        fltk::Window window{ 30, 30, 800, 600, "Über Kasino" };
        
        fltk::Box* box = new fltk::Box{ 250, 60, 300, 100, "Über Kasino!" };

        fltk::Button btn_howto{ 125, 300, 100, 100, "How To" };
        fltk::Button btn_play{ 350, 300, 100, 100, "Play" }; 
        fltk::Button btn_exit{ 575, 300, 100, 100, "Exit" };

        //
        // Lay out window
        //

        window.begin();
        window.color( 0x00500000 );

        box->box( FL_NO_BOX );
        box->labelfont( FL_BOLD + FL_ITALIC + FL_HELVETICA );
        box->labelsize( 90 );
        box->labeltype( FL_SHADOW_LABEL );

        btn_howto.box( FL_DIAMOND_UP_BOX )
            .background( FL_BLACK )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                HelpWindow::show();
            } );

        btn_play.box( FL_DIAMOND_UP_BOX )
            .background( FL_DARK_RED )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                Game game;
                GameWindow::show( game );
            } );

        btn_exit.box( FL_DIAMOND_UP_BOX )
            .background( FL_BLACK )
            .foreground( FL_LIGHT1 )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                exit( 0 );
            } );

        //
        // Show the window
        //

        window.end();
        window.show();
        Fl::run();
    }

}

