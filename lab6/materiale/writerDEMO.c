#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    const char *shm_name = "/myshm";
    const size_t shm_size = 4096;

    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, shm_size);

    void *shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    const char *msg = "Bunasiua din memoria partajata!";
    strcpy((char *)shm_ptr, msg);

    printf("Am scris in memorie: %s\n", (char *)shm_ptr);

    munmap(shm_ptr, shm_size);
    close(shm_fd);

    // nu facem unlink, scopul e sa citeasca si celalalt proces

    return 0;
}
