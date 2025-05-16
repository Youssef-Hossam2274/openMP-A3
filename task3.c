#include <mpi.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int rank, size, N, padded_N;
    int *array = NULL;
    int *local_array = NULL;
    int chunk_size;
    double local_sum = 0.0, global_sum = 0.0;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        printf("Enter the size of the array: ");
        fflush(stdout);
        scanf("%d", &N);
        array = (int *)malloc(N * sizeof(int));

        printf("Enter %d elements:\n", N);
        for (int i = 0; i < N; i++) {
            scanf("%d", &array[i]);
        }

        // Padding logic
        padded_N = (N % size == 0) ? N : N + (size - (N % size));
        array = realloc(array, padded_N * sizeof(int));
        for (int i = N; i < padded_N; i++) {
            array[i] = 0; // pad with 0s
        }
    }

    // Broadcast padded size to all
    MPI_Bcast(&padded_N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    chunk_size = padded_N / size;

    // Allocate local chunk
    local_array = (int *)malloc(chunk_size * sizeof(int));

    // Scatter equal chunks
    MPI_Scatter(array, chunk_size, MPI_INT, local_array, chunk_size, MPI_INT, 0, MPI_COMM_WORLD);

    // Local sum using OpenMP
    #pragma omp parallel for reduction(+:local_sum)
    for (int i = 0; i < chunk_size; i++) {
        local_sum += local_array[i];
    }

    // Reduce to global sum
    MPI_Reduce(&local_sum, &global_sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        printf("Global sum = %.0f\n", global_sum);
        free(array);
    }

    free(local_array);
    MPI_Finalize();
    return 0;
}

