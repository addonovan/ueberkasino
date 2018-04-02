#include "shoe.hpp"

namespace UberCasino {

  /**
  Returns the card at the index specified in the Shoe
  @param i the index specified
  @return the card at the specified index
  */
  Card Shoe::next(int i){ return Deck[i]; }

  /**
  Fills the shoe with 52 cards by alternating suits
  */
  void Shoe::instanceShoe(){

    for(int s=0; s<4; s++){
        if(s%2 !=0){
          for(int v=0; v<13; v++){
            Deck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
          }
        }
        if(s%2 ==0){
          for(int v=0; v<13; v++){
            Deck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
          }
        }
      }
    }

  /**
  Empties all the cards in the shoe, used after all cards have been dealt
  */
  void Shoe::resetShoe() {Deck.clear();}
  
  /**
  Provides access to the vector of cards in the Shoe
  @return the vector of cards
  */
  std::vector<Card> Shoe::getShoe(){ return Deck;}

  /**
  Adds a new card to the Shoe
  @param card the card to be added
  */
  void Shoe::addCard(Card card){ Deck.push_back(card); }

} /* UberCasino */
