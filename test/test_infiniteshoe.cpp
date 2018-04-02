#include "infiniteshoe.hpp"
#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <thread>
#include <chrono>

bool quitter=false;
int j,i;
UberCasino::InfiniteShoe testInfShoe;

//Requires compile with -pthread

void printDeck(){

  while(true && !quitter){

    if(j >testInfShoe.getShoe().size()){
      testInfShoe.instanceShoe();
    }
    std::cout<<testInfShoe.next(j).getSuit()<<" "<< testInfShoe.next(j).getValue()<<std::endl;
    j++;
    std::this_thread::sleep_for(std::chrono::milliseconds(i));

}

}

void stopper(){
  if(std::cin.get()=='q')
    quitter=true;
}



int main(){
  std::cin>>i;
  std::cin.clear();
  std::cin.ignore(1000, '\n');
  testInfShoe.instanceShoe();
  std::thread dealer_thread(printDeck);
  std::thread stop_thread(stopper);

  dealer_thread.join();
  stop_thread.join();
  

      return 0;
  }
