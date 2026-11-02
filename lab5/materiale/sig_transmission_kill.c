#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    int pid = fork();

    if (pid < 0) {
        perror("fork");
    }
    else if (pid == 0) {
        // COPIL
        while (1) {
            printf("Copilul rulează...\n");
            sleep(1);
        }
    } else {
        // PARINTE
        sleep(3);
        printf("Părintele trimite SIGINT copilului\n");
        kill(pid, SIGINT); // trimite semnal
    }
    return 0;
}
