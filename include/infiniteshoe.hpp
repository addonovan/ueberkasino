#ifndef INFINITESHOE_H
#define INFINITESHOE_H

#include "shoe.hpp"
#include <stdlib.h>
#include <time.h>

namespace UberCasino {

class InfiniteShoe : public Shoe {
public:
  Card next(int i);            // Returns the card at index i in the shoe
  void resetShoe();            // Empties all cards in the Shoe
  void instanceShoe();         // Fills the shoe with a set number of cards
  std::vector<Card> getShoe(); // Returns the vector of cards in the shoe

private:
  std::vector<Card> infinteDeck;
};

} /* UberCasino */

#endif
