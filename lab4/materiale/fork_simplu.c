#include <stdio.h> // standard input - output
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>


void fork_simplu() {

    printf("Inainte de fork - un singur proces cu PID: %d\n", getpid());

    pid_t aux_pid = fork(); 
    
    /*
     * de aici incolo ambele procese executa codul simultan
     * procesele se comporta ca doua entitati diferite
     */

    if(aux_pid < 0) {
        perror("fork"); // error pentru ca fork a esuat
        //return 1;
    }
    else if (aux_pid == 0) {
        // executat doar de copil
        printf("PROCES COPIL cu PID: %d\n", getpid());
        printf("Parintele meu are PID: %d\n", getppid());
    }
    else {
        printf("PROCES PARINTE cu PID: %d\n", getpid());
        printf("Copilul meu are PID: %d\n", aux_pid);
    }

}

int main(int argc, char *argv[]) {

    fork_simplu();

    return 0;
}