#include "eightdeckshoe.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>

int main(){
  bool passed;
  UberCasino::EightDeckShoe testShoe;

    testShoe.instanceShoe();
    int i,j;
    std::cin>>i;
    while(true && !(testShoe.getShoe().empty())){

      if(j >=testShoe.getShoe().size()-1){
        testShoe.resetShoe();
      }
      std::cout<<" " <<j<<" "<<testShoe.next(j).getSuit()<<" "<< testShoe.next(j).getValue()<<std::endl;
      j++;
      std::this_thread::sleep_for(std::chrono::milliseconds(i));
  }
}
