#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <boost/thread.hpp>
#include <mutex>
#include <map>

#include <UberCasino.h>
#include "player.hpp"
#include "types.inl"

namespace uc
{

    /**
     * The states which this game can be in at any point in
     * a game's lifecycle.
     */
    enum class GameState
    {
        /** Not currently in a game, but looking for one. */
        SearchingForGame,

        /** Found a game, but haven't been confirmed as a player yet. */
        JoiningGame,

        /** In a game, but waiting for it to start. */
        WaitingForStart,

        /** In a game, but waiting for our turn to come. */
        WaitingForTurn,

        /** In a game, and its our turn to play */
        Playing,

        /** In a game, but it's still going and we've either busted or stood */
        Standing,

        /** We were in a game, but it just ended */
        HandOver,
    };

    /** A point in time using the steady clock interface. */
    typedef std::chrono::steady_clock::time_point TimePoint;

    /**
     * A simple state machine which will react to all network
     * events and UI events in a safe manner, while also providing
     * access to things such as the player and the state of the game.
     */
    class Game
    {

        //
        // Members
        //

    private:

        /** Mutex for `m_state`. */
        std::mutex m_state_mtx;

        /** The current state of the game. */
        GameState m_state;

        /** Mutex for `m_player`. */
        std::mutex m_player_mtx;

        /** The player in this game. */
        Player m_player; 

        /** Mutex for `m_partial_response`. */
        std::mutex m_partial_response_mtx;

        /**
         * A partial response from the player.
         *
         * This can happen if the player's strategy is set to manual,
         * so the majority of the player's state information needs to
         * be saved off to be sent via OSPL later, after the an action
         * is chosen.
         */
        net::Player* m_partial_response = nullptr;

        /** Mutex for `m_last_response`. */
        std::mutex m_last_response_mtx;

        /** The last time we sent or received an even about the game. */
        TimePoint m_last_response;

        /** The index in the game structure that our player appears in. */
        long int m_player_index;

        /**
         * Map of hands in the game, the key is the index of the player in
         * the game structure.
         *
         * The dealer's hand is kept at the special index -1, and the hand
         * kept by `m_player` is ignored entirely, and the index is skipped.
         */
        std::map< long int, net::Hand > m_hands;

        //
        // Constructors
        //

    public:

        /**
         * Constructs a new game which will be in the 
         * `GameState::SearchingForGame` state by default, until it receives
         * the simuli required to play the game.
         */
        Game();

        //
        // Miscellaneous Helper Methods
        //

    private:

        /**
         * Delays the timeout operation.
         *
         * This is used every time we send or receive a stimulus relating to
         * the game we're currently in.
         */
        void delay_timeout();

        /**
         * Records the hands of all players in the `game`, whose cards
         * are currently visible.
         */
        void record_hands( const net::Game& game );

        //
        // Accessor functions
        //

    public:

        /**
         * Returns a constant reference to this game's player.
         */
        const Player& player() const;

        /**
         * Returns a constant reference to all of the known hands in this
         * game, excluding the player's own, which can be accessed via the
         * `player()` call.
         *
         * The indices are guaranteed to be continuous (i.e. that there won't
         * be an index 4 without indices 0, 1, 2, and 3), even if this game's
         * player comes within the range [0, i].
         *
         * The dealer's hand will be a special case, and is stored with the
         * related key of `-1`.
         */
        const std::map< long int, net::Hand >& hands() const;

        /**
         * Tests whether the game is currently at a table and playing or not.
         */
        bool in_game() const;

        /**
         * Tests whether the game the player is in (if any) has dealt cards.
         */
        bool cards_dealt() const;

        //
        // Callbacks, both UI and Network
        //
    
    public:

        /**
         * (Network) callback for when a `game` event is received.
         */
        void on_game_update( net::Game game );

        /**
         * (Network) callback for when a `dealer` event is received.
         */
        void on_dealer_update( net::Dealer dealer );

        /**
         * (UI) callback which will change the player's `strategy` for playing
         * the game.
         */
        template< class T >
        void on_strategy_changed( T* strategy )
        {
            m_player.strategy( strategy );
        }

        /**
         * Changes the bet by adding the given `difference`.
         */
        void on_bet_changed( int difference );

        /**
         * Chooses the `action` for the user to send if the current strategy
         * allows for the user to do so.
         */
        void on_action_picked( net::Action action );

        //
        // State Handlers
        //
   
    private:

        /**
         * Checks to see if the dealer of the game we joined has accepted us.
         *
         * Transitions:
         * * => WaitingForStart, if the dealer accepted us
         * * => SearchingForGame, otherwise
         */
        void on_join_game( net::Game game );

        /**
         * Waits for the game to start.
         *
         * Transitions:
         * * => WaitingForTurn, when the game starts 
         */
        void on_waiting_for_start( net::Game game );

        /**
         * Waits for our turn to begin, and saves off all of the information
         * for other players.
         *
         * Transitions:
         * * => HandOver, when the game is over
         * * => Playing, when we're the active player
         * * => Standing, when we've busted or stood
         */
        void on_waiting_for_turn( net::Game game );

        /**
         * Lets the `player` decide what action to perform, then publishes
         * the changes.
         *
         * Transitions:
         * * => HandOver, when the game is over
         * * => Playing, when the strategy is set to manual
         * * => WaitingForTurn, otherwise
         */
        void on_playing( net::Game game );

        /**
         * Lets the game enter a sink state while the game is still going on
         * for other players, but this player has either busted or stood
         *
         * Transitions:
         * * => HandOver, when the game is over
         * * => Standing, otherwise
         */
        void on_standing( net::Game game );

        /**
         * Ends the current game and leaves the dealer's lobby.
         *
         * Transitions:
         * * => SearchingForGame
         */
        void on_hand_over();

        /**
         * Safely transitions into the new `state`.
         *
         * This will also log the transition information when compiled
         * under `DEBUG` mode.
         */
        void transition( GameState state );

        /**
         * Called when a game times out.
         *
         * This will also log the timeout when compiled under `DEBUG` mode.
         *
         * Transitions:
         * * => HandOver
         */
        void on_timeout();

    };

}

#endif // __GAME_HPP__

