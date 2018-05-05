#include <UberCasino.h>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"

TEST_CASE( "to_string on Hand objects", "[misc][to_string(Hand)]" )
{
    SECTION( "A full hand should include every card without bounds issues" )
    {
        net::Card full[ net::MAX_CARDS ];
        std::string expected = "";

        // set all cards to Ace of Diamonds and build the expected
        // output string at the same time
        for( auto i = 0u; i < net::MAX_CARDS; i++ )
        {
            full[ i ].suite = net::Suit::diamonds;
            full[ i ].card = net::CardKind::ace;
            full[ i ].valid = true;

            expected += "Ace of Diamonds\n";
        }
        net::Hand hand = uc::to_hand( full );

        REQUIRE( uc::to_string( hand ) == expected );
    }

    SECTION( "A partially filled hand should not include invalid cards" )
    {
        net::Card part[ 7 ];
        std::string expected = "";

        for( auto i = 0u; i < 7; i++ )
        {
            part[ i ].suite = net::Suit::diamonds;
            part[ i ].card = net::CardKind::ace;
            part[ i ].valid = true;

            expected += "Ace of Diamonds\n";
        }
        net::Hand hand = uc::to_hand( part );

        REQUIRE( uc::to_string( hand ) == expected );
    }

    SECTION( "A face-down first card should be represented with \"Face Down\"" )
    {
        net::Card fdown[ 2 ];
        std::string expected = "";

        fdown[ 0 ].suite = net::Suit::diamonds;
        fdown[ 0 ].card = net::CardKind::ace;
        fdown[ 0 ].valid = false;
        expected += "Face Down\n";

        fdown[ 1 ].suite = net::Suit::diamonds;
        fdown[ 1 ].card = net::CardKind::ten;
        fdown[ 1 ].valid = true;
        expected += "Ten of Diamonds\n";

        net::Hand hand = uc::to_hand( fdown );
        REQUIRE( uc::to_string( hand ) == expected );
    }
}

TEST_CASE( "to_string on Suit enums", "[misc][to_string(Suit)]" )
{
    SECTION( "An invalid suit value should throw an exception" )
    {
        REQUIRE_THROWS( uc::to_string( ( net::Suit ) 500 ) );
    }

    SECTION( "A valid suit value should be converted to the correct string" )
    {
        // brute forcing and testing all cases here is perfectly acceptable
        // considering how few cases there are
        REQUIRE( uc::to_string( net::Suit::spades )   == "Spades" );
        REQUIRE( uc::to_string( net::Suit::diamonds ) == "Diamonds" );
        REQUIRE( uc::to_string( net::Suit::hearts )   == "Hearts" );
        REQUIRE( uc::to_string( net::Suit::clubs )    == "Clubs" );
    }
}

TEST_CASE( "to_string on CardKind enums", "[misc][to_string(CardKind)]" )
{
    SECTION( "An invalid card value should throw an exception" )
    {
        REQUIRE_THROWS( uc::to_string( ( net::CardKind ) 500 ) );
    }

    SECTION( "A valid card value should be converted to the correct string" )
    {
        // this is probably stretching it, to be honest. This is a bit too
        // verbose of a test, but it's also very thorough. This is probably
        // acceptable to most people, considering that we REALLY don't want
        // typos or malfunctions in this part of the software
        // Plus, 13 cases to test really isn't that bad, it all still fits
        // on a single screen
        REQUIRE( uc::to_string( net::CardKind::ace )    == "Ace" );
        REQUIRE( uc::to_string( net::CardKind::two )    == "Two" );
        REQUIRE( uc::to_string( net::CardKind::three )  == "Three" );
        REQUIRE( uc::to_string( net::CardKind::four )   == "Four" );
        REQUIRE( uc::to_string( net::CardKind::five )   == "Five" );
        REQUIRE( uc::to_string( net::CardKind::six )    == "Six" );
        REQUIRE( uc::to_string( net::CardKind::seven )  == "Seven" );
        REQUIRE( uc::to_string( net::CardKind::eight )  == "Eight" );
        REQUIRE( uc::to_string( net::CardKind::nine )   == "Nine" );
        REQUIRE( uc::to_string( net::CardKind::ten )    == "Ten" );
        REQUIRE( uc::to_string( net::CardKind::jack )   == "Jack" );
        REQUIRE( uc::to_string( net::CardKind::queen )  == "Queen" );
        REQUIRE( uc::to_string( net::CardKind::king )   == "King" );
    }
}
