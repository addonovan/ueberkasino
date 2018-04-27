#ifndef __MISC_HPP__
#define __MISC_HPP__

#include <string>
#include <UberCasino.h>
#include "types.inl"

namespace uc
{

    std::string to_string( const net::Card cards[ net::MAX_CARDS ] );

    std::string to_string( net::Suit suit );

    std::string to_string( net::CardKind kind );

}

#endif // __MISC_HPP__
