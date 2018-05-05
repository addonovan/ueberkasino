#ifndef __HELPERS_HPP__
#define __HELPERS_HPP__

#include <game.hpp>
#include <UberCasino.h>
#include <types.inl>
#include <strategy.hpp>
#include <misc.hpp>

using namespace uc;

#define DEALER_UID  "testdealer"
#define DEALER_NAME "testdealer"
#define GAME_UID    "testgame"

#define COPY_STRING( dst, src )\
    memset( dst, 0, sizeof( src ) );\
    memcpy( dst, src, sizeof( src ) );

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
void deal_20s( Game& game1, Game& game2, net::Game& game );

void deal_12s( Game& game1, Game& game2, net::Game& game );

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

#endif

