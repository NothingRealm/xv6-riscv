#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv) {
    int p[2];
    pipe(p);
    if (fork() == 0) {
        int buffer[256];
        read(p[0], buffer, sizeof buffer);
        printf("%d: received %s\n", getpid(), buffer);
        write(p[1], "pong\n", 4);
    } else {
        int buffer[256];
        write(p[1], "ping\n", 4);
        read(p[0], buffer, sizeof buffer);
        printf("%d: received %s\n", getpid(), buffer);
    }
    exit(0);
}