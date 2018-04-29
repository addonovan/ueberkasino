#ifndef __TITLE_WINDOW_HPP__
#define __TITLE_WINDOW_HPP__

#include <memory>
#include <UberCasino.h>
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    /**
     * The main/title screen which allows the user to start a new game,
     * open a help window, or exit the game.
     */
    class TitleWindow
    {

    public:

        /**
         * Shows the title window.
         */
        static void show();

    };

}

#endif // __TITLE_WINDOW_HPP__

