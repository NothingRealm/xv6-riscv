#include "kernel/types.h"
#include "user.h"


int main(int argc, char *argv[])  {
    int p[2];
    pipe(p);
    if(fork() == 0) {
        char* arg[2];
        arg[0] = "wc";
        arg[1] = 0;
        close(0);
        dup(p[0]);
        close(p[0]);
        close(p[1]);
        // char buf[512];
        exec("wc", arg);
        // read(p[0], buf, sizeof buf);
        // printf("%s",buf);
    } else {
        write(p[1], "hello world\n", 12);
        close(p[0]);
        close(p[1]);
        wait(0);
    }
    exit(0);
}