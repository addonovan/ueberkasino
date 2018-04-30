#ifndef __FLTK_HPP__
#define __FLTK_HPP__

#include <memory>
#include <vector>

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Round_Button.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Window.H>
#include "types.inl"

namespace fltk
{

    template< typename T >
    class RawButton;

    /** A `RawButton` type for a regular Fl_Button */
    typedef RawButton< Fl_Button >          Button;

    /** A `RawButton` type for an `Fl_Round_Button` */
    typedef RawButton< Fl_Round_Button >    RadioButton;

    /**
     * A generic wrapper around the FLTK buttons. This allows for calls to be
     * chained in a builder-pattern-style manner.
     */
    template< typename T >
    class RawButton
    {
   
        //
        // Members
        //

    private:

        /** The actual FLTK button we're representing */
        std::unique_ptr< T > m_button;

        /** A list of user data passed to the button's callbacks */
        std::vector< void* > m_user_data;

        //
        // Constructor
        //

    public:

        /**
         * Constructs a new button at `(x, y)` with the dimensions
         * `(width, height)` and the label `text`.
         */
        RawButton( int x, int y, int width, int height, const std::string& text )
          : m_button{ new T{ 
                  x, 
                  y, 
                  width, 
                  height, 
                  strndup( text.c_str(), text.size() ) 
            } }
        {
        }

        //
        // Builder Methods
        //

    public:

        /**
         * Sets the box type for this button.
         */
        RawButton< T >& box( BoxType type )
        {
            m_button->box( type );
            return *this;
        }

        /**
         * Sets the background color of this button.
         */
        RawButton< T >& background( Color color )
        {
            m_button->color( color );
            return *this;
        }

        /**
         * Sets the foreground (label) color of this button.
         */
        RawButton< T >& foreground( Color color )
        {
            m_button->labelcolor( color );
            return *this;
        }

        /**
         * Sets the font for this button.
         */
        RawButton< T >& font( Font font )
        {
            m_button->labelfont( font );
            return *this;
        }

        /**
         * Changes the type of button this is, for instance `FL_RADIO_BUTTON`
         */
        RawButton< T >& type( unsigned char type )
        {
            m_button->type( type );
            return *this;
        }

        /**
         * Assigns the given callback, `cb`, to be called when the button is
         * pressed.
         */
        template< typename F >
        RawButton< T >& callback( F cb )
        {
            m_button->callback( cb );
            return *this;
        }

        /**
         * Adds another element of user data to this button's user data. This
         * will be passed as the second (`void*`) argument to the button's
         * callback.
         *
         * A non-null pointer to a `std::vector< void* >` will be passed as the
         * `void*` parameter, and thus you must first `reinterpret_cast` it back
         * into its original type.
         *
         * After that, you need to get the data out of the vector by using the
         * `->at( index )` syntax, which will return another `void*` which must
         * also be `reintepret_cast`ed back into the original type.
         *
         * The order of values in the user data vector will be the same as the
         * order in which they are inserted.
         */
        template< typename U >
        RawButton< T >& add_user_data( U* data )
        {
            m_user_data.push_back( reinterpret_cast< void* >( data ) ); 
            m_button->user_data( reinterpret_cast< void* >( &m_user_data ) );
            return *this;
        }

        /**
         * Supplies the `action` closure with a non-null pointer to the
         * underlying `Fl_Button` of this button, allowing you do perform any
         * FLTK operations which are not represented by this adapter.
         */
        template< typename F >
        RawButton< T >& raw_action( F action )
        {
            action( m_button.get() );
            return *this;
        }

    };

    /**
     * A better fltk label, which will manage the label's:
     * * `display: TextDisplay`
     * * `text_buffer: TextBuffer`
     * * `style_buffer: TextBuffer`
     *
     * Automatically so you don't have to deal with the insane amount of
     * overhead for what probably should be the simplest UI element. 
     */
    class Label
    {

        //
        // Members
        //

    private:

        /** The underlying text display */
        std::unique_ptr< TextDisplay > m_display;

        /** The underlying text buffer for this label's text */
        std::unique_ptr< TextBuffer >  m_text;

        /** The underlying style buffer (might be null!) for this label */
        std::unique_ptr< TextBuffer >  m_style;

        //
        // Constructor
        //

    public:
        
        /**
         * Constructs a new FLTK TextDisplay at `(x, y)` with dimensions
         * `(width, height)`, as well as its TextBuffer, with the given `text`. 
         */
        Label( int x, int y, int width, int height, const std::string& text = "" )
          : m_display{ new TextDisplay{ x, y, width, height } },
            m_text{ new TextBuffer }
        {
            m_text->text( text.c_str() );
            m_display->buffer( m_text.get() );
        }

        //
        // Builder Methods
        //

    public:

        /**
         * Changes the `text` to draw in this label.
         */
        Label& text( const std::string& text )
        {
            m_text->text( text.c_str() );
            return *this;
        }

        /**
         * Changes the `text` of the style buffer.
         *
         * This will create a new style buffer if one doesn't already exist.
         */
        Label& style( const std::string& text )
        {
            if ( m_style == nullptr )
                m_style = std::unique_ptr< TextBuffer >{ new TextBuffer };

            m_style->text( text.c_str() );
            return *this;
        }

        /**
         * Defines the `entries` of the style table used to style the text
         * in this label.
         */
        Label& style_table( const std::vector< StyleEntry >& entries )
        {
            if ( m_style == nullptr )
            {
                m_style = std::unique_ptr< TextBuffer >{ new TextBuffer };
            }

            m_display->highlight_data( 
                m_style.get(), 
                entries.data(), 
                entries.size(), 
                'E', 
                0, 
                0 
            );

            return *this;
        }

        /**
         * Supplies the `action` closure with a non-null pointer to the
         * underlying `Fl_TextDisplay` and `Fl_TextBuffer` (text) as well as
         * a possibly-null pointer to a `Fl_TextBuffer` (style), allowing you
         * to perform FLTK operations which are not represented by this adapter.
         */
        template< typename F >
        Label& raw_action( F action )
        {
            action( m_display.get(), m_text.get(), m_style.get() );
            return *this;
        }
    };

}


#endif // __FLTK_HPP__
