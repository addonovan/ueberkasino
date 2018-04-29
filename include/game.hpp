#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <boost/thread.hpp>
#include <mutex>

#include <UberCasino.h>
#include "player.hpp"
#include "types.inl"

namespace uc
{

    enum class GameState
    {
        SearchingForGame,
        JoiningGame,
        WaitingForStart,
        WaitingForTurn,
        Playing,
        HandOver,
    };

    typedef std::chrono::steady_clock::time_point TimePoint;

    class Game
    {

        //
        // Members
        //

    private:

        std::mutex m_state_mtx;
        GameState m_state;

        Player m_player; 

        std::mutex m_partial_response_mtx;
        net::Player* m_partial_response = nullptr;

        std::mutex m_last_response_mtx;
        TimePoint m_last_response;

        //
        // Constructors
        //

    public:

        Game();

    private:

        void delay_timeout();

        //
        // Accessor functions
        //

    public:

        const Player& player() const;

        //
        // Callbacks, both UI and Network
        //
    
    public:

        void on_game_update( net::Game game );

        void on_dealer_update( net::Dealer dealer );

        template< class T >
        void on_strategy_changed( T* strategy )
        {
            m_player.strategy( strategy );
        }

        void on_bet_changed( int difference );

        void on_action_picked( net::Action action );

        //
        // State Handlers
        //
   
    private:

        void on_join_game( net::Game game );

        void on_waiting_for_start( net::Game game );

        void on_waiting_for_turn( net::Game game );

        void on_playing( net::Game game );

        void on_hand_over( net::Game game );

        void transition( GameState tag );

        void on_timeout();

    };

}

#endif // __GAME_HPP__

