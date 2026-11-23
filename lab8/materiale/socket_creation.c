#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

int main() {
    int s_tcp, s_udp, s_local;

    // Creare socket TCP IPv4 (AF_INET, SOCK_STREAM, protocol 0 -> TCP)
    // AF_NET = IPv4, SOCK_STREAM = flux de octeti, protocol = 0 -> kernelul alege implicit TCP

    s_tcp = socket(AF_INET, SOCK_STREAM, 0);
    if (s_tcp < 0) {
        perror("socket");
        return errno;
    }

    printf("Socket TCP creat cu descriptorul %d\n", s_tcp);
    

    // Creare socket UDP IPv4 (AF_INET, SOCK_DGRAM, 0 -> UDP)
    // UDP nu este fiabil, nu asigură ordinea pachetelor, trimite mesaje, nu flux continuu
    s_udp = socket(AF_INET, SOCK_DGRAM, 0);
    if (s_udp < 0) {
        perror("socket");
        return errno;
    }

    printf("Socket UDP creat cu descriptorul %d\n", s_udp);


    // Creare socket local AF_UNIX (IPC local cu fisier)
    // folosit pentru IPC rapid,
    // nu folosește TCP/UDP, poate avea adresa intr-un path (ex: /tmp/mysock)
    s_local = socket(AF_UNIX, SOCK_STREAM, 0);
    if (s_local < 0) {
        perror("socket");
        return errno;
    }

    printf("Socket local AF_UNIX creat cu descriptorul %d\n", s_local);

    close(s_tcp);
    close(s_udp);
    close(s_local);

    return 0;
}
