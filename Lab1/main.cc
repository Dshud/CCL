#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

#include "sudoku.h"
#include "ThreadPool.h"

int64_t now()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec * 1000000 + tv.tv_usec;
}


int main(int argc, char* argv[])
{
  init_neighbors();
  FILE* fp = fopen(argv[1], "r");
  char puzzle[128];
  int total_solved = 0;
  int total = 0;
  //int64_t start = now();
  while (fgets(puzzle, sizeof puzzle, fp) != NULL) {
    if (strlen(puzzle) >= N) {
      ++total;
      input(puzzle);
      }
      else {
        printf("No: %s", puzzle);
      }
  }
  
  ThreadPool pool(THREADNUM);
  while(!puzzleSet.empty()){
    pool.enqueue(solveSudoku);
  }
  //exit(1);
  //int64_t end = now();
  //double sec = (end-start)/1000000.0;
  //printf("%f sec %f ms each %d\n", sec, 1000*sec/total, total_solved);
  return 0;
}

