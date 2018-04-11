#ifndef STRATEGY_HPP
#define STRATEGY_HPP

#include <vector>
#include <string>
#include "card.hpp"

class Strategy {
public:
    enum Strat { MANUAL, CONSERV, LOOKUP, COUNT, RECKLESS };

    Strategy();

    void switchStrategy(Strat);
    std::string makeMove(std::vector<UberCasino::Card>);

    // helpers
    std::string conservativeMove(std::vector<UberCasino::Card>);
    std::string countingMove(std::vector<UberCasino::Card>);
    std::string recklessMove(std::vector<UberCasino::Card>);
    std::string lookupMove(std::vector<UberCasino::Card>);

private:
    Strat _currentStrat;
};

#endif
