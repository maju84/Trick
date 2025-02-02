/* 
   PURPOSE: ( Child signal handler )
   PROGRAMMERS: (((Alex Lin) (NASA) (Feb 2008) (--) (Realtime)))
 */

/* 
 * $Id: child_handler.cpp 874 2010-07-28 16:42:51Z lin $
 */

#include <sys/types.h>
#include <sys/wait.h>

/**
 * @relates Trick::Executive
 * C binded function to handle the SIGCHLD signal.  The handler removes child processes 
 * from the process table when a child process exits. 
 * @return void
 */
void child_handler(int sig) {

    int status;

    switch (sig) {
        case SIGCHLD:
#if !( __ghs )
            wait(&status);
#endif
            break;
        default:
            break;
    }

    return;
}
