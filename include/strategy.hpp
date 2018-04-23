#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <vector>
#include <string>

#include "hand.hpp"

namespace UberCasino {

class Strategy {
public:
    enum Strat { MANUAL, CONSERV, LOOKUP, RECKLESS };
    enum Action { HIT, STAND, DOUBLE, DEFAULT };

    Strategy();

    void switchStrategy(Strat);
    Strategy::Strat getCurrentStrat();
    Strategy::Action makeMove(Hand);

    // helpers
    Strategy::Action conservativeMove(Hand);
    Strategy::Action recklessMove();
    Strategy::Action lookupMove(Hand);

private:
    Strat _currentStrat;

    const Strategy::Action lookupTable[10][10] = 
    {     /* 2       3       4       5       6       7       8       9       10      11 */
/*4-8*/{    HIT,    HIT,    HIT,    HIT,    HIT,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 9 */{    HIT, DOUBLE, DOUBLE, DOUBLE, DOUBLE,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 10*/{ DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE,    HIT,    HIT },
/* 11*/{ DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE, DOUBLE },
/* 12*/{    HIT,    HIT,  STAND,  STAND,  STAND,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 13*/{  STAND,  STAND,  STAND,  STAND,  STAND,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 14*/{  STAND,  STAND,  STAND,  STAND,  STAND,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 15*/{  STAND,  STAND,  STAND,  STAND,  STAND,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 16*/{  STAND,  STAND,  STAND,  STAND,  STAND,    HIT,    HIT,    HIT,    HIT,    HIT },
/* 17*/{  STAND,  STAND,  STAND,  STAND,  STAND,  STAND,  STAND,  STAND,  STAND,  STAND }
    };
};

} /* UberCasino */

#endif
