#include <cstdio>

#include <title_window.hpp>

void setup_handler();

int main()
{
    setup_handler();
    fclose( stderr );

    uc::TitleWindow::show();
    return 0;
}

#ifndef DEBUG

void setup_handler()
{
}

#else

#include <signal.h> 
#include <execinfo.h>

void handler( int sig )
{
    void* array[ 10 ];
    size_t size = backtrace( array, 10 );
    fprintf( stderr, "Error: signal %d:\n", sig );
    backtrace_symbols_fd( array, size, STDERR_FILENO );
    exit( 0 );
}

void setup_handler()
{
    signal( SIGSEGV, handler );
}

#endif

