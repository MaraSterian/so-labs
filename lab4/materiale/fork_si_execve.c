#include <stdio.h> // standard input - output
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

void fork_si_execve() { // combinatie tipica

    pid_t pid = fork(); 

    if(pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        // COPIL - se va executa un program nou

        printf("COPIL: executam comanda pwd...\n");

        char *argv[] = {"/usr/bin/pwd", NULL}; // vectorul de argumente
        execve("/usr/bin/pwd", argv, NULL); // schimbam executabilul

        // daca ajungem aici inseamna ca execve a esuat
        perror("execve");
    }
    else {
        // PARINTE - continua programul original

        wait(NULL); // parintele asteapta copilul sa termine

        printf("PARINTE: program terminat!\n");
    }
}

int main(int argc, char *argv[]) {

    fork_si_execve();

    return 0;
}