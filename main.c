#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int getran(){
  int fd = open("/dev/urandom", O_RDONLY);
  if (fd < 0) {
    perror("/dev/urandom failed.");
    exit(1);
  }
  unsigned int rand;
  read(fd,&rand,sizeof(rand));
  return rand % 5 + 1;
}

int main(){
  pid_t child1 = fork();
  if (child1 < 0){
    perror("fork failed.");
    exit(1);
  }
  if (child1 == 0){
    int rand = getran();
    printf("PID: %d Randon Number: %d\n",getpid(),rand);
    sleep(rand);
    printf("%d finished after %d seconds\n",getpid(),rand);
    exit(0);
  }
  pid_t child2 = fork();
  if (child2 < 0){
    perror("fork failed.");
    exit(1);
  }
  if (child2 == 0){
    int rand = getran();
    printf("PID: %d Randon Number: %d\n",getpid(),rand);
    sleep(rand);
    printf("%d finished after %d seconds\n",getpid(),rand);
    exit(0);
  }
  wait(NULL);
  wait(NULL);
  return 0;
}
