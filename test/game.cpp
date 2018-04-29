#include <network.hpp>
#include <game.hpp>
#include <strategy.hpp>

int main()
{
    uc::Game uc_game;
    uc_game.on_strategy_changed( new uc::RecklessStrategy );

    uc::Network::get().on_game_update( [ &uc_game ]( net::Game game ) {
        uc_game.on_game_update( game );
    } );

    uc::Network::get().on_dealer_update( [ &uc_game ]( net::Dealer dealer ) {
        uc_game.on_dealer_update( dealer );
    } );

    // block and let everything work itself out
    while ( true );
}

