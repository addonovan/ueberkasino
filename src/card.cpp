#include "card.hpp"

namespace UberCasino {
  /**Creates a card with the given suit and value */
  Card::Card(Suit asuit, Value avalue): suit{asuit}, value{avalue} {}

  /**
   Returns the value of a card as a string
   @return the value of the card (string)
  */
  std::string Card::getValue() {return values[value];}

  /**
   Returns the value of a card as an integer
   @return the value of the card (int)
  */
  int Card::getValInt(){return integervals[value];}

  /**
   Returns the suit of a card as a string
   @return the suit of the card (string)
  */  
  std::string Card::getSuit()  {return suits[suit];}

} /* UberCasino */
