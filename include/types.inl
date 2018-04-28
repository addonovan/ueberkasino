
// Create typedefs for OSPL things, using the minimal net:: namespace
#ifdef _UBERCASINO_H_
#ifndef __TYPES_NETWORK__
#define __TYPES_NETWORK__

/**
 * Namespace dealing with things relating to the OpenSplice network
 * communcation.
 */
namespace net
{
    /** A networked game state. */
    typedef UberCasino::Game               Game;

    typedef UberCasino::game_state         GameState;

    /** A networked player state. */
    typedef UberCasino::PlayerState        PlayerState;

    /** The player action structure sent over the network. */
    typedef UberCasino::Player             Player;

    /** A dealer structure sent over the network. */
    typedef UberCasino::Dealer             Dealer;

    typedef UberCasino::card_t             Card;

    typedef UberCasino::suite_t            Suit;

    typedef UberCasino::card_kind          CardKind;

    typedef UberCasino::player_action_t    Action;

    constexpr long int UUID_LENGTH = UberCasino::SIZE_OF_UUID;

    constexpr long int MAX_PLAYERS = UberCasino::MAX_PLAYERS_IN_A_GAME;

    constexpr long int MAX_CARDS = UberCasino::MAX_CARDS_PER_PLAYER;

}

#endif // __TYPES_NETWORK__
#endif // _UBERCASINO_H_

#ifdef Fl_H
#ifndef __TYPES_FLTK__

namespace fltk
{
    typedef Fl_Window           Window;
    typedef Fl_Widget           Widget;
    typedef Fl_Box              Box;

    typedef Fl_Boxtype          BoxType;
    typedef Fl_Color            Color;
    typedef Fl_Font             Font;

    typedef Fl_Text_Display     TextDisplay;
    typedef Fl_Text_Buffer      TextBuffer;

    typedef Fl_Text_Display::Style_Table_Entry StyleEntry;
}

#endif // __TYPES_FLTK__
#endif // Fl_H
