#include <game_window.hpp>
#include <network.hpp>
#include <misc.hpp>
#include <cstring>

//
// Global, Constant Style Table
//

namespace uc
{

    GameWindow::GameWindow( Game& game )
        : m_game{ game }
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

#define CREATE_ACTION_BUTTON( button_name, action )\
        ( button_name ).box( FL_OVAL_BOX )\
            .background( FL_BLACK )\
            .foreground( FL_LIGHT1 )\
            .font( FL_BOLD )\
            .callback( []( fltk::Widget*, void* ) {\
                self->m_game.on_action_picked( action );\
            } )

        CREATE_ACTION_BUTTON( m_btn_hit, net::Action::hitting ); 
        CREATE_ACTION_BUTTON( m_btn_stand, net::Action::standing );
        CREATE_ACTION_BUTTON( m_btn_double, net::Action::doubling );

#undef CREATE_ACTION_BUTTON

        //
        // Create the Manual, Reckless, etc. Buttons
        //

#define CREATE_STRATEGY_BUTTON( button_name, class )\
        ( button_name ).type( FL_RADIO_BUTTON )\
            .background( FL_BLACK )\
            .foreground( FL_BLACK )\
            .font( FL_BOLD )\
            .callback( []( fltk::Widget*, void* ) {\
                self->m_game.on_strategy_changed( new class );\
            } )

        CREATE_STRATEGY_BUTTON( m_btn_manual, uc::ManualStrategy )
            .raw_action( []( Fl_Button* btn ) {
                btn->set();
            } );
        m_game.on_strategy_changed( new uc::ManualStrategy );

        CREATE_STRATEGY_BUTTON( m_btn_conservative, uc::ConservativeStrategy );
        CREATE_STRATEGY_BUTTON( m_btn_reckless, uc::RecklessStrategy );
        CREATE_STRATEGY_BUTTON( m_btn_basic, uc::BasicStrategy );

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
                self->change_bet( -self->m_game.player().bet() );
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

        Network::get().on_game_update( []( net::Game game ) {
            self->on_game_update( game ); 
        } );

        Network::get().on_dealer_update( []( net::Dealer dealer ) {
            self->on_dealer_update( dealer );
        } );

        // must be done here so all the c_str() things don't go out of scope
        // or something like that, idk. It screws up the text, that's all I
        // know
        Fl::run();
    }

    GameWindow::~GameWindow() = default;

    void
    GameWindow::change_bet( int delta )
    {
        m_game.on_bet_changed( delta );
       
        auto& player = m_game.player(); 
        m_bet.text( std::to_string( player.bet() ) );
        m_balance.text( std::to_string( ( int ) player.balance() ) );
    }

    void
    GameWindow::on_game_update( net::Game game )
    {
        m_game.on_game_update( game );
        // TODO also update all of the card displays to whatever the game
        // says they should be
    }

    void
    GameWindow::on_dealer_update( net::Dealer dealer )
    {
        m_game.on_dealer_update( dealer );
        // TODO also show the dealer's name if the game is connected correctly
    }

}
