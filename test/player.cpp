#include <UberCasino.h>
#include <player.hpp>
#include <types.inl>

#include "catch.hpp"


TEST_CASE( "A default player must have certain values" )
{
    uc::Player def;
    SECTION( "The balance of a default player is $200.0" )
    {
        REQUIRE( ( def.balance() ) == 200.0f );
    }

    SECTION( "The default player will bet $0" )
    {
        REQUIRE( ( def.bet() ) ) == 0 );
    }
}
