#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void handler(int signum) {
    printf("Am primit semnalul %d\n", signum);
}

int main(int argc, char const *argv[])
{
    struct sigaction sa = { 0 }; // 0 pt siguranta

    // sa.sa_handler = NULL;
    // sa.sa_mask = empty;
    // sa.sa_flags = 0;
    // sa.sa_sigaction = NULL;

    sa.sa_handler = handler; // apelata la SIGUSR1

    sigemptyset(&sa.sa_mask); //nu va fi blocat niciun semnal
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);

    printf("PID = %d. Trimit semnalul SIGUSR1 către mine însumi...\n", getpid());
    
    raise(SIGUSR1);
    raise(SIGINT);
    printf("Execuția continuă după primirea semnalului.\n");
    
    //raise(SIGINT);
    //kill(getpid(), SIGINT);
    
    while (1)
        pause();
    
    return 0;
}
