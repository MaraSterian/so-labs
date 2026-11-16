#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
    int fd[2];
    pid_t pid;
    char buf[100];

    if (pipe(fd) < 0) {
        perror("pipe");
        return errno;
    }

    pid = fork();
    if (pid < 0) {
    // fork nereusit
        perror("fork");
        return errno;
    }

    if (pid == 0) {
    // Proces COPIL
        close(fd[1]); // copilul nu scrie in pipe

        dup2(fd[0], STDIN_FILENO); // redirectam stdin -> citirea din pipe
        close(fd[0]);

        char buf[100];
        scanf("%s", buf); // citim mesajul de la parinte

        printf("Copilul a primit: %s\n", buf);
    } else {
    // Proces PARINTE
        close(fd[0]); // parintele nu citeste din pipe

        dup2(fd[1], STDOUT_FILENO); // redirectam stdout -> scriere in pipe
        close(fd[1]);

        printf("Salut"); // mesajul va ajunge la copil prin pipe
    }

    return 0;
}
