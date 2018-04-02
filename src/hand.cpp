#include "hand.hpp"

namespace UberCasino {

/**
 Provides access to the vector of cards in the hand
 @return The vector of cards
*/
std::vector<Card> Hand::cards() const{ return m_cards;}

/**
 Adds a new card to the hand
 @param card the card to add
*/
void Hand::addCard(Card card){ m_cards.push_back(card);}

/**
 Empties all the cards in the hand, used at the end of a round
*/
void Hand::resetHand(){m_cards.clear();}

/**
 Calculates the current value of the hand
 @return current value of the hand (int)
*/
int Hand::handValue()
{
  bool aceChk=false;
  int sum=0;
  for(int i=0; i< m_cards.size(); i++)
  {
    sum+=  m_cards[i].getValInt();
    if(m_cards[i].getValInt()==1){
      aceChk=true;
    }
  }

  if(aceChk && sum<=11){
    sum+=10;
  }
  return sum;
}


} /* UberCasino */
