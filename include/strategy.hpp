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
        virtual net::Action process( const char* uuid, const net::Game& game ) const = 0;
    };

    /**
     * A strategy where the user will *always* hit.
     */
    class RecklessStrategy : public Strategy
    {
        /**
         * Ignores both `uuid` and the current state of the `game` and ALWAYS
         * hits.
         */
        net::Action process( const char* uuid, const net::Game& game ) const;
    };

    /**
     * A strategy where the user will only hit if they can't *possibly*
     * bust.
     */
    class ConservativeStrategy : public Strategy
    {
        /**
         * Uses the player's `uuid` to determine their cards in the current
         * `game` and will hit ONLY if there is NO possibility of ever busting.
         */
        net::Action process( const char* uuid, const net::Game& game ) const;
    };

    /**
     * A strategy which employs so-called "basic blacjack strategy".
     */
    class BasicStrategy : public Strategy
    {
        /**
         * Uses the current state of the game along with the current player's
         * hand to determine what action to do next. This will emply so-called
         * "basic blackjack strategy" in the form of a look-up table to perform
         * the most "optimal" move on average.
         */
        net::Action process( const char* uuid, const net::Game& game ) const;
    };

    /**
     * A strategy which will always return 'idle', signaling to the
     * window that it needs to wait for one of its buttons to receive
     * a callback instead.
     */
    class ManualStrategy : public Strategy
    {
        /**
         * Will always completely ignore the `uuid` and `game` parameters and
         * simply return `net::Action::idle` to signify to the UI and Game
         * state machine that manual intervention is needed to complete a
         * turn.
         */
        net::Action process( const char* uuid, const net::Game& game ) const;
    };
}

#endif // __STRATEGY_HPP__
