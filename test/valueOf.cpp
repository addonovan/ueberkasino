#include <UberCasino.h>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"


TEST_CASE( "value_of calculates the value of a given hand", "[misc][value_of(Hand)]" )
{
    SECTION("An empty hand has a value of 0")
    {
         net::Hand empty;

         REQUIRE( uc::value_of( empty ) == 0u );
    }

    SECTION("A single ace has a value of 11")
    {
         net::Card ace;
         ace.suite = net::Suit::spades;
         ace.card = net::CardKind::ace;
         ace.valid = true;

         net::Hand one;
         one[ 0 ] = ace;

         REQUIRE( uc::value_of( one ) == 11u );
    }

    SECTION("Two aces has a value of 12")
    {
         net::Card ace;
         ace.suite = net::Suit::spades;
         ace.card = net::CardKind::ace;
         ace.valid = true;

         net::Hand two;
         two[ 0 ] = ace;
         two[ 1 ] = ace;

         REQUIRE( uc::value_of( two ) == 12u );
    }

    SECTION("Every ace in a hand of all aces has a value of 1 except for one")
    {
         net::Card ace;
         ace.suite = net::Suit::clubs;
         ace.card = net::CardKind::ace;
         ace.valid = true;

         net::Hand aceHigh;
         aceHigh[ 0 ] = ace;
         aceHigh[ 1 ] = ace;
         aceHigh[ 2 ] = ace;
         aceHigh[ 3 ] = ace;
         aceHigh[ 4 ] = ace;

         REQUIRE( uc::value_of( aceHigh ) == 15u );
    }

    SECTION("All face cards have a value of 10 ")
    {
         net::Card king, queen, jack;
         king.suite = net::Suit::hearts;
         king.card = net::CardKind::king;
         king.valid = true;

         queen.suite = net::Suit::clubs;
         queen.card = net::CardKind::queen;
         queen.valid = true;

         jack.suite = net::Suit::diamonds;
         jack.card = net::CardKind::jack;
         jack.valid = true;

         net::Hand faceMe;
         faceMe[ 0 ] = jack;
         faceMe[ 1 ] = king;
         faceMe[ 2 ] = queen;
         faceMe[ 3 ] = king;
         faceMe[ 4 ] = jack;

         REQUIRE( uc::value_of( faceMe ) == 50u );
    }

    SECTION( "A hand of invalid cards has a value of 0" )
    {
         net::Hand invhand;
         net::Card ten;
         ten.suite = net::Suit::diamonds;
         ten.card = net::CardKind::ten;
         ten.valid = false;

         for( auto i = 0u; i < net::MAX_CARDS; i++)
         {
              invhand[ i ] = ten;
         }

         REQUIRE( uc::value_of ( invhand ) == 0u );
    }

    SECTION( "A hand with the first card invalid belongs to the dealer" )
    {
         net::Hand dealer;
         net::Card ten;
         ten.suite = net::Suit::diamonds;
         ten.card = net::CardKind::ten;
         ten.valid = false;

         net::Card ace;
         ace.suite = net::Suit::spades;
         ace.card = net::CardKind::ace;
         ace.valid = true;

         dealer[ 0 ] = ten;
         dealer[ 1 ] = ace;

         REQUIRE( uc::value_of( dealer ) == 11u );
    }

    SECTION( "A hand of assorted values must have a correct value ")
    {
         net::Hand assortHand;
         net::Card seven;
         seven.suite = net::Suit::spades;
         seven.card =  net::CardKind::seven;
         seven.valid = true;

         net::Card six;
         six.suite = net::Suit::hearts;
         six.card  = net::CardKind::six;
         six.valid = true;

         assortHand[ 0 ] = seven;
         assortHand[ 1 ] = seven;

         REQUIRE( uc::value_of( assortHand ) == 14u );

         assortHand[ 3 ] = six;
         assortHand[ 2 ] = six;

         REQUIRE( uc::value_of( assortHand ) == 26u );
    }
}
