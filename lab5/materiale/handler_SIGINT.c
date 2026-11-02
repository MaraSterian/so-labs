#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>



void handler(int signum) {
    printf("Am primit semnalul %d\n", signum);
}

int main() {

    // crearea si initializarea cu zero a structurii
    struct sigaction sa = { 0 };

    // specificarea rutinei pe care sa o apeleze la primirea semnalului
    sa.sa_handler = handler;
    //sa.sa_handler = SIG_IGN;

    // masca goala pentru a nu bloca niciun semnal in timpul rutinei
    sigemptyset(&sa.sa_mask);

    // actiunea se intampla la primirea semnalului SIGINT
    sigaction(SIGINT, &sa, NULL);

    printf("PID = %d. Aștept semnal...\n", getpid());
    while (1) 
        pause(); // asteapta semnale
}