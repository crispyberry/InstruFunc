#include "inslib.h"
int counter=0;
void insert_mem(){
  counter++;
}
long insert_begin()
{
  struct timeval star;
  gettimeofday(&star, NULL);
  long b = star.tv_sec * 1000000 + star.tv_usec;
  return b;
}

void insert_end(char *name, long b)
{
  struct timeval end;
  gettimeofday(&end, NULL);
  long e = end.tv_sec * 1000000 + end.tv_usec;
  long t = e - b;
  printf("%s %ld us\n",name, t);
}
