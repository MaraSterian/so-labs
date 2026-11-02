#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    const char *shm_name = "/myshm";
    const size_t shm_size = 4096;

    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    void *shm_ptr = mmap(NULL, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);

    printf("Am citit din memorie: %s\n", (char *)shm_ptr);

    munmap(shm_ptr, shm_size);
    close(shm_fd);

    // Curatam resursa
    shm_unlink(shm_name);
    return 0;
}
