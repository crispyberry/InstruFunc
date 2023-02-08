#include "inslib.h"
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#define N 200
#define M 300
#define K 400

void matmul(float A[N][K], float B[K][M], float C[N][M]) {
  int i, j, k;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < K; k++) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }
}

void random_init(float A[N][K], float B[K][M], float C[N][M]){
  srand(time(NULL));
  int i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < K; j++)
      A[i][j] = static_cast<float>(rand()) / RAND_MAX;
  for (i = 0; i < K; i++)
    for (j = 0; j < M; j++)
      B[i][j] = static_cast<float>(rand()) / RAND_MAX;
  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++)
      C[i][j] = static_cast<float>(rand()) / RAND_MAX;
}

static void print_array(
    float D[N][M])
{
  int i, j;

  for (i = 0; i < N; i++)
    for (j = 0; j < M; j++) {
      fprintf (stderr, "%0.2lf ", D[i][j]);
      if ((i * N + M) % 20 == 0) fprintf (stderr, "\n");
    }
  fprintf (stderr, "\n");
}

int main(){
    float A[N][K];
    float B[K][M];
    float C[N][M];
    random_init(A, B, C);
    matmul(A, B, C);
    print_array(C);
    return 0;
}