#include "player.hpp"
#include "dealer.hpp"
#include <iostream>
#include <thread>

int main(){

UberCasino::Dealer testDealer;
UberCasino::Player testPlayer;

testDealer.giveConservativeHand();
testDealer.dealBlackJack();

std::cout<<"Start test program"<<std::endl;


for(int j=0; j<2; j++){
    std::cout<<"Dealing Cards"<<std::endl;
    std::cout<<j<<std::endl;

  testPlayer.addCard(testDealer.getShoe().next(j));
  /*
  std::cout <<j<< " " << testPlayer.getHand().cards()[j].getSuit() << " "
            << testPlayer.getHand().cards()[j].getValue() << std::endl;
  std::cout<<"Cards Dealt"<<std::endl;
  */
}

if(testDealer.getHand().handValue() > testPlayer.getHand().handValue()){

  std::cout<<"Player loses the round"<<std::endl;
}

else
{
  std::cout<<"Player wins the round"<<std::endl;
}

 return 0;
}
