#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(){
  int n;
  printf("Enter size of matrix and vector:");
  scanf("%d", &n);
  
  int** matrix = malloc(n * sizeof(int*));
  int* vector = malloc(n * sizeof(int));
  int* result = malloc(n * sizeof(int));
  

  for (int i = 0; i < n; ++i) {
    matrix[i] = malloc(n * sizeof(int));
  }


  printf("Enter matrix elements\n");
  for (int i = 0; i < n; ++i) {
    for(int j = 0; j < n; ++j) {
      scanf("%d", &matrix[i][j]);
    }
  }

  printf("Enter vecotr elements\n");
  for (int i = 0; i < n; ++i) {
    scanf("%d", &vector[i]);
  }

  #pragma omp parallel for
  for (int i = 0; i < n; ++i) {
    result[i] = 0;
    for (int j = 0; j < n; ++j) {
      result[i] += matrix[i][j] * vector[j];
    }
  }
  printf("Resultant vector:\n");

  for (int i = 0; i < n; ++i) {
    printf("%d ", result[i]);
  }



  return 0;
}