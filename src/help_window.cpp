#include <help_window.hpp>

const char* text =
#include "../res/help.txt"
;

const char* style =
#include "../res/help.style"
;

namespace uc
{

    HelpWindow::HelpWindow()
    {
		m_window.begin();

        m_box->box( FL_NO_BOX );
        m_box->labelfont( FL_BOLD + FL_HELVETICA );
        m_box->labelsize( 20 );

        m_tutorial.style_table( m_style_table )
			.text( text )
			.style( style );

		m_window.end();
		m_window.show();

		Fl::run();
    }

}

