#include <game_window.hpp>
#include <network.hpp>
#include <misc.hpp>
#include <cstring>

//
// Global, Constant Style Table
//

namespace uc
{

    GameWindow::GameWindow()
    {
        static GameWindow* self = this;

        m_window.begin();
        m_window.color( 0x00500000 );

        m_box->box( FL_NO_BOX );
        m_box->labelfont( FL_BOLD + FL_HELVETICA );
        m_box->labelsize( 30 );
        m_box->labeltype( FL_SHADOW_LABEL );

        //
        // Create the Hit, Stand, Double Down buttons
        //

#define CREATE_ACTION_BUTTON( button_name, cb )\
        ( button_name ).box( FL_OVAL_BOX )\
            .background( FL_BLACK )\
            .foreground( FL_LIGHT1 )\
            .font( FL_BOLD )\
            .callback( []( fltk::Widget*, void* ) cb )

        CREATE_ACTION_BUTTON( m_btn_hit, {
            self->send_action( net::Action::hitting );
        } );

        CREATE_ACTION_BUTTON( m_btn_stand, {
            self->send_action( net::Action::standing );
        } );

        CREATE_ACTION_BUTTON( m_btn_double, {
            self->send_action( net::Action::doubling );
        } );

#undef CREATE_ACTION_BUTTON

        //
        // Create the Manual, Reckless, etc. Buttons
        //

#define CREATE_STRATEGY_BUTTON( button_name, cb )\
        ( button_name ).type( FL_RADIO_BUTTON )\
            .background( FL_BLACK )\
            .foreground( FL_BLACK )\
            .font( FL_BOLD )\
            .callback( []( fltk::Widget*, void* ) cb )

        CREATE_STRATEGY_BUTTON( m_btn_manual, {
            self->m_player.strategy( new uc::ManualStrategy );
        } ).raw_action( []( Fl_Button* btn ) {
            btn->set();
        } );
        m_player.strategy( new uc::ManualStrategy );

        CREATE_STRATEGY_BUTTON( m_btn_conservative, {
            self->m_player.strategy( new uc::ConservativeStrategy );
        } );

        CREATE_STRATEGY_BUTTON( m_btn_reckless, {
            self->m_player.strategy( new uc::RecklessStrategy );
        } );

        CREATE_STRATEGY_BUTTON( m_btn_basic, {
            self->m_player.strategy( new uc::BasicStrategy );
        } );

#undef CREATE_STRATEGY_BUTTON

        //
        // Create the betting UI
        //

#define CREATE_BET_BUTTON( amount )\
        ( m_btn_bet_ ## amount ).box( FL_SHADOW_BOX )\
            .background( FL_LIGHT1 )\
            .foreground( FL_BLACK )\
            .font( FL_BOLD )\
            .callback( []( fltk::Widget*, void* ) {\
                self->change_bet( amount );\
            } )

        CREATE_BET_BUTTON( 1 );
        CREATE_BET_BUTTON( 5 );
        CREATE_BET_BUTTON( 10 );
        CREATE_BET_BUTTON( 50 );

        m_btn_bet_clear.box( FL_SHADOW_BOX )
            .background( FL_LIGHT1 )
            .foreground( FL_BLACK )
            .font( FL_BOLD )
            .callback( []( fltk::Widget*, void* ) {
                self->change_bet( -self->m_player.bet() );
            } );

#undef CREATE_BET_BUTTON

        m_balance.style_table( m_style_table )
            .style( "DDDDDDD");

        m_bet.style_table( m_style_table )
            .style( "DDDDDDD" );

        //
        // Create the Dealer and Player screens
        //

        m_dealer_display.style_table( m_style_table )
            .style( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

        m_player_display.style_table( m_style_table )
            .style( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

        for ( auto i = 0; i < net::MAX_PLAYERS - 1; i++ )
        {
            fltk::Label player_entry{ 40, 43 + ( 90 * i ), 175, 65 };
            player_entry.style_table( m_style_table )
                .style( "EEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" );

            m_player_displays.push_back( std::move( player_entry ) );
        }

        //
        // Show the window
        //

        m_window.end();
        m_window.show();

        Network::get().on_game_update( []( Game game ) {
            self->on_game_update( game ); 
        } );
        Network::get().on_dealer_update( []( Dealer dealer ) {
            self->on_dealer_update( dealer );
        } );

        // must be done here so all the c_str() things don't go out of scope
        // or something like that, idk. It screws up the text, that's all I
        // know
        Fl::run();
    }

    GameWindow::~GameWindow()
    {
        // deleting a nullptr is A-OK in C++
        delete m_partial_response;
    }

    void
    GameWindow::change_bet( int delta )
    {
        m_player.bet( m_player.bet() + delta );
        
        m_bet.text( std::to_string( m_player.bet() ) );
        m_balance.text( std::to_string( ( int ) m_player.balance() ) );
    }

    void
    GameWindow::send_action( net::Action action )
    {
        if ( m_partial_response == nullptr )
            return;

        m_partial_response->A = action;
        Network::get().send( *m_partial_response );

        delete m_partial_response;
        m_partial_response = nullptr;
    }

    void
    GameWindow::on_game_update( net::Game game )
    {
        // if we aren't in a game yet, just ignore it
        if ( m_player.game() == nullptr )
            return;

        // if the game doesn't match, then don't bother
        if ( strncmp( game.game_uid, m_player.game()->game_uid, net::UUID_LENGTH ) != 0 )
            return;

        // update the player's status
        m_player.from( game );

        // now, let's update all of the displays for cards and such,
        // and just treat the dealer and player as special cases
        auto pos = 0;
        for ( auto i = 0; i < net::MAX_PLAYERS; i++ )
        {
            net::PlayerState player = m_player.game()->p[ i ];

            // update our cards if we come across ourselves, otherwise, update
            // the next player's
            ( m_player == player ? m_player_display : m_player_displays[ pos++ ] )
                .text( to_string( player.cards ) );
        }

        m_dealer_display.text( to_string( m_player.game()->dealer_cards ) );
    }

    void
    GameWindow::on_dealer_update( net::Dealer dealer )
    {
        // ignore dealer updates if we're already in a game
        if ( m_player.game() != nullptr )
            return;

        m_player.join( dealer );
    }

}
