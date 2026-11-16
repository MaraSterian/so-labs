#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd = open("myfifo", O_RDWR);
    char buf[100];

    read(fd, buf, sizeof(buf));
    printf("Process2 received: %s\n", buf);

    char reply[] = "Pong from process 2";
    write(fd, reply, strlen(reply) + 1);

    close(fd);
}
