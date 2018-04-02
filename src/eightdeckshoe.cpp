#include "eightdeckshoe.hpp"

namespace UberCasino {

  /**
  Returns the card at the index specified in the Shoe
  @param i the index specified
  @return the card at the specified index
  */
  Card EightDeckShoe::next(int i){ return EightDeck[i]; }

  /**
  Fills the shoe with 416 cards by alternating suits
  */
  void EightDeckShoe::instanceShoe(){
   for(int e=0; e<8; e++){
    for(int s=0; s<4; s++){
        if(s%2 !=0){
          for(int v=0; v<13; v++){
            EightDeck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
          }
        }
        if(s%2 ==0){
          for(int v=0; v<13; v++){
            EightDeck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
          }
        }
      }
    }
  }

  /**
  Empties all the cards in the shoe, used after all cards have been dealt
  */
  void EightDeckShoe::resetShoe() {EightDeck.clear();}

  /**
  Provides access to the vector of cards in the Shoe
  @return the vector of cards
  */
  std::vector<Card> EightDeckShoe::getShoe(){ return EightDeck;}

  /**
  Adds a new card to the Shoe
  @param card the card to be added
  */
  void EightDeckShoe::addCard(Card card){ EightDeck.push_back(card); }

} /* UberCasino */
