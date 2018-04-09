#ifndef DEALER_H
#define DEALER_H

#include "card.hpp"
#include "shoe.hpp"
#include "eightdeckshoe.hpp"
#include "infiniteshoe.hpp"
#include "hand.hpp"

namespace UberCasino {

  class Dealer{

  public:
    Shoe getShoe();
    Hand getHand();
    void dealBlackJack();
    void dealBustedHand();
    void dealConservativeHand();

    void giveBlackJack();
    void giveBustedHand();
    void giveConservativeHand();

  private:
    Shoe dealerShoe;
    Hand dealerHand;
    Card ace{Suit::SPADES, Value::ACE};
    Card jack{Suit::SPADES, Value::JACK};
    Card ten{Suit::HEARTS, Value::TEN};
    Card seven{Suit::DIAMONDS, Value::SEVEN};


  };

} /* UberCasino */

#endif
