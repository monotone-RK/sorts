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
int temp[DATANUM];
void MergeSort(int sortdata[], int left, int right) {
  
  if (left >= right) return;
  
  int mid, i, j, k;
  
  mid = (left + right) / 2;
  MergeSort(sortdata, left, mid);
  MergeSort(sortdata, mid + 1, right);
  
  for (i = left; i <= mid; i++)                temp[i] = sortdata[i];
  for (i=mid+1, j=right; i <= right; i++, j--) temp[i] = sortdata[j];
  
  i = left;  
  j = right; 
  for (k = left; k <= right; k++) {
    if (temp[i] <= temp[j]) sortdata[k] = temp[i++];
    else                    sortdata[k] = temp[j--];
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
    printf("usage: ./merge [data_init type]\n");
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
  MergeSort(data, 0, DATANUM-1);
  end = get_time();

  /* ----- Show Results ----- */
  for (i = 0; i < SHOWNUM; i++) printf("%d ", data[i]);
  printf("\n");
  printf("# elasped time:%9.3f sec\n", (end - start)/1000000.0);
  
  return 0;
}
/**********************************************************************/
