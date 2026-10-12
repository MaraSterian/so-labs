#include <stdio.h> // standard input - output
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <errno.h>

// scriere directa pe ecran
void func1() {

    const char *msg1 = "bunasiua\n";
    write(1, msg1, 10);
}

// scriere directa in fisier
void func2() {

    int fd1 = open("exemplu.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    const char *msg2 = "bunasiua in fisier\n";
    write(fd1, msg2, 20);
    close (fd1);
}

// citire din fisier
void func3() {

    int fd = open("exemplu.txt", O_RDONLY);
    char buf[128];
    ssize_t n = read(fd, buf, sizeof(buf) - 1);
    write(1, buf, n);
    close(fd);
}

// citire de la tastatura
void func4() {

    char buf[50];
    //write(1, "scrie ceva: ", 13);
    ssize_t n = read(0, buf, sizeof(buf)); // 0 = stdin
    //write(1, "ai scris: ", 10);
    write(1, buf, n);
}

// verificare daca un fisier poate fi deschis
int func5() {
    int fd = open("inexistent.txt", O_RDONLY);
    if(fd < 0) {
        perror("Eroare la open");
        // return 1;
        return errno;
    }
    close(fd);
    return 0;
}

// informatii despre fisier
void func6() {
    struct stat sb;
    if(stat("exemplu.txt", &sb) == 0)
        printf("Dimensiune fisier: %ld bytes\n", sb.st_size);
    else
        perror("Eroare la stat");
}


int main(int argc, char const *argv[]) {

    func1();

    func2(); // creaza exemplu.txt

    func3(); // il citeste

    func6(); // ii afiseaza dimensiunea

    int r = func5(); // eroare intentionata
    printf("func5 a returnat: %d\n", r);

    func4(); // asteapta input de la tastatura

    return 0;
}