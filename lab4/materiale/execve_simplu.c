#include <stdio.h> // standard input - output
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

void execve_simplu() {

    printf("Inainte de execve\n");

    char *argv[] = {"/usr/bin/ls", "-l", NULL}; // vectorul de argumente

    execve("/usr/bin/ls", argv, NULL); // urmeaza semnatura syscall-ului execve

    perror("execve a esuat"); // NU se executa daca execve reuseste
}

int main(int argc, char *argv[]) {

    execve_simplu();

    return 0;
}