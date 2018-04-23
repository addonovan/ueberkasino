#ifndef PLAYER_H
#define PLAYER_H

#include "card.hpp"
#include "hand.hpp"
#include "UeberKasino.h"
#include "strategy.hpp"
#include <boost/thread.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>


namespace UberCasino {

typedef UeberKasino::PlayerState UKPlaystate;
  class Player{

  public:
    Hand getHand();                       //Getter for player hand
    void addCard(Card card);              //Add a card to the players hand
    void payout(int w);                   //Add money to players purse
    void bet(int b);                      //Remove money from players purse
    void chooseStrategy(Strategy::Strat); //Switch current strategy
    Strategy::Action action(int a);       //The action the player will take [HIT, STAND, DOUBLE]




  private:
    UKPlaystate m_net;      //Player state for networking
    Strategy _currentStrategy; //the current strategy
    Hand playerHand;          // the player's hand
    int purse=200;            // The players total money

};


} /* UberCasino */

#endif
