#include <strategy.hpp>

namespace uc
{

    net::Action
    RecklessStrategy::process( const net::Game& game ) const
    {
        // hide unused parameter warnings
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
    ConservativeStrategy::process( const net::Game& game ) const
    {
        // TODO actual implementation
        ( void )( game );

        return net::Action::standing;
    }

    net::Action
    BasicStrategy::process( const net::Game& game ) const
    {
        // TODO actual implementation
        ( void )( game );

        return net::Action::standing;
    }

}
