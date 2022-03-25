#include "stdio.h"
#include "sys/time.h"
#include "inslib.h"
int M = 100;
int N = 100;
void test(){
  int x = 2;
  int A[M*N];
  for (int i = 0;i < N;i++){
    for(int j = 0;j < M;j++){
      A[i*M+j]+=x;
    }
  } 
}
int main()
{
  //insert_begin();
  test(); 
  //insert_end("main",b);
  return 0;
}
