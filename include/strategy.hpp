#ifndef __STRATEGY_HPP__
#define __STRATEGY_HPP__

#include <UberCasino.h>
#include "types.inl"

namespace uc
{
    /**
     * A pure virtual class describing what a strategy should do.
     */
    class Strategy
    {

    public:
        /**
         * Processes the given state of the `game`, and determines which
         * action the user with the given `uuid` should perform.
         */
        virtual net::Action process( const char* uuid, const net::Game& game) const = 0;
    };

    /**
     * A strategy where the user will *always* hit.
     */
    class RecklessStrategy : public Strategy
    {
        net::Action process( const char* uuid, const net::Game& game) const;
    };

    /**
     * A strategy where the user will only hit if they can't *possibly*
     * bust.
     */
    class ConservativeStrategy : public Strategy
    {
        net::Action process( const char* uuid, const net::Game& game) const;
    };

    /**
     * A strategy which employs so-called "basic blacjack strategy".
     */
    class BasicStrategy : public Strategy
    {
        net::Action process( const char* uuid, const net::Game& game) const;
    };

    /**
     * A strategy which will always return 'idle', signaling to the
     * window that it needs to wait for one of its buttons to receive
     * a callback instead.
     */
    class ManualStrategy : public Strategy
    {
        net::Action process( const char* uuid, const net::Game& game) const;
    };
}

#endif // __STRATEGY_HPP__
