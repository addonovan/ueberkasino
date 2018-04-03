#include "shoe.hpp"
#include <chrono>
#include <ctime>
#include <iostream>
#include <stdlib.h>
#include <thread>

int main() {
  UberCasino::Shoe testShoe;

  testShoe.instanceShoe();
  int i;
  auto j = 0u;
  std::cin >> i;
  while (!(testShoe.getShoe().empty())) {

    if (j >= testShoe.getShoe().size() - 1) {
      testShoe.resetShoe();
    }

    std::cout << " " << j << " " << testShoe.next(j).getSuit() << " "
              << testShoe.next(j).getValue() << std::endl;
    j++;

    std::this_thread::sleep_for(std::chrono::milliseconds(i));
  }
}
