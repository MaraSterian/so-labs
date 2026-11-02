#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>

int main(int argc, char const *argv[])
{
    // ANTETUL FUNCTIEI: int shm_open(const char *path, int flags, mode_t mode);

    char shm_name[] = "/myshm";
    int shm_fd;

    // semantica aproape identica cu syscall-ul open(2), 
    // shm_open(3) fiind doar un wrapper peste aceasta
    shm_fd = shm_open (shm_name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    
    // verificam ca shm_open s-a executat fara erori
    if (shm_fd < 0) {
        perror (NULL);
        return errno;
    }

    // definirea dimensiunii cu ajutorul functiei ftruncate(2)
    size_t shm_size = 1000;
    
    if (ftruncate (shm_fd, shm_size) == -1) {
        perror (NULL);
        // extinderea syscall-ului unlink(2) care sterge fisiere de pe disk
        shm_unlink (shm_name);
        return errno;
    }
    // memoria partajata se incarca in spatiul procesului cu ajutorul syscall
    // void *mmap (void *addr, size_t len, int prot, int flags, int fd, off_t offset);
    
    // addr = adresa la care sa fie incarcata in proces - 0, pentru a lasa kernelul sa decida
    // len = dimensiunea memoriei incarcate (shm_size in cazul nostru)
    // prot = drepturi de access (PROT_READ - pages may be read, PROT_WRITE - pages may be written)
    // flags = tipul de memorie (MAP_SHARED - modificarile pot fi vizibile si in celelalte procese)
    // fd = descriptorul obiectului de memorie
    // offset = locul in obiectul de memorie partajata de la care sa fie incarcat in spatiul procesului
    
    void *shm_ptr = mmap (0, shm_size, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror (NULL);
        shm_unlink (shm_name);
        return errno ;
    }

    // void *shm_ptr = mmap (0, 100, PROT_WRITE, MAP_SHARED, shm_fd, 500);
    // if (shm_ptr == MAP_FAILED) {
    //     perror (NULL);
    //     shm_unlink (shm_name);
    //     return errno ;
    // }

    // cand nu mai e nevoie de zona de memorie, se foloseste syscall-ul munmap(2)
    // int munmap (void *addr, size_t len);

    munmap (shm_ptr, shm_size);
    // munmap (shm_ptr, 100);
    return 0;
}
