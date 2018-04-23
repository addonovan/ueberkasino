#ifndef CARD_H
#define CARD_H

#include "suits.hpp"
#include "values.hpp"
#include <string>
#include "UeberKasino.h"

typedef UeberKasino::card_t UKCard;
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

  /**
  *Returns the enum suit of the card
  *@return the suit of the card (enum)
  */
  Suit _suit();

  /**
  *Returns the enum value of the card
  *@return the value of the card (enum)
  */
  Value _value();

  /**
  *Converts a card to the card_t type in the idl
  * @Return card_t of the selected card
  */
 UKCard to_ospl(Card plcard);


private:
  const Suit suit;

  const Value value;
};

} /* UberCasino */

#endif
