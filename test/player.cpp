#include <cstdlib>
#include <iostream>
#include <string>

#include <UberCasino.h>
#include <player.hpp>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"
#include "helpers.hpp"

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
        REQUIRE( def.hand()[ 0 ].valid == false );
    }
}

TEST_CASE( "The Player methods must modify its data accordingly")
{
    SECTION( "The balance of a player should change when modified" )
    {
        uc::Player richBoi;
        richBoi.balance( 300 );
        REQUIRE( richBoi.balance() == 300.0f );
        
        richBoi.balance( 0 );
        REQUIRE( richBoi.balance() == 0.0f );
        
        richBoi.balance( -400 );
        REQUIRE( richBoi.balance() == -400.0f );
    }

    SECTION( "The players bet should change when modified" )
    {
        uc::Player drunkBoi;
        drunkBoi.bet( 10 );
        REQUIRE( drunkBoi.bet() == 10 );

        drunkBoi.bet( 50 );
        REQUIRE( drunkBoi.bet() == 50 );

        drunkBoi.bet( 200 );
        REQUIRE( drunkBoi.bet() == 200 );
    }
    
    SECTION( "Modifying a player's bet should remove from their balance" )
    {
        uc::Player player;
        player.balance( 200 );
        player.bet( 20 );

        REQUIRE( player.balance() == 180 );
    }

    SECTION( "A player should not be able to bet more than their balance" )
    {
        uc::Player dumbBoi;
        dumbBoi.balance( 500 );
        dumbBoi.bet( 1000 );

        REQUIRE( dumbBoi.bet() == 500 );
        REQUIRE( dumbBoi.balance() == 0 );
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

    SECTION( "A serialized player should equal is unserialized counterpart" )
    {
        net::Dealer dealer;
        uc::Player janus;
        janus.strategy( new uc::RecklessStrategy );

        janus.join( dealer );
        std::string plguid = janus.game()->game_uid;
        std::string dlguid = dealer.game_uid;

        REQUIRE( plguid == dlguid );
    }

    SECTION( "Deserializing a player without joining a game should throw" )
    {
        uc::Player eager;
        net::Game nogame;

        REQUIRE_THROWS( eager.from( nogame ) );
    }

    SECTION( "Converting data from a joined game should copy cards to the players hand" )
    {
        uc::Player dataman;
        dataman.strategy( new uc::ConservativeStrategy );
        dataman.join( create_dealer() );

        auto game = create_game();
        auto expected = std::string{ "" };

        for ( auto i = 0u; i < net::MAX_CARDS; i++ )
        {
            game.p[ game.active_player ].cards[ i ] = net::Card {
                .card = net::CardKind::ace,
                .suite = net::Suit::spades,
                .valid = true
            };
            expected += "Ace of Spades\n";
        }
        dataman.from( game );

        REQUIRE( uc::to_string( dataman.hand() ) == expected );
    }

    SECTION( "Serialized player packet should be correct" )
    {
        uc::Player source;
        source.balance( 500 );
        source.strategy( new uc::RecklessStrategy );

        net::Dealer dealio;
        source.join( dealio );
        source.from( create_game() );

        auto actual = source.to();
        
        // find the null terminator, or use the entire length of the string
        auto* end = std::find( 
            actual.name, 
            actual.name + sizeof( actual.name ),
            '\0' 
        );
        auto actual_name = std::string{ actual.name, end };

        auto expected_name = std::string{ "Austin Donovan" };

        REQUIRE( actual_name == expected_name );
        REQUIRE( actual.balance == 500.0f );
        REQUIRE( actual.count == 11 );
        REQUIRE( actual.A == net::Action::hitting );
    }

    SECTION( "A player's bet should be forfeited on a loss" )
    {
        uc::Player player;
        player.bet( 20 );
        player.on_lose();
        REQUIRE( player.bet() == 0 );
        REQUIRE( ( int ) player.balance() == 180 );
    }

    SECTION( "A player's bet should be returned two fold on a win" )
    {
        uc::Player player;
        player.bet( 20 );
        player.on_win();
        REQUIRE( player.bet() == 0 );
        REQUIRE( ( int ) player.balance() == 220 );
    }

    SECTION( "A player's bet should be returned on a tie" )
    {
        uc::Player player;
        player.bet( 20 );
        player.on_tie();
        REQUIRE( player.bet() == 0 );
        REQUIRE( ( int ) player.balance() == 200 );
    }
}

