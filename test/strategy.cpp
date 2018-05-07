#include <cstdlib>
#include <iostream>
#include <string>

#include <UberCasino.h>
#include <strategy.hpp>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"
#include "helpers.hpp"


net::Game gameStates[ 15 ] =
{
/*0*/   gen_pl_blj_dl_ace(),       //Dealer hand = ace Player = blackjack
/*1*/   gen_pl_blj_dl_lte6(0),     //Dealer hand = 6 Player = blackjack
/*2*/   gen_pl_blj_dl_lte6(1),     //Dealer hand <6  Player = blackjack
/*3*/   gen_pl_lte11_dl_ace(0),    //Dealer hand = ace Player = 11
/*4*/   gen_pl_lte11_dl_ace(1),    //Dealer hand = ace player < 11 (7)
/*5*/   gen_pl_lte11_dl_grt6(0),   //Dealer hand >6 Player = 11
/*6*/   gen_pl_lte11_dl_grt6(1),   //Dealer hand >6 Player < 11
/*7*/   gen_pl_lte11_dl_lte6(0),   //Dealer hand =6 Player = 11
/*8*/   gen_pl_lte11_dl_lte6(1),   //Dealer hand =6 Player < 11
/*9*/   gen_pl_lte11_dl_lte6(2),   //Dealer hand <6 Player = 11
/*10*/  gen_pl_lte11_dl_lte6(3),   //Dealer hand <6 Player < 11
/*11*/  gen_pl_grt11_dl_ace(),     //Dealer hand = ace Player > 11
/*12*/  gen_pl_grt11_dl_grt6(),    //Dealer hand >6  Player > 11
/*13*/  gen_pl_grt11_dl_lte6(1),   //Dealer hand =6 Player > 11
/*14*/  gen_pl_grt11_dl_lte6(0),   //Dealer hand >6 Player > 11
};

TEST_CASE( "Strategies should return the appropiate action based on game state" )
{
    SECTION( "A manual strategy should always be idle" )
    {
        uc::ManualStrategy man;
        for( auto i = 0u; i < 14; i++ )
        {
            REQUIRE( man.process( gameStates[ i ] ) == net::Action::idle );
        }
    }

    SECTION( "A reckless strategy should always hit" )
    {
        uc::RecklessStrategy rek;
        for( auto i = 0u; i < 14; i++ )
        {
            REQUIRE( rek.process( gameStates[ i ] ) == net::Action::hitting );
        }
    }

    SECTION( "A conservative strategy should hit if it's impossible to bust" )
    {
        uc::ConservativeStrategy con;

        REQUIRE( con.process( gameStates[ 3 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 4 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 5 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 6 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 7 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 8 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 9 ] ) ==  net::Action::hitting );
        REQUIRE( con.process( gameStates[ 10 ] ) ==  net::Action::hitting );
    }

    SECTION( "A conservative strategy should stand if it's possible to bust" )
    {
        uc::ConservativeStrategy con;

        REQUIRE( con.process( gameStates[ 0 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 1 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 2 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 11 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 12 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 13 ] ) ==  net::Action::standing );
        REQUIRE( con.process( gameStates[ 14 ] ) ==  net::Action::standing );
    }

    SECTION( "A basic strategy should always play in accordance to the table" )
    {
        uc::BasicStrategy bask;

        REQUIRE_THROWS( bask.process( gameStates[ 0 ] ) );
        REQUIRE_THROWS( bask.process( gameStates[ 1 ] ) );
        REQUIRE_THROWS( bask.process( gameStates[ 2 ] ) );
        REQUIRE( bask.process( gameStates[ 3 ] ) == net::Action::doubling );
        REQUIRE( bask.process( gameStates[ 4 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 5 ] ) == net::Action::doubling );
        REQUIRE( bask.process( gameStates[ 6 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 7 ] ) == net::Action::doubling );
        REQUIRE( bask.process( gameStates[ 8 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 9 ] ) == net::Action::doubling );
        REQUIRE( bask.process( gameStates[ 10 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 11 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 12 ] ) == net::Action::hitting );
        REQUIRE( bask.process( gameStates[ 13 ] ) == net::Action::standing );
        REQUIRE( bask.process( gameStates[ 14 ] ) == net::Action::standing );
    }

}
