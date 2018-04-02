#ifndef EIGHTDECKSHOE_H
#define EIGHTDECKSHOE_H
#include "shoe.hpp"
#include <vector>


namespace UberCasino {

class EightDeckShoe{

  public:
    Card next(int i);              //Returns the card at index i in the shoe
    void addCard(Card card);       //Adds a card to the Shoe
    void resetShoe();              //Empties all cards in the Shoe
    void instanceShoe();           //Fills the shoe with a set number of cards
    std::vector<Card> getShoe();   //Returns the vector of cards in the shoe

  private:
      std::vector<Card> EightDeck;
  };

}

#endif
