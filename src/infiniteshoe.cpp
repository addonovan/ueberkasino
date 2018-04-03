#include "infiniteshoe.hpp"

namespace UberCasino {

/**
 Returns the card at the index specified in the Shoe
 @param i the index specified
 @return the card at the specified index
*/
Card InfiniteShoe::next(int i) { return infinteDeck[i]; }

/**
Fills the shoe with 416 cards, randomly choosing suit and value
*/

void InfiniteShoe::instanceShoe() {
  int randSuit, randVal;
  srand(time(NULL));
  for (int e = 0; e < 416; e++) {
    randSuit = rand() % 4;
    randVal = rand() % 13;
    infinteDeck.push_back((UberCasino::Card{(Suit)randSuit, (Value)randVal}));
  }
}
/**
Provides access to the vector of cards in the Shoe
@return the vector of cards
*/
std::vector<Card> InfiniteShoe::getShoe() { return infinteDeck; }

} /* UberCasino */
