#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[]) {
    printf("boo the pid is: %d\n", getpid());
    int pid = fork();
    sleep(10); // I added this to see the prints respectively you can uncomment it to watch the parent and child proc running concurently
    printf("The pid is: %d\n", getpid());
    if(pid > 0) {
        printf("parent: child = %d\n", pid);
        pid = wait(0);
        printf("childe %d is done\n", pid);
    } else if(pid == 0) {
        printf("child: exiting\n");
        exit(0);
    } else {
        printf("fork error\n");
    }
    printf("Im here\n");
    exit(0);
}