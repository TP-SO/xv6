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

  pid = 0;

  for ( k = 0; k < n * 3; k++ ) {
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
    else {

    }
  }

  // parent

  int sum_CPU_retime = 0;
  int sum_CPU_rutime = 0;
  int sum_CPU_stime = 0;

  int sum_S_retime = 0;
  int sum_S_rutime = 0;
  int sum_S_stime = 0;

  int sum_IO_retime = 0;
  int sum_IO_rutime = 0;
  int sum_IO_stime = 0;

  int retime, rutime, stime, last_pid;

  for (int i = 0; i < n * 3; i++) {
    last_pid = wait2(&retime, &rutime, &stime);

    switch(last_pid % 3){
      case 0:
        sum_CPU_retime += retime;
        sum_CPU_rutime += rutime;
        sum_CPU_stime += stime;
        printf(1, "TIPO: CPU-Bound ");
        break;

      case 1:
        sum_S_retime += retime;
        sum_S_rutime += rutime;
        sum_S_stime += stime;
        printf(1, "TIPO: S-CPU ");
        break;

      case 2:
        sum_IO_retime += retime;
        sum_IO_rutime += rutime;
        sum_IO_stime += stime;
        printf(1, "TIPO: IO-Bound ");
        break;
    }

    printf(1, "PID %d RUNNABLE: %d \t RUNNING: %d \t SLEEPING: %d\n",last_pid, retime, rutime, stime);
  }

  printf(1, "PROCESSOS CPU-Bound");
  printf(1, "\nMEDIA RUNNABLE: %d MEDIA RUNNING %d MEDIA SLEEPING %d\n",
         sum_CPU_retime / n, sum_CPU_rutime / n, sum_CPU_stime / n);

  printf(1, "PROCESSOS S-CPU");
  printf(1, "\nMEDIA RUNNABLE: %d MEDIA RUNNING %d MEDIA SLEEPING %d\n",
         sum_S_retime / n, sum_S_rutime / n, sum_S_stime / n);

  printf(1, "PROCESSOS IO-Bound");
  printf(1, "\nMEDIA RUNNABLE: %d MEDIA RUNNING %d MEDIA SLEEPING %d\n",
         sum_IO_retime / n, sum_IO_rutime / n, sum_IO_stime / n);

  exit();
}
