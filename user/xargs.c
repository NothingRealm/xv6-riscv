#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX 100

int main(int argc, char *argv[]) {
	char buf[MAX] = " ";
	//printf("%d	%s	%s \n", argc, argv[1], argv[2]);
	
	while(strcmp(buf, "")) {
		gets(buf, MAX);
		if (strcmp(buf, "")) {
			int pid = fork();
			if (pid == 0) {
			int x = strlen(buf);
			buf[x - 1] = '\0';
			char *arg[argc] ;
			for (int i = 0; i < argc - 1; i++) {
				arg[i] = argv[i + 1];
//				printf("%s\n", arg[i]);
			}
			arg[argc - 1] = buf;
			arg[argc] = "";
//			printf("%s\n", arg[argc]);
//			for (int i = 0; i < argc; i++) {
//				printf("%s\n", arg[i]);
//			}
			argv[argc - 1] = buf;
			exec(argv[1], arg);
			exit(0);
			}
		 else if(pid > 0) {
			wait(0);
			}
		}	
	}


	exit(0);

}
