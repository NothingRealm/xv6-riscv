#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}


char*
find(char *path, char *found)
{
  
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  char *name = "";

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return "Error";
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return "Error";
  }

  switch(st.type){
  case T_FILE:
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }
	  name = de.name;
	  if(!strcmp(name, found)) {
			char *p = path + strlen(name);
			*p++ = '/';
			strcpy(p, found);
	  		return path;
	  }
	  if(st.type == T_DIR && strcmp(name, ".") && strcmp(name, "..")){
	  	char *founded = find(name, found);
		if(strcmp(founded, "") && strcmp(founded, "Error")) {
			char *p = path + strlen(path);
			*p++ = '/';
			strcpy(p, founded);
			return path;
		}
	  }
	  	
    }
    break;
  }
  return "";
  close(fd);
 }  


int main(int argc, char *argv[]) {
	if(argc != 3) {
		printf("Error 3");
	} else {
		char *x = find(argv[1], argv[2]);
		printf("%s\n", x);
	}
	exit(0);
}
