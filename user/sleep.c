#include "kernel/types.h"
#include "user.h"

int main(int argc, char *argv[])  {
    
    int Sleep_Sec = atoi(argv[1]);
    if (argc == 2 && (Sleep_Sec > 0 || *argv[1] == '0')) {
        Sleep_Sec *= 10;
        sleep(Sleep_Sec);
    } else if (argc == 1) {
        printf("usage: sleep for n second.\n");
    } else {
        printf("Wrong input !!!.\n");
    }
    exit(0);

}