#ifndef PLAYER_H
#define PLAYER_H

#include "card.hpp"
#include "hand.hpp"

namespace UberCasino {

  class Player{

  public:
    Hand getHand();
    void addCard(Card card);
    int betAmount();
    void chooseStrategy();
    void action();


  private:
    Hand playerHand;

  };


} /* UberCasino */

#endif
