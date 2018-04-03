#include "card.hpp"

namespace UberCasino {

Card::Card(Suit asuit, Value avalue) : suit{asuit}, value{avalue} {}

std::string Card::getValue() { return values[value]; }

int Card::getValInt() { return integervals[value]; }

std::string Card::getSuit() { return suits[suit]; }

}
