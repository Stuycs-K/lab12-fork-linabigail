#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(){
  pid_t child1 = fork();
  pid_t child2 = fork();
  if (child1 < 0 || child2 < 0){
    perror("fork failed.\n");
    exit(1);
  }
  int fd = open("/dev/urandom", O_RDONLY);
  int rand;
  read(fd,&rand,sizeof(rand));
  rand = rand % 5 + 1;
  printf("PID: %d Randon Number: %d\n",getpid(),rand);
  sleep(rand);
  printf("");
  return 0;
}
