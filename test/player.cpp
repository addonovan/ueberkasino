#include <UberCasino.h>
#include <player.hpp>
#include <misc.hpp>
#include <types.inl>

#include "catch.hpp"


TEST_CASE( "A default player must have certain values" )
{
    uc::Player def;
    SECTION( "The balance of a default player is $200.0" )
    {
        REQUIRE( def.balance() == 200.0f );
    }

    SECTION( "The default player will bet $0" )
    {
        REQUIRE( def.bet() == 0 );
    }

    SECTION( "The default player will not be in a game" )
    {
        REQUIRE( def.game() == nullptr );
    }

    SECTION( "The default player must have an empty hand" )
    {
        REQUIRE(  def.hand()[ 0 ].suite  == (net::Suit) 0 );
        REQUIRE(  def.hand()[ 0 ].card  == (net::CardKind) 0);
        REQUIRE(  def.hand()[ 0 ].valid == false );
    }

}
