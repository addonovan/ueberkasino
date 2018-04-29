#include <help_window.hpp>

const char* text =
#include "../res/help.txt"
;

const char* style =
#include "../res/help.style"
;

namespace uc
{

    void
    HelpWindow::show()
    {
        //
        // Create components
        //

        fltk::Window window{ 30, 30, 800, 600, "How To" }; 
        fltk::Box* box = new fltk::Box{ 300, 10, 200, 50, "How to Play" };
        fltk::Label tutorial{ 20, 60, 760, 520 };

        std::vector< fltk::StyleEntry > style_table = {
            { FL_BOLD,      FL_HELVETICA, 18, 0u },
            { FL_ITALIC,    FL_HELVETICA, 18, 0u },
            { FL_BLACK,     FL_HELVETICA, 18, 0u }, 
        };

        //
        // Lay out window
        //

		window.begin();

        box->box( FL_NO_BOX );
        box->labelfont( FL_BOLD + FL_HELVETICA );
        box->labelsize( 20 );

        tutorial.style_table( style_table )
			.text( text )
			.style( style );

        //
        // Show the window
        //

		window.end();
		window.show();

		Fl::run();
    }

}

