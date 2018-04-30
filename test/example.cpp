#include "catch.hpp"

bool is_true( bool val )
{
    return val == true;
}

TEST_CASE( "is_true computes true truthfully", "[example/is_true]" )
{
    REQUIRE( is_true( true ) == true );
    REQUIRE( is_true( false ) == false );
}

