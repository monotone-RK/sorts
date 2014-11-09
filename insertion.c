/**********************************************************************/
/* Measurement of Sort Process Time                       monotone-RK */
/*                                                         2014-11-09 */
/**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#define L_NAME "Measurement of Sort Process Time Ver 1.0"
#define RANGE   100000000
#define MIN     0
#define MAX     (RANGE - 1)
#ifndef DATANUM
#define DATANUM 32*1024*1024  // 32M * 4 = 128MB
#endif
#define SHOWNUM 100

int data[DATANUM]; // data to be sorted

/** function to return the current time                              **/
/**********************************************************************/
long long get_time() {
  struct timeval  tp;
  struct timezone tz;
  gettimeofday(&tp, &tz);
  return tp.tv_sec * 1000000ull + tp.tv_usec;
}

/**********************************************************************/
void InsertionSort(int sortdata[], int left, int right) {
  int i;
  
  for (i = left+1; i < right+1; i++) {
    int temp = sortdata[i];
    int emptyIndex = i;
    while (emptyIndex > 0 && sortdata[emptyIndex-1] > temp) {
      sortdata[emptyIndex] = sortdata[emptyIndex-1];
      emptyIndex--;
    }
    sortdata[emptyIndex] = temp;
  }
}

/**********************************************************************/
int GetRandom(int min, int max) {
  return min + (int)(rand()*(max-min+1.0)/(1.0+RAND_MAX));
}

/**********************************************************************/
void data_init(char type[]) {
  int i;
  srand(1);

  if      (!strcmp(type, "random"))  for (i = 0; i < DATANUM; i++) data[i] = GetRandom(MIN, MAX);
  else if (!strcmp(type, "sorted"))  for (i = 0; i < DATANUM; i++) data[i] = i;
  else if (!strcmp(type, "reverse")) for (i = 0; i < DATANUM; i++) data[i] = DATANUM-i;
  else                               { printf("data_init type is wrong.\n"); exit(1); }
}

/**********************************************************************/
int main(int argc, char *argv[]) {

  if (argc == 1) {
    printf("%s\n", L_NAME);
    printf("usage: ./insertion [data_init type]\n");
    printf(" data_init type : random, sorted, reverse\n");
    exit(1);
  }

  if (argc != 2) {
    printf("Error! The number of argument is wrong.\n");
    exit(1);
  }
  
  int i;
  long long start;
  long long end;

  /* ----- Initialization ----- */
  printf("# sort elements n = %d\n",  DATANUM);
  data_init(argv[1]);
  for (i = 0; i < SHOWNUM; i++) printf("%d ", data[i]);
  printf("\n");

  /* ----- Measurement of Sort Process Time ----- */
  start = get_time();
  InsertionSort(data, 0, DATANUM-1);
  end = get_time();

  /* ----- Show Results ----- */
  for (i = 0; i < SHOWNUM; i++) printf("%d ", data[i]);
  printf("\n");
  printf("# elasped time:%9.3f sec\n", (end - start)/1000000.0);
  
  return 0;
}
/**********************************************************************/
