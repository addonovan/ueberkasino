#ifndef __TITLE_WINDOW_HPP__
#define __TITLE_WINDOW_HPP__

#include <memory>
#include <UberCasino.h>
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    class TitleWindow
    {

        //
        // Members
        //
    
    private:
        fltk::Window m_window{ 30, 30, 800, 600, "Über Kasino" };
        
        std::unique_ptr< fltk::Box > m_box{ 
            new fltk::Box{ 250, 60, 300, 100, "Über Kasino!" }
        };

        fltk::Button m_btn_howto{ 125, 300, 100, 100, "How To" };
        fltk::Button m_btn_play{ 350, 300, 100, 100, "Play" }; 
        fltk::Button m_btn_exit{ 575, 300, 100, 100, "Exit" };

    public:

        TitleWindow();

    };

}

#endif // __TITLE_WINDOW_HPP__

