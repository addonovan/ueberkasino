#include <iostream>
#include "card.hpp"

int main(){

std::string expectedSuit= "DIAMONDS";
std::string expectedValue= "JACK";
bool passed =true;

UberCasino::Card newcard(Suit::DIAMONDS, Value::JACK);
UberCasino::Card ace(Suit::HEARTS, Value::ACE);

if(newcard.getSuit() !=expectedSuit){
  std::cerr<< "Constructor fail!: got '" <<newcard.getSuit()<< "' but expecting '"
  << expectedSuit << "'"<<std::endl;
  passed= false;
}

if(newcard.getValue() !=expectedValue){
  std::cerr<< "Constructor fail!: got '" <<newcard.getValue()<< "' but expecting '"
  << expectedValue << "'"<<std::endl;
  passed= false;
}


return 0;

}
