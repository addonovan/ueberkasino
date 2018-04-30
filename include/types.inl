// Create typedefs for OSPL things, using the minimal net:: namespace
#ifdef _UBERCASINO_H_
#ifndef __TYPES_NETWORK__
#define __TYPES_NETWORK__

#include <array>

/**
 * Namespace dealing with things relating to the OpenSplice network
 * communcation.
 */
namespace net
{
    /** A networked game packet. */
    typedef UberCasino::Game               Game;

    /** A networked game state. */
    typedef UberCasino::game_state         GameState;

    /** A networked player state. */
    typedef UberCasino::PlayerState        PlayerState;

    /** The player action structure sent over the network. */
    typedef UberCasino::Player             Player;

    /** A dealer structure sent over the network. */
    typedef UberCasino::Dealer             Dealer;

    /** A combinatino of the suit and card kind */
    typedef UberCasino::card_t             Card;

    /** An enum representing the four suits of cards. */
    typedef UberCasino::suite_t            Suit;

    /** An enum representing the 13 types of cards. */
    typedef UberCasino::card_kind          CardKind;

    /** An enum representing the actions a player can take. */
    typedef UberCasino::player_action_t    Action;

    /** The length of a single UUID. */
    constexpr long int UUID_LENGTH = UberCasino::SIZE_OF_UUID;

    /** The maximum number of players who can be in a single game at one time */
    constexpr long int MAX_PLAYERS = UberCasino::MAX_PLAYERS_IN_A_GAME;

    /** The maximum number of cards a single player can hold. */
    constexpr long int MAX_CARDS = UberCasino::MAX_CARDS_PER_PLAYER;

    /** A hand of cards, owned by either players or dealers */
    typedef std::array< Card, MAX_CARDS > Hand;

}

#endif // __TYPES_NETWORK__
#endif // _UBERCASINO_H_

#ifdef Fl_H
#ifndef __TYPES_FLTK__

/**
 * A namespace whose sole purpose to eliminate writing the `Fl_` prefix.
 */
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
