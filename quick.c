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
void QuickSort(int sortdata[], int left, int right) {
  int temp = 0;
  int i = left + 1;
  int k = right;
  
  while (i < k) {
    while (sortdata[i] < sortdata[left] && i < right) i++;
    while (sortdata[k] >= sortdata[left] && k > left) k--;
    if (i < k) {
      temp = sortdata[i];
      sortdata[i] = sortdata[k];
      sortdata[k] = temp;
    }
  }
  if (right-left != 1 || sortdata[left] > sortdata[k]) {
    temp = sortdata[left];
    sortdata[left] = sortdata[k];
    sortdata[k] = temp;
  }
  if (left < k-1)  QuickSort(sortdata, left, k-1);
  if (k+1 < right) QuickSort(sortdata, k+1, right);
  
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
    printf("usage: ./quick [data_init type]\n");
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
  QuickSort(data, 0, DATANUM-1);
  end = get_time();

  /* ----- Show Results ----- */
  for (i = 0; i < SHOWNUM; i++) printf("%d ", data[i]);
  printf("\n");
  printf("# elasped time:%9.3f sec\n", (end - start)/1000000.0);
  
  return 0;
}
/**********************************************************************/
