#ifndef HAND_H
#define HAND_H
#include "card.hpp"
#include <vector>

namespace UberCasino {

class Hand {
public:
  std::vector<Card> cards() const; // Returns the vector of cards in the hand
  void addCard(Card card);         // Adds a card to the hand
  void resetHand();                // Removes all cards from the hand
  int handValue();                 // Returns the current value of the hand

private:
  std::vector<Card> m_cards;
};
} /* UberCasino */

#endif
