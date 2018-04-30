#include <misc.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace uc
{

    std::string 
    to_string( const net::Hand& hand )
    {
        std::stringstream out;

        // then only go over the actual number of cards we have,
        // and if we come across an invalid card, then we know that
        // it's just face down

        auto i = 0u;

        // if the first card isn't valid, then it's just being hidden
        // from us, so we'll skip it
        if ( !is_valid( hand[ i ] ) )
        {
            out << "Face Down" << std::endl;
            i++;
        }

        for ( ; i < hand.size(); i++ )
        {
            const auto& card = hand[ i ];

            // if the card isn't valid, then we'll know we're at the end
            // of the card list
            if ( !is_valid( card ) )
                break;

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
            case net::Suit::hearts:     return "Hearts";
            case net::Suit::diamonds:   return "Diamonds";
            case net::Suit::clubs:      return "Clubs";
            case net::Suit::spades:     return "Spades";

            default:
                 throw std::runtime_error{ "What is this suit???" };
        }
    }

    std::string
    to_string( net::CardKind kind )
    {
        switch ( kind )
        {
            case net::CardKind::ace:    return "Ace";
            case net::CardKind::two:    return "Two";
            case net::CardKind::three:  return "Three"; 
            case net::CardKind::four:   return "Four"; 
            case net::CardKind::five:   return "Five";
            case net::CardKind::six:    return "Six";
            case net::CardKind::seven:  return "Seven";
            case net::CardKind::eight:  return "Eight"; 
            case net::CardKind::nine:   return "Nine"; 
            case net::CardKind::ten:    return "Ten"; 
            case net::CardKind::jack:   return "Jack"; 
            case net::CardKind::queen:  return "Queen"; 
            case net::CardKind::king:   return "King"; 

            default:
                throw std::runtime_error{ "What is this card???" };
        }
    }

    net::Hand to_hand( const net::Card cards[ net::MAX_CARDS ] )
    {
        net::Hand hand;
        std::copy( cards, cards + hand.size(), hand.begin() ); 

        // completely zero out any cards which aren't valid 
        for ( auto i = 0u; i < hand.size(); i++ )
        {
            if ( hand[ i ].valid == true )
                continue;

            net::Card card;
            memset(
                reinterpret_cast< void* >( &card ),
                0,
                sizeof( card )
            );
            hand[ i ] = card;
        }

        return hand;
    }

    unsigned int value_of( const net::Hand& hand )
    {
        auto ace_count = 0u;
        auto sum = 0u;


        auto i = 0u;

        // if the first card is invalid, we might just be looking at
        // the dealer's cards, so we'll check the next one too
        if ( !is_valid( hand[ 0 ] ) )
            i++;

        for ( ; i < hand.size(); i++ )
        {
            const auto& card = hand[ i ];

            // stop the first time we find an invalid card
            if ( !is_valid( card ) )
                break;

            // departure from normal formatting for sake of readability
            // and verifiability at a glance
            switch ( card.card )
            {
                case net::CardKind::ace:    ace_count++;    break;
                case net::CardKind::two:    sum += 2;       break; 
                case net::CardKind::three:  sum += 3;       break;
                case net::CardKind::four:   sum += 4;       break;
                case net::CardKind::five:   sum += 5;       break;
                case net::CardKind::six:    sum += 6;       break;
                case net::CardKind::seven:  sum += 7;       break;
                case net::CardKind::eight:  sum += 8;       break;
                case net::CardKind::nine:   sum += 9;       break;

                case net::CardKind::ten:
                case net::CardKind::jack:
                case net::CardKind::queen:
                case net::CardKind::king:   sum += 10;      break;

                // is_valid has verified card is one of these already
            }
        }

        // if even when they're all counted as ones, we bust, then we'll
        // just count them all like ones
        if ( ace_count + sum > 21 )
            return ace_count + sum;

        // => there must be SOME way to not bust
        
        // try to maximize the value of all of our aces 
        auto ace_low = 0;
        auto ace_high = ace_count;

        while ( ( ace_high * 11 ) + ( ace_low * 1 ) + sum > 21 )
        {
            ace_low++;
            ace_high--;
        }

        return ( ace_high * 11 ) + ( ace_low * 1 ) + sum;
    }

    bool is_valid( const net::Card& card )
    {
        if ( card.valid != true )
            return false;

        // if either of these to_strings throw an exception, then hey,
        // it was an invalid card!
        //
        // The chances of:
        // 1. valid == 1
        // 2. 0 <= card < 13
        // 3. 0 <= suit < 4
        //
        // all together are astronomically low for a 32-bit unsigned
        // integer, so hopefully we won't get garbage data
        //
        // And if it was an invalid card, then hey, the following cards
        // won't be valid either :)
        
        if ( card.valid != true )
            return false;

        if ( ( long ) card.card >= 13 )
            return false;

        if ( ( long ) card.suite >= 4 )
            return false;

        return true;
    }

}
