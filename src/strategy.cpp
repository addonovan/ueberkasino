#include "strategy.hpp"

#include <vector>
#include <string> // this will probably change
#include <stdexcept>

Strategy::Strategy() {
    _currentStrat = MANUAL;
}

void Strategy::switchStrategy(Strat newStrat) {
    _currentStrat = newStrat;
}

std::string Strategy::makeMove(std::vector<UberCasino::Card> hand) {
    switch (_currentStrat) {

        case MANUAL:
            return "nothing";

        case CONSERV:
            return conservativeMove(hand);

        case LOOKUP:
            return lookupMove(hand);

        case COUNT:
            return countingMove(hand);

        case RECKLESS:
            return recklessMove(hand);

        default:
            return "nothing";
    }
}

std::string Strategy::conservativeMove(std::vector<UberCasino::Card> hand) {
    int value = 0;

    for (UberCasino::Card card : hand) {
        value += card.getValInt();
    }

    if (value > 12) 
        return "Stand";
    else
        return "Hit";
}

std::string Strategy::countingMove(std::vector<UberCasino::Card> hand) {
    (void)(hand);
    throw std::runtime_error{"I wasn't implemented :("};
}

std::string Strategy::recklessMove(std::vector<UberCasino::Card> hand) {
    (void)(hand);
    return "Hit";
}

std::string Strategy::lookupMove(std::vector<UberCasino::Card> hand) {
    (void)(hand);
    throw std::runtime_error{"I wasn't implemented :("};
}
