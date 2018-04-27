#include <strategy.hpp>

namespace uc
{

    net::Action
    RecklessStrategy::process( const char* uuid, const net::Game& game ) const
    {
        // hide unused parameter warnings
        ( void )( uuid );
        ( void )( game );

        return net::Action::hitting;
    }

    net::Action
    ManualStrategy::process( const char* uuid, const net::Game& game ) const
    {
        ( void )( uuid );
        ( void )( game );

        return net::Action::idle;
    }

    net::Action
    ConservativeStrategy::process( const char* uuid, const net::Game& game ) const
    {
        // TODO actual implementation
        ( void )( uuid );
        ( void )( game );

        return net::Action::standing;
    }

    net::Action
    BasicStrategy::process( const char* uuid, const net::Game& game ) const
    {
        // TODO actual implementation
        ( void )( uuid );
        ( void )( game );

        return net::Action::standing;
    }

}
