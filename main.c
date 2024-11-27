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
  close(fd);
  return rand % 5 + 1;
}

int main(){
  printf("%d about to create 2 child processes\n",getpid());
  int rand, stat;
  pid_t pid[2];

  if ((pid[0] = fork()) == 0){
    rand = getran();
    printf("PID: %d %d sec\n",getpid(),rand);
    sleep(rand);
    printf("%d finished after %d seconds\n",getpid(),rand);
    exit(rand);
  }
  if ((pid[1] = fork()) == 0){
    rand = getran();
    printf("PID: %d %d sec\n",getpid(),rand);
    sleep(rand);
    printf("%d finished after %d seconds\n",getpid(),rand);
    exit(rand);
  }

  pid_t childpid = waitpid(-1,&stat,0);
  if (WIFEXITED(stat)){
    printf("Main Process %d is done. Child %d slept for %d sec\n",getpid(),childpid,WEXITSTATUS(stat));
  }
  return 0;
}
