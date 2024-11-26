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
  // printf("random number: %d\n",rand%5+1);
  return rand % 5 + 1;
}

int main(){
  printf("%d about to create 2 child processes\n",getpid());
  int rand, stat;
  pid_t pid[2];
  // pid_t child1 = fork();
  // if (child1 < 0){
  //   perror("fork failed.");
  //   exit(1);
  // }
  // if (child1 == 0){
  //   rand = getran();
  //   printf("PID: %d %d sec\n",getpid(),rand);
  //   sleep(rand);
  //   printf("%d finished after %d seconds\n",getpid(),rand);
  //   exit(rand);
  // }

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

  // pid_t child2 = fork();
  // if (child2 < 0){
  //   perror("fork failed.");
  //   exit(1);
  // }
  // if (child2 == 0){
  //   rand = getran();
  //   printf("PID: %d %d sec\n",getpid(),rand);
  //   sleep(rand);
  //   printf("%d finished after %d seconds\n",getpid(),rand);
  //   exit(rand);
  // }
  // for (int i = 0; i < 2; i++){
    pid_t childpid = waitpid(-1,&stat,0);
    if (WIFEXITED(stat)){
      // pid_t childpid = wait(NULL);
      printf("Main Process %d is done. Child %d slept for %d sec\n",getpid(),childpid,WEXITSTATUS(stat));
      return 0;
    }
  // }
  // pid_t childpid = wait(NULL);
  // printf("Main Process %d is done. Child %d slept for %d sec\n",getpid(),childpid,rand);
  // wait(NULL);
  return 0;
}
