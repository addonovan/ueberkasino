#include "dealer.hpp"

namespace UberCasino {

/** Provides access to the dealers shoe */
Shoe Dealer::getShoe() { return dealerShoe;}
/** Provides access to the dealers hand */
Hand Dealer::getHand() { return dealerHand;}

/*Places a blackjack in the players hand*/
void Dealer::dealBlackJack(){

  dealerShoe.addCard(ace);
  dealerShoe.addCard(jack);

}
/*Places a card value greater than 21 in the players hand*/
void Dealer::dealBustedHand(){

  dealerShoe.addCard(ten);
  dealerShoe.addCard(seven);
  dealerShoe.addCard(ten);
}
/*Places a card value less than 21 in the players hand*/
void Dealer::dealConservativeHand(){

  dealerShoe.addCard(seven);
  dealerShoe.addCard(ace);
}

/*Places a blackjack in the dealers hand*/
void Dealer::giveBlackJack(){

  dealerHand.addCard(ace);
  dealerHand.addCard(jack);

}
/*Places a card value greater than 21 in the dealers hand*/
void Dealer::giveBustedHand(){

  dealerHand.addCard(ten);
  dealerHand.addCard(seven);
  dealerHand.addCard(ten);
}

/*Places a card value less than 21 in the dealers hand*/
void Dealer::giveConservativeHand(){

  dealerHand.addCard(seven);
  dealerHand.addCard(ace);
}


} /* UberCasino */
