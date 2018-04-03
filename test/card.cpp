#include "card.hpp"
#include <iostream>

int main() {
  std::string expectedSuit = "DIAMONDS";
  std::string expectedValue = "JACK";

  UberCasino::Card newcard{Suit::DIAMONDS, Value::JACK};
  UberCasino::Card ace{Suit::HEARTS, Value::ACE};

  if (newcard.getSuit() != expectedSuit) {
    std::cerr << "Constructor fail!: got '" << newcard.getSuit()
              << "' but expecting '" << expectedSuit << "'" << std::endl;
  }

  if (newcard.getValue() != expectedValue) {
    std::cerr << "Constructor fail!: got '" << newcard.getValue()
              << "' but expecting '" << expectedValue << "'" << std::endl;
  }

  return 0;
}
