#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    // Taking array size
    int n;
    printf("Enter array size\n> ");
    scanf("%d", &n);
    
    // Taking array elements
    int* arr = malloc(n * sizeof(int));
    printf("Enter array elements\n> ");
    for (int i = 0; i < n; ++i) {
        scanf("%d", arr + i);
    }

    // Computing sum
    int sum = 0;
    #pragma omp parallel for 
    for (int i = 0; i < n; ++i) {
        sum += arr[i];
    }

    // Computing mean & variance
    double mean = 1.0*sum / n;
    double variance = 0;

    #pragma omp parallel for 
    for (int i = 0; i < n; ++i) {
        variance += (arr[i] - mean) * (arr[i] - mean);
    }
    
    variance /= n;

    // Finally std_deviation
    double std_deviation = sqrt(variance);

    printf("\nFinal Standard Deviation = %.8f\n", std_deviation);
}
