#ifndef __HELP_WINDOW_HPP__
#define __HELP_WINDOW_HPP__

#include <memory>
#include <vector>

#include <UberCasino.h>
#include "fltk.hpp"
#include "types.inl"

namespace uc
{

    /**
     * Displays information which the user could need if they
     * have never played blackjack before.
     */
    class HelpWindow
    {
        
    public:

        /**
         * Shows the help window to the user.
         */
        static void show();

    };

}

#endif // __HELP_WINDOW_HPP__
