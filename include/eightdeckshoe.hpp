#ifndef EIGHTDECKSHOE_H
#define EIGHTDECKSHOE_H
#include "shoe.hpp"
#include <vector>

namespace UberCasino {

class EightDeckShoe {

public:
  EightDeckShoe();

  /**
   * Returns the card at the index specified in the Shoe
   * @param i the index specified
   * @return the card at the specified index
   */
  Card next(int i);

  /**
   * Adds a new card to the Shoe
   * @param card the card to be added
   */
  void addCard(Card card);

  /**
   * Empties all the cards in the shoe, used after all cards have been dealt
   */
  void resetShoe();

  /**
   * Provides access to the vector of cards in the Shoe
   * @return the vector of cards
   */
  std::vector<Card> getShoe();

private:
  std::vector<Card> EightDeck;
};
}

#endif
