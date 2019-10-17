#include "kernel/types.h"
#include "user.h"

char buf[512];
int n;

int main(int argc, char *argv[])  {
    if(fork()) {
        write(1, "Hello ", 6);
    } else {
        wait(0);
        write(1, "world\n", 6);
    }
    exit(0);
}