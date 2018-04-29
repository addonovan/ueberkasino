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

    typedef RawButton< Fl_Button >          Button;
    typedef RawButton< Fl_Round_Button >    RadioButton;

    template< typename T >
    class RawButton
    {
    
    private:
        std::unique_ptr< T > m_button;

        std::vector< void* > m_user_data;

    public:
        RawButton( int x, int y, int width, int height, const std::string& text )
          : m_button{ new T{ x, y, width, height, text.c_str() } }
        {
        }

    public:
        RawButton< T >& box( BoxType type )
        {
            m_button->box( type );
            return *this;
        }

        RawButton< T >& background( Color color )
        {
            m_button->color( color );
            return *this;
        }

        RawButton< T >& foreground( Color color )
        {
            m_button->labelcolor( color );
            return *this;
        }

        RawButton< T >& font( Font font )
        {
            m_button->labelfont( font );
            return *this;
        }

        RawButton< T >& type( unsigned char type )
        {
            m_button->type( type );
            return *this;
        }

        template< typename F >
        RawButton< T >& callback( F cb )
        {
            m_button->callback( cb );
            return *this;
        }

        template< typename U >
        RawButton< T >& add_user_data( U* data )
        {
            m_user_data.push_back( reinterpret_cast< void* >( data ) ); 
            m_button->user_data( reinterpret_cast< void* >( &m_user_data ) );
            return *this;
        }

        template< typename F >
        RawButton< T >& raw_action( F action )
        {
            action( m_button.get() );
            return *this;
        }

    };

    class Label
    {

    private:

        std::unique_ptr< TextDisplay > m_display;
        std::unique_ptr< TextBuffer >  m_text;
        std::unique_ptr< TextBuffer >  m_style;

    public:
        Label( int x, int y, int width, int height, const std::string& text = "" )
          : m_display{ new TextDisplay{ x, y, width, height } },
            m_text{ new TextBuffer }
        {
            m_text->text( text.c_str() );
            m_display->buffer( m_text.get() );
        }

        Label( Label&& other ) noexcept
          : m_display{ std::move( other.m_display ) },
            m_text{ std::move( other.m_text ) },
            m_style{ std::move( other.m_style ) }
        {
        }

    public:
        Label& text( const std::string& text )
        {
            m_text->text( text.c_str() );
            return *this;
        }

        Label& style( const std::string& text )
        {
            if ( m_style == nullptr )
                m_style = std::unique_ptr< TextBuffer >{ new TextBuffer };

            m_style->text( text.c_str() );
            return *this;
        }

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
                'A', 
                0, 
                0 
            );

            return *this;
        }

        template< typename F >
        Label& raw_action( F action )
        {
            action( m_display.get(), m_text.get(), m_style.get() );
            return *this;
        }
    };

}


#endif // __FLTK_HPP__
