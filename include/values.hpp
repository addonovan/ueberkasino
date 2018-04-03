#ifndef VALUES_H
#define VALUES_H

#include <string>
#include <vector>

enum Value {
  ACE,
  TWO,
  THREE,
  FOUR,
  FIVE,
  SIX,
  SEVEN,
  EIGHT,
  NINE,
  TEN,
  JACK,
  QUEEN,
  KING
};
const std::vector<std::string> values = {"ACE",  "2",     "3",   "4", "5",
                                         "6",    "7",     "8",   "9", "10",
                                         "JACK", "QUEEN", "KING"};
const std::vector<int> integervals = {1, 2, 3,  4,  5,  6, 7,
                                      8, 9, 10, 10, 10, 10};

#endif
