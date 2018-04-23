#include "card.hpp"

namespace UberCasino {

Card::Card(Suit asuit, Value avalue) : suit{asuit}, value{avalue} {}

std::string Card::getValue() { return values[value]; }

int Card::getValInt() { return integervals[value]; }

std::string Card::getSuit() { return suits[suit]; }

Suit Card::_suit(){
  return suit;
}

Value Card::_value(){
 return value;
}

UKCard Card::to_ospl(Card plcard){

UKCard acard;
acard.suite = (UeberKasino::suite_t) plcard._suit();
acard.card  = (UeberKasino::card_kind) plcard._value();
acard.valid = true;

 return acard;
}

}
