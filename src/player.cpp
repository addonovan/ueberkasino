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
}


int Player::betAmount(){
  int b;
  b= 50;
  return b;

}

void Player::chooseStrategy(){

}

void Player::action(){

}



}
