#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    sleep(10);
    const char* filenames[100] = {"file1", "file2", "file3", "file4", "file5"};
    for (size_t i = 0; i < 5; i++)
    {
        printf("Acum incercam sa creem fisierul %s\n", filenames[i]);
        int rc = open(filenames[i], O_CREAT, 0644);
        if (rc) {
            printf("Fisier creat cu succes\n");
        }
        sleep(10);
    }

    sleep(120);
    
    
    return 0;
}
