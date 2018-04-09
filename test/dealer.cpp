#include "dealer.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main(){
  int j=0;
  UberCasino::Dealer testDealer;



  while(j<5){
    testDealer.dealBustedHand();

    testDealer.getShoe().next(j);
    std::cout<<testDealer.getShoe().next(j).getSuit()<<" "<< testDealer.getShoe().next(j).getValue()<<std::endl;
    j++;

  }

}
