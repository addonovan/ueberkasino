#include "strategy.hpp"
#include "hand.hpp"

#include <vector>
#include <stdexcept>

namespace UberCasino {

Strategy::Strategy()
{
    _currentStrat = MANUAL;
}

Strategy::Strat Strategy::getCurrentStrat() {
    return _currentStrat;
}

void Strategy::switchStrategy(Strat newStrat) {
    _currentStrat = newStrat;
}

Strategy::Action Strategy::makeMove(UberCasino::Hand hand) {
    switch (_currentStrat) {

        case Strat::MANUAL:
            return Action::DEFAULT;

        case Strat::CONSERV:
            return conservativeMove(hand);

        case Strat::LOOKUP:
            return lookupMove(hand);

        case Strat::RECKLESS:
            return recklessMove();

        default:
            return Action::DEFAULT;
    }
}

Strategy::Action Strategy::conservativeMove(Hand hand) {
    if (hand.handValue() > 12)
        return STAND;
    else
        return HIT;
}

Strategy::Action Strategy::lookupMove(Hand hand) {
           /* subtracting 8 gets the proper row index value into lookupTable
              dealer value (column) currently set to 0, but should change
                depending on how this method gets the dealers up card */
    return lookupTable[ hand.handValue() - 8 ][ 0 ];
}

/* Always hit */
Strategy::Action Strategy::recklessMove() {
    return HIT;
}

} /* UberCasino */
