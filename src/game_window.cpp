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
    }

    void
    GameWindow::show( Game& game )
    {
        GameWindow game_win{ game };

        //
        // Create components
        //

        fltk::Window window{ 30, 30, 800, 600, "Black Jack" };

        fltk::Box* box = new fltk::Box{ 250, 5, 300, 100, "Black Jack!" };

        fltk::Button btn_hit{    600, 470, 60, 60, "HIT" };
        fltk::Button btn_stand{  650, 420, 60, 60, "STAND" };
        fltk::Button btn_double{ 700, 470, 60, 60, "DBL\nDOWN" };

        fltk::RadioButton btn_manual{       625, 150, 20, 20, "Manual" };
        fltk::RadioButton btn_conservative{ 625, 175, 20, 20, "Conservative" };
        fltk::RadioButton btn_reckless{     625, 200, 20, 20, "Reckless" };
        fltk::RadioButton btn_basic{        625, 225, 20, 20, "Traditional" };

        fltk::Label balance{  600, 300, 160, 50, 
            std::to_string( ( int ) game.player().balance() )
        };
        fltk::Label bet{      315, 255, 160, 50,
            std::to_string( game.player().bet() )
        };

        fltk::Button btn_bet_1{       295, 315, 45, 30, "$1" };
        fltk::Button btn_bet_5{       345, 315, 45, 30, "$5" };
        fltk::Button btn_bet_10{      395, 315, 45, 30, "$10" };
        fltk::Button btn_bet_50{      445, 315, 45, 30, "$50" };
        fltk::Button btn_bet_clear{   345, 355, 90, 45, "CLEAR BET" };

        fltk::Label dealer_display{ 315, 133, 175, 65 };
        fltk::Label player_display{ 315, 453, 175, 105 };

        std::map< long int, fltk::Label* > card_displays;
        card_displays[ -1 ] = &dealer_display;
        card_displays[ -2 ] = &player_display;

        std::vector< fltk::StyleEntry > style_table = {
            { FL_BOLD,      FL_HELVETICA, 18, 0u },
            { FL_ITALIC,    FL_HELVETICA, 18, 0u },
            { FL_BLACK,     FL_HELVETICA, 18, 0u }, 
            { FL_BLACK,     FL_HELVETICA, 34, 0u },
            { FL_BLACK,     FL_HELVETICA, 10, 0u },
        };

        //
        // Set up components
        //

        window.begin();
        window.color( 0x00500000 );

        box->box( FL_NO_BOX );
        box->labelfont( FL_BOLD + FL_HELVETICA );
        box->labelsize( 30 );
        box->labeltype( FL_SHADOW_LABEL );

        //
        // Create the Hit, Stand, Double Down buttons
        //

#define CREATE_ACTION_BUTTON( button_name, action )\
        ( button_name ).box( FL_OVAL_BOX )\
            .background( FL_BLACK )\
            .foreground( FL_LIGHT1 )\
            .font( FL_BOLD )\
            .add_user_data( &game )\
            .callback( []( fltk::Widget*, void* data ) {\
                auto* params =\
                    reinterpret_cast< std::vector< void* >* >( data );\
                auto* game = reinterpret_cast< Game* >( params->at( 0 ) );\
                if ( game == nullptr ) return;\
                game->on_action_picked( action );\
            } )

        CREATE_ACTION_BUTTON( btn_hit, net::Action::hitting ); 
        CREATE_ACTION_BUTTON( btn_stand, net::Action::standing );
        CREATE_ACTION_BUTTON( btn_double, net::Action::doubling );

#undef CREATE_ACTION_BUTTON

        //
        // Create the Manual, Reckless, etc. Buttons
        //

#define CREATE_STRATEGY_BUTTON( button_name, class )\
        ( button_name ).type( FL_RADIO_BUTTON )\
            .background( FL_BLACK )\
            .foreground( FL_BLACK )\
            .font( FL_BOLD )\
            .add_user_data( &game )\
            .callback( []( fltk::Widget*, void* data ) {\
                auto* params =\
                    reinterpret_cast< std::vector< void* >* >( data );\
                auto* game = reinterpret_cast< Game* >( params->at( 0 ) );\
                \
                if ( game == nullptr ) return;\
                game->on_strategy_changed( new class );\
            } )

        CREATE_STRATEGY_BUTTON( btn_manual, uc::ManualStrategy )
            .raw_action( []( Fl_Button* btn ) {
                btn->set();
            } );
        game.on_strategy_changed( new uc::ManualStrategy );

        CREATE_STRATEGY_BUTTON( btn_conservative, uc::ConservativeStrategy );
        CREATE_STRATEGY_BUTTON( btn_reckless, uc::RecklessStrategy );
        CREATE_STRATEGY_BUTTON( btn_basic, uc::BasicStrategy );

#undef CREATE_STRATEGY_BUTTON

        //
        // Create the betting UI
        //

#define CREATE_BET_BUTTON( name, amount )\
        ( btn_bet_ ## name ).box( FL_SHADOW_BOX )\
            .background( FL_LIGHT1 )\
            .foreground( FL_BLACK )\
            .font( FL_BOLD )\
            .add_user_data( &game_win )\
            .add_user_data( &bet )\
            .add_user_data( &balance )\
            .callback( []( fltk::Widget*, void* data ) {\
                auto* params =\
                    reinterpret_cast< std::vector< void* >* >( data );\
                \
                auto* self = \
                    reinterpret_cast< GameWindow* >( params->at( 0 ) );\
                auto* bet = \
                    reinterpret_cast< fltk::Label* >( params->at( 1 ) );\
                auto* balance = \
                    reinterpret_cast< fltk::Label* >( params->at( 2 ) );\
                \
                if ( self == nullptr ) return;\
                if ( bet == nullptr ) return;\
                if ( balance == nullptr ) return;\
                self->change_bet( amount, bet, balance );\
            } )

        CREATE_BET_BUTTON( 1, 1 );
        CREATE_BET_BUTTON( 5, 5 );
        CREATE_BET_BUTTON( 10, 10 );
        CREATE_BET_BUTTON( 50, 50 );
        CREATE_BET_BUTTON( clear, -self->m_game.player().bet() );

#undef CREATE_BET_BUTTON

        balance.style_table( style_table )
            .style( "DDDDDDD");

        bet.style_table( style_table )
            .style( "DDDDDDD" );

        //
        // Create the player screens 
        //

#define PLAYER_ENTRY( i )\
        fltk::Label player_entry_ ## i { 40, 43 + ( 90 * i ), 175, 65 };\
        card_displays[ i ] = &player_entry_ ## i;

        // this MUST not be done in a for loop, FLTK will get very pissy if you
        // do because FLTK is an amazingly shitty library that shouldn't exist
        // with modern C++ code
        
        PLAYER_ENTRY( 0 );
        PLAYER_ENTRY( 1 );
        PLAYER_ENTRY( 2 );
        PLAYER_ENTRY( 3 );
        PLAYER_ENTRY( 4 );
        PLAYER_ENTRY( 5 );

#undef PLAYER_ENTRY

        //
        // Show the window
        //

        window.end();
        window.show();

        Network::get().on_game_update( [ &game_win ]( net::Game game ) {
            game_win.on_game_update( game ); 
        } );

        Network::get().on_dealer_update( [ &game_win ]( net::Dealer dealer ) {
            game_win.on_dealer_update( dealer );
        } );

        std::map< std::string, void* > ui_info;

#define UI_INFO_ITEM( var )\
        ui_info[ #var ] = reinterpret_cast< void* >( &var );

        UI_INFO_ITEM( game_win );
        UI_INFO_ITEM( card_displays );
        UI_INFO_ITEM( bet );
        UI_INFO_ITEM( balance );

#undef UI_INFO_ITEM

        Fl::add_timeout( 
            0.5,
            GameWindow::update_ui_timed,
            reinterpret_cast< void* >( &ui_info )
        );

        // must be done here so all the c_str() things don't go out of scope
        // or something like that, idk. It screws up the text, that's all I
        // know
        Fl::run();
    }

    void
    GameWindow::change_bet( int delta, fltk::Label* bet, fltk::Label* balance )
    {
        m_game.on_bet_changed( delta );
       
        auto& player = m_game.player(); 
        bet->text( std::to_string( player.bet() ) );
        balance->text( std::to_string( ( int ) player.balance() ) );
    }

    void
    GameWindow::update_ui_timed( void* data )
    {
        auto& map = *reinterpret_cast< std::map< std::string, void* >* >( data );

        auto& game = *reinterpret_cast< GameWindow* >( map[ "game_win" ] );
        auto& displays = 
            *reinterpret_cast< 
                std::map< long int, fltk::Label* >* 
            >( map[ "card_displays" ] ); 

        game.update_card_displays( displays );

        auto* bet = reinterpret_cast< fltk::Label* >( map[ "bet" ] );
        auto* balance = reinterpret_cast< fltk::Label* >( map[ "balance" ] );

        game.change_bet( 0, bet, balance );

        Fl::add_timeout( 
            0.5,
            GameWindow::update_ui_timed,
            data
        );
    }

    void
    GameWindow::update_card_displays( 
            std::map< long int, fltk::Label* >& card_displays
    )
    {
        // if we aren't in a game, then we'll just blank out all of our card
        // displays
        if ( !m_game.cards_dealt() )
            return;

        // update all of our game hands
        auto& hands = m_game.hands();
       
        // fill in all of the hand labels with the most recent information 
        for ( const auto& hand : hands )
        {
            auto* label = card_displays[ hand.first ];
            label->text( to_string( hand.second ) );
        }

        // finally, update our player's card display
        // this is a special case where card_displays[ -2 ] is the player's
        auto* label = card_displays[ -2 ];
        label->text( to_string( m_game.player().hand() ) );
    }

    void
    GameWindow::on_game_update( net::Game game )
    {
        m_game.on_game_update( game );
    }

    void
    GameWindow::on_dealer_update( net::Dealer dealer )
    {
        m_game.on_dealer_update( dealer );
    }

}
