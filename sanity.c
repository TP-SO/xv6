#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  int pid;
  int k, n;
  int mod;

  if(argc < 2)
	n = 3; //Default
  else
	n = atoi(argv[1]);
  n = n * 3;
  pid = 0;

  for ( k = 0; k < n; k++ ) {
    pid = fork ();
    if ( pid < 0 ) {
      printf(1, "%d failed in fork!\n", getpid());
    } else if (pid > 0) {
      // parent
      int retime, rutime, stime;
      while(wait2(&retime, &rutime, &stime) >= 0) 
      printf(1, "%d RUNNABLE: %d \t RUNNING: %d \t SLEEPING: %d\n",pid ,retime, rutime, stime);
    }
    else{
      mod = pid % 3;
      if (mod == 0) {
        for (int i = 0; i < 100; i++) {
          for (int j = 0; j < 1000000; j++) {}
        }
      } else if (mod == 1) {
        for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 1000000; j++) {}
        }
      } else {
        for (int i = 0; i < 100; i++) {
          sleep(1);
        }
      }

      break;
    }
  }
  exit();
}
