#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <stdlib.h>

void fork_cu_waitpid() {
    printf("Inainte de fork - un singur proces cu PID: %d\n", getpid());
    
    // Cream doi copii
    pid_t pid1 = fork();
    
    if (pid1 < 0) {
        perror("fork");
        return;
    }
    
    if (pid1 == 0) {
        // COPIL 1
        printf("COPIL 1 (PID %d): incep lucrul...\n", getpid());
        sleep(1);
        printf("COPIL 1: termin cu codul 42\n");
        exit(42);  // Exit cu cod 42
    } else {
        // PARINTE
        pid_t pid2 = fork();
        
        if (pid2 == 0) {
            // COPIL 2
            printf("COPIL 2 (PID %d): incep lucrul...\n", getpid());
            sleep(3);
            printf("COPIL 2: termin cu codul 7\n");
            exit(7);  // Exit cu cod 7
        } else {
            // PARINTE - astept copiii
            printf("PARINTE: am doi copii cu PID-urile %d si %d\n", pid1, pid2);
            
            // Astept SPECIFIC copilul 1
            printf("\nPARINTE: astept copilul 1 (%d) cu WNOHANG...\n", pid1);
            int status1;
            pid_t returned_pid;
            
            // Incerc sa astept fara sa ma blochez (WNOHANG)
            int incercari = 0;
            while ((returned_pid = waitpid(pid1, &status1, WNOHANG)) == 0) {
                printf("PARINTE: copilul 1 inca lucreaza... (incercarea %d)\n", ++incercari);
                sleep(1);
            }
            
            if (returned_pid == pid1) {
                printf("PARINTE: copilul 1 s-a terminat!\n");
                
                // Verific codul de iesire
                if (WIFEXITED(status1)) {
                    int exit_code = WEXITSTATUS(status1);
                    printf("PARINTE: copilul 1 a iesit cu codul: %d\n", exit_code);
                } else if (WIFSIGNALED(status1)) {
                    int signal = WTERMSIG(status1);
                    printf("PARINTE: copilul 1 a fost ucis de semnalul: %d\n", signal);
                }
            }
            
            // Acum astept copilul 2 - BLOCKING
            printf("\nPARINTE: astept copilul 2 (%d) BLOCKING...\n", pid2);
            int status2;
            waitpid(pid2, &status2, 0);
            
            if (WIFEXITED(status2)) {
                int exit_code = WEXITSTATUS(status2);
                printf("PARINTE: copilul 2 a iesit cu codul: %d\n", exit_code);
            }
            
            printf("PARINTE: toti copiii s-au terminat!\n");
        }
    }
}

int main(int argc, char *argv[]) {
    fork_cu_waitpid();
    return 0;
}