#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    const char *filenames[] = {"file1", "file2", "file3", "file4", "file5"};

    printf("PID: %d\n", getpid());
    fflush(stdout);
    sleep(10);

    for (size_t i = 0; i < 5; i++) {
        printf("Acum incercam sa creem fisierul %s\n", filenames[i]);
        fflush(stdout);

        int rc = open(filenames[i], O_CREAT | O_RDWR, 0644);
        if (rc < 0) {
            perror("open");
        } else {
            printf("Fisier creat cu succes, fd = %d\n", rc);
            fflush(stdout);
        }
        sleep(10);
    }
    return 0;
}