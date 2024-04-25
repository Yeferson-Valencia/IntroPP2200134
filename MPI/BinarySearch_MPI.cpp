#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main(int argc, char *argv[])
{
    srand(time(NULL)); // Inicializar semilla de generación aleatoria
    int rank, size;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    double start_time, end_time;

    const int list_size = 10000; // Tamaño del array
    int key;

    // Generar la clave de búsqueda aleatoriamente en el proceso 0
    if (rank == 0) {
        key = rand() % 100; // Generar una clave de búsqueda aleatoria entre 0 y 99
    }

    start_time = MPI_Wtime(); // Marcar el inicio del tiempo de ejecución

    // Transmitir la clave de búsqueda a todos los procesos
    MPI_Bcast(&key, 1, MPI_INT, 0, MPI_COMM_WORLD);

    // Calcular el tamaño local del array para cada proceso
    int local_size = list_size / size + (rank < list_size % size ? 1 : 0);
    int *local_list = (int *)malloc(local_size * sizeof(int));

    // Generar elementos del array aleatoriamente en cada proceso
    for (int i = 0; i < local_size; i++) {
        local_list[i] = rand() % 100; // Generar números aleatorios entre 0 y 99
    }

    // Cada proceso ordena su parte del array
    bubble_sort(local_list, local_size);

    // Combinar los arrays locales para obtener un array global en el proceso 0
    int *list = NULL;
    if (rank == 0) {
        list = (int *)malloc(list_size * sizeof(int));
    }
    MPI_Gather(local_list, local_size, MPI_INT, list, local_size, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        // Realizar la búsqueda binaria
        binary_search(list, 0, list_size - 1, key);
        end_time = MPI_Wtime(); // Marcar el final del tiempo de ejecución
        printf("Time taken: %f seconds\n", end_time - start_time); // Imprimir el tiempo de ejecución
        free(list);
    }

    free(local_list);
    MPI_Finalize();
    return 0;
}

void bubble_sort(int list[], int size)
{
    int temp, i, j;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (list[j] > list[j + 1])
            {
                temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void binary_search(int list[], int lo, int hi, int key)
{
    int mid;

    while (lo <= hi)
    {
        mid = (lo + hi) / 2;
        if (list[mid] == key)
        {
            printf("Key found\n");
            return;
        }
        else if (list[mid] < key)
        {
            lo = mid + 1;
        }
        else
        {
            hi = mid - 1;
        }
    }

    printf("Key not found\n");
}
