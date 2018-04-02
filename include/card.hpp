#ifndef CARD_H
#define CARD_H

#include <string>
#include "suits.hpp"
#include "values.hpp"
namespace UberCasino {

class Card {
  public:
    Card(Suit asuit, Value avalue); 
    std::string getValue();   //Returns card value as a string
    int getValInt();          //Returns card value as an int
    std::string getSuit();    //Returns card suit as a string


  private:
  const  Suit suit;
  const  Value value;


};
} /* UberCasino */

#endif
