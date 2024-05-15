#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int main(int argc, char *argv[]) {
  int pid;
  int k, n;
  int mod;

  int sum_retime = 0;
  int sum_rutime = 0;
  int sum_stime = 0;

  /* double mean_retime; */
  /* , mean_rutime, mean_stime; */

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
    }
    else if (pid == 0) {
      mod = getpid() % 3;
      if (mod == 0) {
        for (int i = 0; i < 100; i++) {
          for (int j = 0; j < 1000000; j++) {}
        }
      } else if (mod == 1) {
        for (int i = 0; i < 20; i++) {
          for (int j = 0; j < 1000000; j++) {}
          yield();
        }
      } else {
        for (int i = 0; i < 100; i++) {
          sleep(1);
        }
      }

      exit();
    }
  }


  // parent
  int retime, rutime, stime;
  while(wait2(&retime, &rutime, &stime) >= 0) {
    sum_retime += retime;
    sum_rutime += rutime;
    sum_stime += stime;
    printf(1, "RUNNABLE: %d \t RUNNING: %d \t SLEEPING: %d\n",retime, rutime, stime);
  }

  /* mean_retime = (double)sum_retime / n; */

  printf(1, "\nMÈDIA RUNNABLE: %f MÉDIA RUNNING %f MÉDIA SLEEPING %f\n", 
         (double)sum_retime / n, (double)sum_rutime / n, (double)sum_stime / n);


  exit();
}
