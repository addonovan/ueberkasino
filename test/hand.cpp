#include <hand.hpp>
#include <iostream>

int main() {
  int expectedVal = 18;
  int twoAceVal = 12;
  int blackjack = 21;
  int busted = 25;

  UberCasino::Card newcard(Suit::DIAMONDS, Value::JACK);
  UberCasino::Card ace(Suit::HEARTS, Value::ACE);
  UberCasino::Card king(Suit::HEARTS, Value::KING);
  UberCasino::Card eight(Suit::HEARTS, Value::EIGHT);
  UberCasino::Card seven(Suit::HEARTS, Value::SEVEN);
  UberCasino::Hand normHand;
  UberCasino::Hand doubleAce;
  UberCasino::Hand lucky;
  UberCasino::Hand gambler;

  normHand.addCard(king);
  normHand.addCard(eight);
  if (normHand.handValue() != expectedVal) {
    std::cerr << "Calculation error! expected " << expectedVal << " but got "
              << normHand.handValue() << std::endl;
  }

  if (normHand.cards()[0].getSuit() != king.getSuit() ||
      normHand.cards()[1].getSuit() != eight.getSuit()) {
    std::cerr << "Suit assignment error! expected " << king.getSuit() << " or "
              << eight.getSuit() << " but got " << normHand.cards()[0].getSuit()
              << std::endl;
  }
  if (normHand.cards()[0].getValue() != king.getValue() ||
      normHand.cards()[1].getValue() != eight.getValue()) {
    std::cerr << "Value assignment error! expected " << king.getValue()
              << " or " << eight.getValue() << " but got "
              << normHand.cards()[0].getValue() << std::endl;
  }
  if (normHand.cards()[0].getValInt() != king.getValInt() ||
      (normHand.cards()[1].getValInt() != eight.getValInt())) {
    std::cerr << "Value assignment error! expected " << king.getValInt()
              << " or " << eight.getValInt() << " but got "
              << normHand.cards()[0].getValInt() << std::endl;
  }

  doubleAce.addCard(ace);
  doubleAce.addCard(ace);
  if (doubleAce.handValue() != twoAceVal) {
    std::cerr << "Calculation error! expected " << twoAceVal << " but got "
              << doubleAce.handValue() << std::endl;
  }

  lucky.addCard(newcard);
  lucky.addCard(ace);
  if (lucky.handValue() != blackjack) {
    std::cerr << "Calculation error! expected " << blackjack << " but got "
              << lucky.handValue() << std::endl;
  }

  gambler.addCard(king);
  gambler.addCard(eight);
  gambler.addCard(seven);

  if (gambler.handValue() != busted) {
    std::cerr << "Calculation error! expected " << busted << " but got "
              << gambler.handValue() << std::endl;
  }
  gambler.resetHand();
  if (gambler.handValue() != 0) {
    std::cerr << "Hand Reset failed! " << gambler.handValue()
              << " still left in hand" << '\n';
  }

  return 0;
}
