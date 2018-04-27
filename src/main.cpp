#include <iostream>
#include <cstdio>

#include <title_window.hpp>

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
    pid_t pid = fork();	
    if ( pid == 0 )
    {
        fclose( stderr );
        uc::TitleWindow window;
        return 0;
    }
    else if ( pid > 0 )
    {
        waitpid( pid, NULL, 0 );
    }
    else
    {
        std::cerr << "failed to start child process!" << std::endl;
        return 1;
    }

    return 0;
}
