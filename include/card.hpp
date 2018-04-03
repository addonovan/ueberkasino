#ifndef CARD_H
#define CARD_H

#include "suits.hpp"
#include "values.hpp"
#include <string>
namespace UberCasino {

class Card {

public:
  /**
   * Creates a card with the given suit and value
   */
  Card(Suit asuit, Value avalue);

  /**
   * Returns the value of a card as a string
   * @return the value of the card (string)
   */
  std::string getValue();

  /**
   * Returns the value of a card as an integer
   * @return the value of the card (int)
   */
  int getValInt();

  /**
   * Returns the suit of a card as a string
   * @return the suit of the card (string)
   */
  std::string getSuit();

private:
  const Suit suit;

  const Value value;
};
} /* UberCasino */

#endif
