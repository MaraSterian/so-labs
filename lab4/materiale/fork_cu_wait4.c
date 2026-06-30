#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <errno.h>
#include <stdlib.h>

void fork_cu_wait4() {
    printf("Inainte de fork - PID parent: %d\n", getpid());
    
    pid_t pid = fork();
    
    if (pid < 0) {
        perror("fork");
        return;
    }
    
    if (pid == 0) {
        // COPIL - facem ceva ce consuma resurse
        printf("COPIL (PID %d): inceput calculul intensiv...\n", getpid());
        
        // Calculul: suma de la 1 la 1 miliard
        long long suma = 0;
        for (long long i = 1; i <= 1000000000; i++) {
            suma += i;
        }
        
        printf("COPIL: Suma calculata: %lld\n", suma);
        printf("COPIL: am terminat!\n");
        exit(0);
    } else {
        // PARINTE - astept cu wait4 si colectez statistici
        printf("PARINTE: astept copilul %d cu wait4()...\n", pid);
        
        int status;
        struct rusage usage;
        
        // wait4 returneaza PID-ul copilului si completeaza usage
        pid_t waited_pid = wait4(pid, &status, 0, &usage);
        
        if (waited_pid == pid) {
            printf("\n=== STATISTICI RESURSE COPIL ===\n");
            
            // Timp CPU utilizator
            printf("Timp CPU utilizator: %ld.%06ld secunde\n",
                   usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
            
            // Timp CPU sistem
            printf("Timp CPU sistem: %ld.%06ld secunde\n",
                   usage.ru_stime.tv_sec, usage.ru_stime.tv_usec);
            
            // Dimensiunea maxima a memoriei
            printf("Maxima rezidenta de memorie: %ld KB\n", usage.ru_maxrss);
            
            // Numar de page faults
            printf("Page faults (fara I/O): %ld\n", usage.ru_minflt);
            printf("Page faults (cu I/O): %ld\n", usage.ru_majflt);
            
            // Context switches
            printf("Context switches voluntare: %ld\n", usage.ru_nvcsw);
            printf("Context switches involuntare: %ld\n", usage.ru_nivcsw);
            
            // Input/Output
            printf("Operatii I/O citire: %ld\n", usage.ru_inblock);
            printf("Operatii I/O scriere: %ld\n", usage.ru_oublock);
            
            printf("\n=== STATUS IESIRE ===\n");
            if (WIFEXITED(status)) {
                printf("Copilul a iesit normal cu codul: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Copilul a fost ucis de semnalul: %d\n", WTERMSIG(status));
            }
        }
    }
}

int main(int argc, char *argv[]) {
    fork_cu_wait4();
    return 0;
}