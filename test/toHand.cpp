#include <UberCasino.h>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"

TEST_CASE( "to_hand converts an array of cards to a hand", "[misc]to_hand(Card)")
{
    SECTION("A single valid card is an acceptable hand")
    {
       net::Card three;
       three.suite = net::Suit::spades;
       three.card =  net::CardKind::three;
       three.valid = true;
       net::Card singleCard [] = { three } ;

       net::Hand testHand;
       testHand = uc::to_hand( singleCard );

       REQUIRE( ( testHand[ 0 ].suite ) == net::Suit::spades );
       REQUIRE( ( testHand[ 0 ].card ) ==  net::CardKind::three );
       REQUIRE( uc::is_valid (testHand[ 0 ] ) == true );

    }

    SECTION("A single invalid card in an array is expected from the dealer")
    {
       net::Card two;
       two.suite = net::Suit::diamonds;
       two.card =  net::CardKind::two;
       two.valid = false;

       net::Card four;
       four.suite = net::Suit::diamonds;
       four.card =  net::CardKind::four;
       four.valid = true;

       net::Card singleCard [] = { two, four } ;

       net::Hand testHand;
       testHand = uc::to_hand( singleCard );

       REQUIRE( ( testHand[ 0 ].suite ) ==  ( net::Suit ) 0 );
       REQUIRE( ( testHand[ 0 ].card ) == ( net::CardKind ) 0 );
       REQUIRE( uc::is_valid (testHand[ 0 ] ) == false );

       REQUIRE( ( testHand[ 1 ].suite ) ==  net::Suit::diamonds );
       REQUIRE( ( testHand[ 1 ].card ) ==  net::CardKind::four );
       REQUIRE( uc::is_valid (testHand[ 1 ] ) == true );

    }

    SECTION("A full hand created from a full array")
    {
        net::Card fullCard[ net::MAX_CARDS ];
        net::Card six;
        six.suite = net::Suit::hearts;
        six.card  = net::CardKind::six;
        six.valid = true;

        net::Card ace;
        ace.suite = net::Suit::spades;
        ace.card = net::CardKind::ace;
        ace.valid = true;

        net::Card inv;
        inv.valid = false;

        fullCard[ 0 ] = ace;
        for(auto i = 1u; i< net::MAX_CARDS; i++)
        {
            if( i % 2 == 0 )
            {
                fullCard[ i ] = six;
            }
           //Items 3 & 9 are invalid
            else if( i % 3 == 0 )
            {
                fullCard[ i ] = inv;
            }
            else
            {
                fullCard[ i ] = ace;
            }
        }
        net::Hand testHand;
        testHand = uc::to_hand( fullCard );
        REQUIRE( ( testHand[ 0 ].suite ) == net::Suit::spades );
        REQUIRE( ( testHand[ 0 ].card ) == net::CardKind::ace );
        REQUIRE( uc::is_valid ( testHand[ 0 ] ) == true );

        REQUIRE( ( testHand[ 1 ].suite ) == net::Suit::spades );
        REQUIRE( ( testHand[ 1 ].card ) ==  net::CardKind::ace);
        REQUIRE( uc::is_valid ( testHand[ 1 ] ) == true );

        REQUIRE( ( testHand[ 2 ].suite ) == net::Suit::hearts );
        REQUIRE( ( testHand[ 2 ].card ) == net::CardKind::six );
        REQUIRE( uc::is_valid ( testHand[ 2 ] ) == true );

        REQUIRE( ( testHand[ 3 ].suite ) == ( net::Suit ) 0 );
        REQUIRE( ( testHand[ 3 ].card ) == ( net::CardKind ) 0  );
        REQUIRE( uc::is_valid ( testHand[ 3 ] ) == false );

        REQUIRE( ( testHand[ 4 ].suite ) == net::Suit::hearts );
        REQUIRE( ( testHand[ 4 ].card ) == net::CardKind::six );
        REQUIRE( uc::is_valid ( testHand[ 4 ] ) == true );

        REQUIRE( ( testHand[ 5 ].suite ) == net::Suit::spades );
        REQUIRE( ( testHand[ 5 ].card ) == net::CardKind::ace );
        REQUIRE( uc::is_valid ( testHand[ 5 ] ) == true );

        REQUIRE( ( testHand[ 6 ].suite ) == net::Suit::hearts );
        REQUIRE( ( testHand[ 6 ].card ) == net::CardKind::six );
        REQUIRE( uc::is_valid ( testHand[ 6 ] ) == true );

        REQUIRE( ( testHand[ 7 ].suite ) == net::Suit::spades );
        REQUIRE( ( testHand[ 7 ].card ) == net::CardKind::ace );
        REQUIRE( uc::is_valid ( testHand[ 7 ] ) == true );

        REQUIRE( ( testHand[ 8 ].suite ) == net::Suit::hearts );
        REQUIRE( ( testHand[ 8 ].card ) == net::CardKind::six );
        REQUIRE( uc::is_valid ( testHand[ 8 ] ) == true );

        REQUIRE( ( testHand[ 9 ].suite ) == ( net::Suit ) 0 );
        REQUIRE( ( testHand[ 9 ].card ) == ( net::CardKind ) 0  );
        REQUIRE( uc::is_valid ( testHand[ 9 ] ) == false );
   }
}
