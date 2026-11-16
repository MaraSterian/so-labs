#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    int fd = open("myfifo", O_RDWR);
    char msg[] = "Ping from process 1";
    char buf[100];

    write(fd, msg, strlen(msg) + 1);
    read(fd, buf, sizeof(buf));

    printf("Process1 received: %s\n", buf);
    close(fd);
}