#include <cstdlib>
#include <iostream>

#include <game.hpp>
#include <UberCasino.h>
#include <types.inl>
#include <strategy.hpp>
#include <misc.hpp>

#include "catch.hpp"
#include "helpers.hpp"

using namespace uc;

//
// Test Cases
//

TEST_CASE( "Game State Machine" )
{
    SECTION( "Joins first game found" )
    {
        Game game1;
        Game game2;
        net::Game game;
        join_game( game1, game2, game );

        // require that both players are in a game and no cards have been dealt
        REQUIRE( game1.in_game() == true );
        REQUIRE( game2.in_game() == true );

        REQUIRE( game1.cards_dealt() == false );
        REQUIRE( game2.cards_dealt() == false );
    }

    SECTION( "Reports when cards have been dealt" )
    {
        // both should be in the WaitingForStart state, so we need to transition
        // them into the WaitingForTurn state, by sending the "game started"
        // signal
        Game game1;
        Game game2;
        net::Game game;
        join_game( game1, game2, game );
        deal_20s( game1, game2, game );
        
        REQUIRE( game1.cards_dealt() == true );
        REQUIRE( game2.cards_dealt() == true );
    }

    SECTION( "Tracks cards of other player(s)" )
    {
        Game game1;
        Game game2;
        net::Game game;
        join_game( game1, game2, game );
        deal_20s( game1, game2, game );

        // hand2 is the hand of the 2nd player, not the first, which is
        // why the numbers for the hands and games appear mismatched
        auto hand2 = game1.hands().at( 0 );
        auto hand1 = game2.hands().at( 0 );

        REQUIRE( hand1[ 0 ].valid == true );
        REQUIRE( hand2[ 0 ].valid == true );

        REQUIRE( hand1[ 0 ].card == net::CardKind::king );
        REQUIRE( hand2[ 0 ].card == net::CardKind::king );

        REQUIRE( hand1[ 0 ].suite == net::Suit::spades );
        REQUIRE( hand2[ 0 ].suite == net::Suit::spades );

        REQUIRE( hand1[ 1 ].valid == true );
        REQUIRE( hand2[ 1 ].valid == true );

        REQUIRE( hand1[ 1 ].card == net::CardKind::queen );
        REQUIRE( hand2[ 1 ].card == net::CardKind::queen );

        REQUIRE( hand1[ 1 ].suite == net::Suit::hearts );
        REQUIRE( hand2[ 1 ].suite == net::Suit::hearts );
    }

    SECTION( "Tracks cards of dealer" )
    {
        Game game1;
        Game game2;
        net::Game game = create_game();
        join_game( game1, game2, game );
        deal_20s( game1, game2, game );

        auto dealer = game1.hands().at( -1 );

        REQUIRE( dealer[ 0 ].valid == false );

        REQUIRE( dealer[ 1 ].valid == true );
        REQUIRE( dealer[ 1 ].card == net::CardKind::ten );
        REQUIRE( dealer[ 1 ].suite == net::Suit::diamonds );
    }

    SECTION( "Stays seated at table after a single hand is over" )
    {
        Game game1;
        Game game2;
        net::Game game = create_game();
        join_game( game1, game2, game );
        deal_20s( game1, game2, game );
        end_game( game1, game2, game );

        REQUIRE( game1.in_game() == true );
        REQUIRE( game2.in_game() == true );
        
        REQUIRE( game1.cards_dealt() == true );
        REQUIRE( game2.cards_dealt() == true );
    }

    SECTION( "Will immediately stand if dealt a blackjack" )
    {
        Game game1, game2;
        net::Game game = create_game();
        game1.on_bet_changed( 20 );
        join_game( game1, game2, game );
        deal_blackjack( game1, game2, game );
        end_game( game1, game2, game );

        // the player should immediately win, so their bet should be refunded
        // to them and they should also get paid back
        REQUIRE( ( int ) game1.player().balance() == 220 );
        REQUIRE( game1.player().bet() == 0 );
    }

    SECTION( "Will immediately stand if dealt a busted hand" )
    {
        Game game1, game2;
        net::Game game = create_game();
        game1.on_bet_changed( 20 );
        join_game( game1, game2, game );
        deal_bust( game1, game2, game );
        end_game( game1, game2, game );

        // the player should immediately lose, so their bet should be taken 
        REQUIRE( ( int ) game1.player().balance() == 180 );
        REQUIRE( game1.player().bet() == 0 );
    }
}

