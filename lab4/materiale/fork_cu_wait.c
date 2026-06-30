#include <stdio.h> // standard input - output
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

void fork_cu_wait() {

    printf("Inainte de fork - un singur proces cu PID: %d\n", getpid());

    pid_t pid = fork(); 

    if(pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        // COPIL
        printf("COPIL: fac ceva...\n");
        sleep(2); // simulam ca treaba copilului ar dura 2 secunde
        printf("COPIL: am terminat!\n");
    }
    else {
        // PARINTE
        printf("PARINTE: astept copilul...\n");
        wait(NULL); // se asteapta finalizarea procesului copil
        printf("PARINTE: copilul a terminat, acum continui eu!\n");
    }
}

int main(int argc, char *argv[]) {

    fork_cu_wait();

    return 0;
}