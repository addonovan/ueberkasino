#ifndef __GAME_HPP__
#define __GAME_HPP__

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

    class Game
    {

        //
        // Members
        //

    private:

        GameState m_state;

        Player m_player; 

        net::Player* m_partial_response = nullptr;

        //
        // Constructors
        //

    public:

        Game();

        //
        // Accessor functions
        //

    public:

        const Player& player() const;

    public:

        //
        // Callbacks, both UI and Network
        //

        void on_game_update( net::Game game );

        void on_dealer_update( net::Dealer dealer );

        template< class T >
        void on_strategy_changed( T* strategy )
        {
            m_player.strategy( strategy );
        }

        void on_bet_changed( int difference );

        void on_action_picked( net::Action action );

    private:

        bool check_join_game( net::Game game );

        void transition( GameState tag );

    };

}

#endif // __GAME_HPP__

