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
    if (pid < 0) return errno;
    // fork nereusit

    if (pid == 0) {
    // Proces COPIL
        close(fd[1]); // inchidem capatul de scriere
        read(fd[0], buf, sizeof(buf));
        printf("Child received: %s\n", buf);
        close(fd[0]);
    } else {
    // Proces PARINTE
        close(fd[0]); // inchidem capatul de citire
        char msg[] = "Hello from parent";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
    }
    return 0;
}
