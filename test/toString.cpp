#include <UberCasino.h>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"

TEST_CASE( "to_string on Hand objects", "[misc][to_string(Hand)]" )
{
    SECTION( "A full hand should include every card without bounds issues" )
    {
        net::Hand hand;
        std::string expected = "";
        
        // set all cards to Ace of Diamonds and build the expected
        // output string at the same time
        for( auto i = 0u; i < net::MAX_CARDS; i++ )
        {
            hand[ i ].suite = net::Suit::diamonds;
            hand[ i ].card = net::CardKind::ace;
            hand[ i ].valid = true;
            
            expected += "Ace of Diamonds\n";
        }
        
        REQUIRE( uc::to_string( hand ) == expected );
    }

    SECTION( "A partially filled hand should not include invalid cards" )
    {
        net::Hand hand;
        std::string expected = "";
        
        for( auto i = 0u; i < 7; i++ )
        {
            hand[ i ].suite = net::Suit::diamonds;
            hand[ i ].card = net::CardKind::ace;
            hand[ i ].valid = true;
            
            expected += "Ace of Diamonds\n";
        }
        
        REQUIRE( uc::to_string( hand ) == expected );
    }

    SECTION( "A face-down first card should be represented with \"Face Down\"" )
    {
        net::Hand hand;
        std::string expected = "";
        
        hand[ 0 ].suite = net::Suit::diamonds;
        hand[ 0 ].card = net::CardKind::ace;
        hand[ 0 ].valid = false;
        expected += "Face Down\n";
        
        hand[ 1 ].suite = net::Suit::diamonds;
        hand[ 1 ].card = net::CardKind::ten;
        hand[ 1 ].valid = true;
        expected += "Ten of Diamonds\n";

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
