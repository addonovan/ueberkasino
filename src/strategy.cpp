#include <strategy.hpp>
#include <misc.hpp>

namespace uc
{

    net::Action
    RecklessStrategy::process( const net::Game& game ) const
    {
        ( void )( game );
        return net::Action::hitting;
    }

    net::Action
    ManualStrategy::process( const net::Game& game ) const
    {
        ( void )( game );
        return net::Action::idle;
    }
    
    net::Action
    BasicStrategy::process( const net::Game& game ) const
    {
        // trying to cut out as much boilerplate as possible here, just to make
        // the chart easier to read/understand
        using std::array;
        using net::Action;
#define H Action::hitting
#define S Action::standing
#define D Action::doubling

        // the constant lookup table describing what action should be performed
        static const array< array< Action, 10 >, 19 > lookup = {{
            // Dealer's Visibile Count           Player's Count
            //2  3  4  5  6  7  8  9  10 A       ==============
            { H, H, H, H, H, H, H, H, H, H }, // 2
            { H, H, H, H, H, H, H, H, H, H }, // 3
            { H, H, H, H, H, H, H, H, H, H }, // 4
            { H, H, H, H, H, H, H, H, H, H }, // 5
            { H, H, H, H, H, H, H, H, H, H }, // 6
            { H, H, H, H, H, H, H, H, H, H }, // 7
            { H, H, H, H, H, H, H, H, H, H }, // 8
            { H, D, D, D, D, H, H, H, H, H }, // 9
            { D, D, D, D, D, D, D, D, H, H }, // 10
            { D, D, D, D, D, D, D, D, D, D }, // 11
            { H, H, S, S, S, H, H, H, H, H }, // 12
            { S, S, S, S, S, H, H, H, H, H }, // 13
            { S, S, S, S, S, H, H, H, H, H }, // 14
            { S, S, S, S, S, H, H, H, H, H }, // 15
            { S, S, S, S, S, H, H, H, H, H }, // 16
            { S, S, S, S, S, H, H, H, H, H }, // 17
            { S, S, S, S, S, S, S, S, S, S }, // 18
            { S, S, S, S, S, S, S, S, S, S }, // 19
            { S, S, S, S, S, S, S, S, S, S }  // 20
        }};

#undef D
#undef S
#undef H

        // calculate the player's count
        auto player = value_of( to_hand( game.p[ game.active_player ].cards ) );
        auto dealer = value_of( to_hand( game.dealer_cards ) );

        // because both the player and dealer's counts can start at a min of 2,
        // we need to subtract 2 to get to the first position
        player -= 2;
        dealer -= 2;

        // opting to use `at( index )` instead of `[ index ]` here because it
        // will do bounds checking for us, ensuring that nothing funky went on
        return lookup.at( player ).at( dealer );
    }

    net::Action
    ConservativeStrategy::process( const net::Game& game ) const
    {
        auto count = value_of( to_hand( game.p[ game.active_player ].cards ) );

        // if we could bust by getting a ten-point-card, then we won't ever hit,
        // we can safely disregard and eleven-valued-ace in this case because if
        // that were to cause us to bust, then it'd be valued at a 1 instead.
        if ( count + 10 > 21 )
        {
            return net::Action::standing;
        }
        else
        {
            return net::Action::hitting;
        }
    }

}
