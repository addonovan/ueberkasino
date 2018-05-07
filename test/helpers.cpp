#include "helpers.hpp"

#define CARD( game, pos, value, suit )\
    ( game ).p[ 0 ].cards[ pos ].valid = true;\
    ( game ).p[ 0 ].cards[ pos ].card = net::CardKind::value;\
    ( game ).p[ 0 ].cards[ pos ].suite = net::Suit::suit\

#define DEALER_CARD( game, pos, value, suit )\
    ( game ).dealer_cards[ pos ].valid = true;\
    ( game ).dealer_cards[ pos ].card = net::CardKind::value;\
    ( game ).dealer_cards[ pos ].suite = net::Suit::suit\

#define RESET_GAME( game )\
    memset( game.p[ 0 ].cards, 0, sizeof( game.p[ 0 ].cards ) );\
    memset( game.dealer_cards, 0, sizeof( game.dealer_cards ) );

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
    game.active_player = 0;
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
deal_20s( Game& game1, Game& game2, net::Game& game )
{
    game.gstate = net::GameState::playing;

    game.p[ 0 ].cards[ 0 ] = game.p[ 1 ].cards[ 0 ] = net::Card {
        .card = net::CardKind::king,
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 1 ] = game.p[ 1 ].cards[ 1 ] = net::Card {
        .card = net::CardKind::queen,
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
deal_12s( Game& game1, Game& game2, net::Game& game )
{
    game.gstate = net::GameState::playing;

    game.p[ 0 ].cards[ 0 ] = game.p[ 1 ].cards[ 0 ] = net::Card {
        .card = net::CardKind::king,
        .suite = net::Suit::spades,
        .valid = true
    };
    game.p[ 0 ].cards[ 1 ] = game.p[ 1 ].cards[ 1 ] = net::Card {
        .card = net::CardKind::two,
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
net::Game
gen_pl_grt11_dl_grt6()
{
    auto game = create_game();
    RESET_GAME( game );
    CARD( game, 0, seven, diamonds );
    CARD( game, 1, ten, diamonds );
    DEALER_CARD( game, 0, seven, diamonds );
    return game;
}

net::Game
gen_pl_grt11_dl_lte6( int i )
{
    auto game = create_game();
    RESET_GAME( game );

    switch ( i )
    {
        case 0:
            CARD( game, 0, six, diamonds );
            CARD( game, 1, ten, diamonds );
            DEALER_CARD( game, 0, six, diamonds );
            break;

        case 1:
            CARD( game, 0, five, diamonds );
            CARD( game, 1, ten, diamonds );
            DEALER_CARD( game, 0, five, diamonds );
            break;
    }

    return game;
}

net::Game
gen_pl_grt11_dl_ace()
{
    auto game = create_game();
    RESET_GAME( game );
    CARD( game, 0, seven, diamonds );
    CARD( game, 1, ten, diamonds );
    DEALER_CARD( game, 0, ace, spades );
    return game;
}

net::Game
gen_pl_lte11_dl_grt6( int i )
{
    auto game = create_game();
    RESET_GAME( game );
    switch ( i )
    {
        case 0:
            CARD( game, 0, six, diamonds );
            CARD( game, 1, five, diamonds );
            DEALER_CARD( game, 0, seven, diamonds );
            break;

        case 1:
            CARD( game, 0, seven, diamonds );
            DEALER_CARD( game, 0, seven, diamonds );
            break;
    }
    return game;
}

net::Game
gen_pl_lte11_dl_lte6( int i )
{
    auto game = create_game();
    RESET_GAME( game );

    switch ( i )
    {
        case 0:
            CARD( game, 0, six, diamonds );
            CARD( game, 1, five, diamonds );
            DEALER_CARD( game, 1, six, diamonds );
            break;

        case 1:
            CARD( game, 0, seven, diamonds );
            DEALER_CARD( game, 1, six, diamonds );
            break;

        case 2:
            CARD( game, 0, five, diamonds );
            CARD( game, 1, six, diamonds );
            DEALER_CARD( game, 1, five, diamonds );
            break;

        case 3:
            CARD( game, 0, five, diamonds );
            DEALER_CARD( game, 1, five, diamonds );
            break;
    }
    return game;
}

net::Game
gen_pl_lte11_dl_ace( int i )
{
    auto game = create_game();
    RESET_GAME( game );
    switch ( i )
    {
        case 0:
            CARD( game, 0, seven, diamonds );
            CARD( game, 1, four, diamonds );
            DEALER_CARD( game, 1, ace, diamonds );
            break;

        case 1:
            CARD( game, 0, seven, diamonds );
            DEALER_CARD( game, 1, ace, diamonds );
            break;
    }
    return game;
}

net::Game
gen_pl_blj_dl_grt6()
{
    auto game = create_game();
    RESET_GAME( game );
    CARD( game, 0, ace, diamonds );
    CARD( game, 1, jack, diamonds );
    DEALER_CARD( game, 1, seven, diamonds );
    return game;
}

net::Game
gen_pl_blj_dl_lte6( int i )
{
    auto game = create_game();
    RESET_GAME( game );
    switch ( i )
    {
        case 0:
            CARD( game, 0, jack, diamonds );
            CARD( game, 1, ace, diamonds );
            DEALER_CARD( game, 1, six, diamonds );
            break;

        case 1:
            CARD( game, 0, jack, diamonds );
            CARD( game, 1, ace, diamonds );
            DEALER_CARD( game, 1, five, diamonds );
            break;
    }
    return game;
}

net::Game
gen_pl_blj_dl_ace()
{
    auto game = create_game();
    CARD( game, 0, jack, diamonds );
    CARD( game, 1, ace, diamonds );
    DEALER_CARD( game, 1, ace, diamonds );
    return game;
}
