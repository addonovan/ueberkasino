#include "eightdeckshoe.hpp"

namespace UberCasino {

EightDeckShoe::EightDeckShoe() {
  for (int e = 0; e < 8; e++) {
    for (int s = 0; s < 4; s++) {
      if (s % 2 != 0) {
        for (int v = 0; v < 13; v++) {
          EightDeck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
        }
      }
      if (s % 2 == 0) {
        for (int v = 0; v < 13; v++) {
          EightDeck.push_back((UberCasino::Card{(Suit)s, (Value)v}));
        }
      }
    }
  }
}

Card EightDeckShoe::next(int i) { return EightDeck[i]; }

void EightDeckShoe::resetShoe() { EightDeck.clear(); }

std::vector<Card> EightDeckShoe::getShoe() { return EightDeck; }

void EightDeckShoe::addCard(Card card) { EightDeck.push_back(card); }

} /* UberCasino */
