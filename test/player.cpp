#include <cstdlib>
#include <iostream>
#include <string>

#include <UberCasino.h>
#include <player.hpp>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"

#define DEALER_UID  "thedealer"
#define DEALER_NAME "thedealer"
#define GAME_UID    "thegame"

#define COPY_STRING( dst, src )\
    memset( dst, 0, sizeof( src ) );\
    memcpy( dst, src, sizeof ( src ) );

std::string expectedH = "";

/**
* Creates a dealer with the configured DEALER_UID and DEALER_NAME, hosting
* a game with the configured GAME_UID.
*/

net::Dealer
create_dealer()
{
    net::Dealer dealer;
    COPY_STRING( &dealer.name, DEALER_NAME );
    COPY_STRING( &dealer.uid, DEALER_UID );
    COPY_STRING( &dealer.game_uid, GAME_UID );
    return dealer;
}

/**
* Creates a game with the configured GAME_UID
*/

net::Game
create_game()
{
    net::Card three;
    three.suite = net::Suit::spades;
    three.card =  net::CardKind::three;
    three.valid = true;

    net::Game game;
    COPY_STRING( &game.game_uid, GAME_UID );
    COPY_STRING( &game.dealer_uid, DEALER_UID );
    game.gstate = net::GameState::playing;
    game.active_player = 0;
    for(auto i = 0u; i < net::MAX_CARDS; i++ )
    {
        game.p[ game.active_player ].cards[ i ] = three;
        expectedH += "Three of Spades\n";
    }
    return game;
}


TEST_CASE( "A default player must have certain values" )
{
    uc::Player def;
    SECTION( "The balance of a default player is $200.0" )
    {
        REQUIRE( def.balance() == 200.0f );
    }

    SECTION( "The default player will bet $0" )
    {
        REQUIRE( def.bet() == 0 );
    }

    SECTION( "The default player will not be in a game" )
    {
        REQUIRE( def.game() == nullptr );
    }

    SECTION( "The default player must have an empty hand" )
    {
        REQUIRE(  def.hand()[ 0 ].suite  == (net::Suit) 0 );
        REQUIRE(  def.hand()[ 0 ].card  == (net::CardKind) 0);
        REQUIRE(  def.hand()[ 0 ].valid == false );
    }

}

TEST_CASE( "The Player methods must modify its data accordingly")
{
    SECTION( "The balance of a player should be changed by the paramater specified" )
    {
        uc::Player richBoi;
        richBoi.balance( 300 );

        REQUIRE( richBoi.balance() == 300.0f );

        richBoi.balance( 0 );

        REQUIRE( richBoi.balance() == 0.0f );

        richBoi.balance( -400 );

        REQUIRE( richBoi.balance() == -400.0f);
    }

    SECTION( "The players bet should be changed by the paramater specified" )
    {
        uc::Player drunkBoi;
        drunkBoi.bet( 10 );

        REQUIRE( drunkBoi.bet() == 10 );

        drunkBoi.bet( 50 );

        REQUIRE( drunkBoi.bet() == 50 );

        drunkBoi.bet( 500 );

        REQUIRE( drunkBoi.bet() == 200 );

        drunkBoi.balance( 500 );
        drunkBoi.bet( 500 );

        REQUIRE( drunkBoi.bet() == 500 );

    }

    SECTION( "A player leaving an invalid game should not crash" )
    {
        uc::Player lostBoi;

        lostBoi.leave();

        REQUIRE( lostBoi.game() == nullptr );

    }

    SECTION( "A players uid must match the uid of the player sent over the network")
    {
        net::Dealer dealer;
        uc::Player original;
        original.strategy( new uc::RecklessStrategy );
        original.join( dealer );

        REQUIRE( original == original.to() );

    }

    SECTION( "If the player joins a game, the uid of the current game must match the game_uid of the dealer" )
    {
        net::Dealer dealer;
        uc::Player janus;
        janus.strategy( new uc::RecklessStrategy );

        janus.join( dealer );
        std::string plguid = janus.game()->game_uid;
        std::string dlguid = dealer.game_uid;

        REQUIRE( plguid == dlguid );

    }

    SECTION(" Trying to convert data from a game struct before joining a game should throw an exception" )
    {
        uc::Player eager;
        net::Game nogame;

        REQUIRE_THROWS( eager.from( nogame ) );
    }

    SECTION( "Converting data from a joined game should copy cards to the players hand" )
    {
        // uc::Player dataman;
        // dataman.strategy( new uc::ConservativeStrategy );
        // net::Game game = create_game();
        // net::Dealer dealer = create_dealer();
        //
        // dataman.join( dealer );
        // dataman.from( game );
        //
        // REQUIRE( uc::to_string( dataman.hand() ) == expectedH );

    }

    SECTION( "The to method should generate a correct player for networking" )
    {
        std::string plname = "Austin Donovan";
        uc::Player sourcePl;
        sourcePl.balance( 500 );
        sourcePl.strategy( new uc::RecklessStrategy );

        net::Dealer dealio;
        sourcePl.join( dealio );

        net::Player netPl;
        netPl = sourcePl.to();

        REQUIRE( netPl.name == plname.c_str() );
        REQUIRE( netPl.balance == 500.0f );
        REQUIRE( netPl.A == net::Action::hitting );



    }


}
