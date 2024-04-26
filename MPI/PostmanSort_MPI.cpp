#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void arrangeItems(int [], int [], int, int);
int len;

int main(int argc, char *argv[]){
    setenv("OMPI_MCA_btl", "^openib", 1);
    setenv("OMPI_MCA_orte_base_help_aggregate", "0", 1);
    int rank, size, start_time, end_time, total_time;
    int i, j, c, t, k, n = 1, max, maxd=0, temp;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Size of the array to sort...
    len = 100000;

    MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int *arr = (int *)malloc(len * sizeof(int));
    int *arr1 = (int *)malloc(len * sizeof(int));

    srand(rank); // Seed rand() with process rank for different random values

    // Automatically fill the array with random values
    for (i = 0; i < len; i++) {
        arr[i] = rand() % 100; // Generate a random number between 0 and 99
    }

    printf("Process %d - Unsorted Array:\n", rank);
    //for (i = 0; i < len; i++)
        //printf("%d ", arr[i]);
    printf("\n");

    MPI_Barrier(MPI_COMM_WORLD);

    start_time = MPI_Wtime();

    int local_len = len / size;
    int *local_arr = (int *)malloc(local_len * sizeof(int));

    MPI_Scatter(arr, local_len, MPI_INT, local_arr, local_len, MPI_INT, 0, MPI_COMM_WORLD);

    // Sort local array
    for (i = 0; i < local_len; i++) {
        t = local_arr[i];
        c = 0;
        while (t > 0) {
            c++;
            t = t / 10;
        }
        if (maxd < c)
            maxd = c;
        c = 0;
    }
    while (--maxd)
        n = n * 10;

    for (i = 0; i < local_len; i++) {
        max = local_arr[i] / n;
        t = i;

        for (j = i + 1; j < local_len; j++) {
            if (max > (local_arr[j] / n)) {
                max = local_arr[j] / n;
                t = j;
            }
        }

        temp = local_arr[t];
        local_arr[t] = local_arr[i];
        local_arr[i] = temp;
    }
    while (n >= 1) {
        for (i = 0; i < local_len;) {
            t = local_arr[i] / n;
            for (j = i + 1; t == (local_arr[j] / n); j++);
                arrangeItems(local_arr, local_arr, i, j);
            i = j;
        }
        n = n / 10;
    }

    MPI_Gather(local_arr, local_len, MPI_INT, arr1, local_len, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Final sorting
        arrangeItems(arr, arr1, 0, len);

        printf("Sorted Array:\n");
        //for (i = 0; i < len; i++)
            //printf("%d ", arr1[i]);
        printf("\n");
    }
    end_time = MPI_Wtime();
    total_time = end_time - start_time; 
    printf("%f", total_time);

    free(arr);
    free(arr1);
    free(local_arr);

    MPI_Finalize();

    return 0;
}
void arrangeItems(int arr[], int arr1[], int k, int n){
    int temp = 0;
    int i = 0;
    int j = 0;

    for (i = k; i < n - 1 && i < len; i++) {
        for (j = i + 1; j < n && j < len; j++) {
            if (arr1[i] > arr1[j]) {
                temp = arr1[i];
                arr1[i] = arr1[j];
                arr1[j] = temp;

                temp = (arr[i] % 10);
                arr[i] = (arr[j] % 10);
                arr[j] = temp;
            }
        }
    }
}
