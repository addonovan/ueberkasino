#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <string>

#include <UberCasino.h>
#include "types.inl"

namespace uc
{

    /**
     * Converts the given hand of `cards` into a string.
     */
    std::string to_string( const net::Card cards[ net::MAX_CARDS ] );

    /**
     * Converts the given `suit` into a string.
     */
    std::string to_string( net::Suit suit );

    /**
     * Converst the given card value/`kind` into a string.
     */
    std::string to_string( net::CardKind kind );

}

#endif // __MISC_HPP__
