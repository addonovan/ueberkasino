#include "player.hpp"

namespace UberCasino{
/**
Provides access to the playerHand Hand
@return the playerHand
*/
Hand Player::getHand(){return playerHand;}

/**
 Adds a new card to the hand
 @param card the card to add
*/
void Player::addCard(Card card){

  playerHand.addCard(card);
  m_net.cards[playerHand.cards().size()] =card.to_ospl(card);
}
/**
Adds money earned from the round into the players purse
@param w the winnings earned
*/
void Player::payout(int w){
  purse +=w;
}

/**
Removes money bet in the roud from the players purse
@ param b the amount bet
*/
void Player::bet(int b){
  purse -=b;
}

/**
Changes the current strategy to a new strategy
@param newStrat the strategy to use
*/
void Player::chooseStrategy(Strategy::Strat newStrat) {
    _currentStrategy.switchStrategy(newStrat);
}
/**
Determines the players next action based on the current Strategy
@param a the action to take from the button press
@return the action selected by the players
*/
Strategy::Action Player::action(int a) {
    if (_currentStrategy.getCurrentStrat() == Strategy::Strat::MANUAL) {
        if (a==1){
          std::cout<<"Hitting"<<std::endl;
	         return Strategy::Action::HIT;
	}
        if(a==2){
          std::cout<<"Standing"<<std::endl;
           return Strategy::Action::STAND;
	}
        if(a==3){
          std::cout<<"Doubling_Down"<<std::endl;
           return Strategy::Action::DOUBLE;
  }
        // i.e. this is handled elsewhere
        return Strategy::Action::DEFAULT;
    } else {
        return _currentStrategy.makeMove(playerHand);
    }

}

}
