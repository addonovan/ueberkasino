#include "strategy.hpp"
#include "hand.hpp"

#include <vector>
#include <stdexcept>

namespace UberCasino {

/**
Strategy()

Constructor sets initial strategy to be manual, assuming that
the user wants to start the game by playing themselves
*/
Strategy::Strategy()
{
    _currentStrat = MANUAL;
}

/**
Strat getCurrentStrat()

getter method for the current strategy
*/
Strategy::Strat Strategy::getCurrentStrat() {
    return _currentStrat;
}

/**
void switchStategy(Strat)

Input: newStrat 
    the user's choice of new strategy

This method takes a new strategy as input and switches the strategy classes
current strategy implementation to the on requested
*/
void Strategy::switchStrategy(Strategy::Strat newStrat) {
    _currentStrat = newStrat;
}

/**
Action makeMove(Hand)

Input: hand
    the user's current hand

This method passes the hand to the correct strategy implementation depending
on whatever the current strategy is set to
*/
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

/**
Action conservativeMove(Hand)

Input: hand
    the user's current hand

The conservative strategy will stand if there is a chance of busting, i.e.
    going over 21
*/
Strategy::Action Strategy::conservativeMove(UberCasino::Hand hand) {
    if (hand.handValue() > 12) 
        return Action::STAND;
    else
        return Action::HIT;
}

/**
Action lookupMove(Hand)

Input: hand
    the user's current hand

The lookup strategy will look up the corresponding action in the lookupTable
depending on the value of the user's current hand and the dealer's up-card
*/
Strategy::Action Strategy::lookupMove(UberCasino::Hand hand) {
           /* subtracting 8 gets the proper row index value into lookupTable
              dealer value (column) currently set to 0, but should change
                depending on how this method gets the dealers up card */
    return lookupTable[ hand.handValue() - 8 ][ 0 ];
}

/**
Action recklessMove()

The reckless strategy plays like someone who has had a few too many drinks and will
always hit. 
*/
Strategy::Action Strategy::recklessMove() {
    return Action::HIT;
}

} /* UberCasino */
