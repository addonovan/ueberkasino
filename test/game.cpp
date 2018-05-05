#include <cstdlib>
#include <iostream>

#include <game.hpp>
#include <UberCasino.h>
#include <types.inl>
#include <strategy.hpp>
#include <misc.hpp>

#include "catch.hpp"

#define DEALER_UID  "testdealer"
#define DEALER_NAME "testdealer"
#define GAME_UID    "testgame"

#define COPY_STRING( dst, src )\
    memset( dst, 0, sizeof( src ) );\
    memcpy( dst, src, sizeof( src ) );

using namespace uc;

//
// Helper Methods
//

// These only exist because the games are state machines which require
// a lot of set-up to get to a new test the further along the line the
// process a test tests. These are the actual blocks of code being tested,
// but they just need to be reused a lot.

/**
 * Forces both players represented by `game1` and `game1` to join the
 * `game` table.
 */
void join_game( Game& game1, Game& game2, net::Game& game );

/**
 * If `turn == 1`, then both players will be dealt two cards worth a value
 * of ten total.
 *
 * Otherwise, they will be dealt two aces.
 */
void deal_20s( Game& game1, Game& game2, net::Game& game, int turn = 1 );

void deal_blackjack( Game& game1, Game& game2, net::Game& game );

void deal_bust( Game& game1, Game& game2, net::Game& game );

/**
 * Ends the game between the two players.
 */
void end_game( Game& game1, Game& game2, net::Game& game );

/**
 * Creates a dealer with the configured DEALER_UID and DEALER_NAME, hosting
 * a game with the configured GAME-UID.
 */
net::Dealer create_dealer();

/**
 * Creates a game with the configured GAME_UID in the default game state.
 */
net::Game create_game();

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

        REQUIRE( value_of( game1.player().hand() ) == 20 );
        REQUIRE( value_of( game2.player().hand() ) == 20 );

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

    SECTION( "Can immediately begin to play another hand" )
    {
        Game game1, game2;
        net::Game game = create_game();
        join_game( game1, game2, game );
        deal_20s( game1, game2, game );
        end_game( game1, game2, game );
        
        // deal different cards, (as they are WaitingForStart at this point)
        deal_20s( game1, game2, game, 2 );

        auto hand1 = game1.player().hand();
        auto hand2 = game2.player().hand();

        REQUIRE( value_of( hand1 ) == 12 );
        REQUIRE( value_of( hand2 ) == 12 );

        // now, check each player's record of the OTHER player's hand
        hand2 = game1.hands().at( 0 );
        hand1 = game2.hands().at( 0 );

        REQUIRE( value_of( hand1 ) == 12 );
        REQUIRE( value_of( hand2 ) == 12 );
    }
}

//
// Implementation of Helper Methods
//

net::Dealer 
create_dealer()
{
    net::Dealer dealer;
    COPY_STRING( &dealer.name, DEALER_NAME );
    COPY_STRING( &dealer.uid, DEALER_UID );
    COPY_STRING( &dealer.game_uid, GAME_UID );
    return dealer;
}

net::Game 
create_game()
{
    net::Game game;
    COPY_STRING( &game.game_uid, GAME_UID );
    COPY_STRING( &game.dealer_uid, DEALER_UID );
    game.gstate = net::GameState::waiting_to_join;
    return game;
}

void 
join_game( Game& game1, Game& game2, net::Game& game )
{
    game1.on_strategy_changed( new RecklessStrategy );
    game2.on_strategy_changed( new RecklessStrategy );

    // make sure the game sees the new dealer, and it should
    // automatically try to join after that
    auto dealer = create_dealer();
    game1.on_dealer_update( dealer );
    game2.on_dealer_update( dealer );

    // now we make a game structure and add the player's UID to that
    auto player1 = game1.player().to();
    auto player2 = game2.player().to();

    // add all players to the game
    game = create_game();
    memcpy( &game.p[ 0 ].uid, &player1.uid, net::UUID_LENGTH );
    memcpy( &game.p[ 1 ].uid, &player2.uid, net::UUID_LENGTH );
    game1.on_game_update( game );
    game2.on_game_update( game );
}

void
deal_blackjack( Game& game1, Game& game2, net::Game& game )
{
    game.gstate = net::GameState::playing;

    game.p[ 0 ].cards[ 0 ] = game.p[ 1 ].cards[ 0 ] = net::Card {
        .card = net::CardKind::ace,
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 1 ] = game.p[ 1 ].cards[ 1 ] = net::Card {
        .card = net::CardKind::jack,
        .suite = net::Suit::hearts,
        .valid = true
    };

    game.dealer_cards[ 0 ] = net::Card {
        .card = net::CardKind::two,
        .suite = net::Suit::clubs,
        .valid = false
    };
    game.dealer_cards[ 1 ] = net::Card {
        .card = net::CardKind::ten,
        .suite = net::Suit::diamonds,
        .valid = true
    };

    game.active_player = 1;
    game1.on_game_update( game );

    game.active_player = 0;
    game2.on_game_update( game );
}

void 
deal_20s( Game& game1, Game& game2, net::Game& game, int turn )
{
    game.gstate = net::GameState::playing;

    game.p[ 0 ].cards[ 0 ] = game.p[ 1 ].cards[ 0 ] = net::Card {
        .card = ( turn == 1 ? net::CardKind::king : net::CardKind::ace ),
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 1 ] = game.p[ 1 ].cards[ 1 ] = net::Card {
        .card = ( turn == 1 ? net::CardKind::queen : net::CardKind::ace ),
        .suite = net::Suit::hearts,
        .valid = true
    };

    game.dealer_cards[ 0 ] = net::Card {
        .card = net::CardKind::two,
        .suite = net::Suit::clubs,
        .valid = false
    };
    game.dealer_cards[ 1 ] = net::Card {
        .card = net::CardKind::ten,
        .suite = net::Suit::diamonds,
        .valid = true
    };

    game.active_player = 1;
    game1.on_game_update( game );

    game.active_player = 0;
    game2.on_game_update( game );
}

void 
deal_bust( Game& game1, Game& game2, net::Game& game )
{
    game.gstate = net::GameState::playing;

    game.p[ 0 ].cards[ 0 ] = game.p[ 1 ].cards[ 0 ] = net::Card {
        .card = net::CardKind::king,
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 1 ] = game.p[ 1 ].cards[ 1 ] = net::Card {
        .card = net::CardKind::king,
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 2 ] = game.p[ 1 ].cards[ 2 ] = net::Card {
        .card = net::CardKind::king,
        .suite = net::Suit::spades,
        .valid = true
    };

    game.dealer_cards[ 0 ] = net::Card {
        .card = net::CardKind::two,
        .suite = net::Suit::clubs,
        .valid = false
    };
    game.dealer_cards[ 1 ] = net::Card {
        .card = net::CardKind::ten,
        .suite = net::Suit::diamonds,
        .valid = true
    };

    game.active_player = 1;
    game1.on_game_update( game );

    game.active_player = 0;
    game2.on_game_update( game );
}

void 
end_game( Game& game1, Game& game2, net::Game& game )
{
    game.gstate = net::GameState::end_hand;
    game.dealer_cards[ 0 ].valid = true;

    game1.on_game_update( game );
    game2.on_game_update( game );
}

