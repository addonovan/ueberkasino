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
    std::string to_string( const net::Hand& hand );

    /**
     * Converts the given `suit` into a string.
     */
    std::string to_string( net::Suit suit );

    /**
     * Converts the given card value/`kind` into a string.
     */
    std::string to_string( net::CardKind kind );

    /**
     * Converts the given raw C array of cards into a Hand. 
     */
    net::Hand to_hand( const net::Card cards[ net::MAX_CARDS ] );

    /**
     * Takes the value of the given hand.
     */
    unsigned int value_of( const net::Hand& hand );

    /**
     * Checks if the given `card` is actually valid or not.
     */
    bool is_valid( const net::Card& card );

}

#endif // __MISC_HPP__
