#ifndef __HELP_WINDOW_HPP__
#define __HELP_WINDOW_HPP__

#include <memory>
#include <vector>

#include <UberCasino.h>
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    class HelpWindow
    {
        
    private:
        fltk::Window m_window{ 30, 30, 800, 600, "How To" }; 

        std::unique_ptr< fltk::Box > m_box{ 
			new fltk::Box{ 300, 10, 200, 50, "How to Play" }
		};

        fltk::Label m_tutorial{ 20, 60, 760, 520 };

        std::vector< fltk::StyleEntry > m_style_table = {
            { FL_BOLD,      FL_HELVETICA, 18, 0u },
            { FL_ITALIC,    FL_HELVETICA, 18, 0u },
            { FL_BLACK,     FL_HELVETICA, 18, 0u }, 
        };

    public:

        HelpWindow();

    };

}

#endif // __HELP_WINDOW_HPP__
