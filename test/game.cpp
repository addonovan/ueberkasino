#include <network.hpp>
#include <game.hpp>
#include <strategy.hpp>
#include <misc.hpp>

int main()
{
    uc::Game uc_game;
    uc_game.on_strategy_changed( new uc::RecklessStrategy );

    uc::Network::get().on_game_update( [ &uc_game ]( net::Game game ) {
        uc_game.on_game_update( game );
      
        if ( !uc_game.in_game() )
            return;

        const auto& hands = uc_game.hands();     

        // print out all of the cards
        for ( const auto& hand : hands )
        {
            std::cout << hand.first << ": " 
                << uc::to_string( hand.second ) << std::endl;
        }

        std::cout << "us: " 
            << uc::to_string( uc_game.player().hand() ) << std::endl;
    } );

    uc::Network::get().on_dealer_update( [ &uc_game ]( net::Dealer dealer ) {
        uc_game.on_dealer_update( dealer );
    } );

    // block and let everything work itself out
    while ( true );
}

