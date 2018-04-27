#include <misc.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace uc
{

    std::string 
    to_string( const net::Card cards[ net::MAX_CARDS ] )
    {
        std::stringstream out;

        for ( auto i = 0; i < net::MAX_CARDS; i++ )
        {
            net::Card card = cards[ i ];
            
            // skip over inactive cards
            if ( !card.valid )
                continue;

            out << to_string( card.card ) 
                << " of " 
                << to_string( card.suite )
                << std::endl;
        }

        return out.str();
    }

    std::string
    to_string( net::Suit suit )
    {
        switch ( suit )
        {
            case net::Suit::hearts:
                return "Hearts";

            case net::Suit::diamonds:
                return "Diamonds";

            case net::Suit::clubs:
                return "Clubs";

            case net::Suit::spades:
                return "Spades";

            default:
                throw std::runtime_error{ "What is this suit???" };
        }
    }

    std::string
    to_string( net::CardKind kind )
    {
        switch ( kind )
        {
            case net::CardKind::ace:
                return "Ace";

            case net::CardKind::two:
                return "Two";

            case net::CardKind::three:
                return "Three";

            case net::CardKind::four:
                return "Four";

            case net::CardKind::five:
                return "Five";

            case net::CardKind::six:
                return "Six";

            case net::CardKind::seven:
                return "Seven";

            case net::CardKind::eight:
                return "Eight";

            case net::CardKind::nine:
                return "Nine";

            case net::CardKind::ten:
                return "Ten";

            case net::CardKind::jack:
                return "Jack";

            case net::CardKind::queen:
                return "Queen";

            case net::CardKind::king:
                return "King";

            default:
                throw std::runtime_error{ "What is this card???" };
        }
    }

}
