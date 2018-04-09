#include "infiniteshoe.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <thread>

bool quitter = false;
int i;
auto j = 0u;
UberCasino::InfiniteShoe testInfShoe;

void printDeck() {

  while (!quitter) {
    if (j > testInfShoe.getShoe().size()) {
      testInfShoe.instanceShoe();
    }

    std::cout << testInfShoe.next(j).getSuit() << " "
              << testInfShoe.next(j).getValue() << std::endl;
    j++;
    std::this_thread::sleep_for(std::chrono::milliseconds(i));
  }
}

void stopper() {
  if (std::cin.get() == 'q')
    quitter = true;
}

int main() {
  /*
  std::cin >> i;
  std::cin.clear();
  std::cin.ignore(1000, '\n');
  testInfShoe.instanceShoe();
  std::thread dealer_thread(printDeck);
  std::thread stop_thread(stopper);

  dealer_thread.join();
  stop_thread.join();
  */
  return 0;
}
