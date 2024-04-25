#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

void arrange(int, int);
int original_array[100], sorted_array[100];
int i, j, temp, max, count, maxdigits = 0, c = 0;

int main(int argc, char** argv) {
    // Inicializa MPI
    MPI_Init(NULL, NULL);

    // Obtiene el número total de procesos
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Obtiene el rango del proceso actual
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int t1, t2, k, t, n = 1;

    // El proceso 0 recibe los datos del usuario
    if (world_rank == 0) {
        printf("Enter size of array :");
        scanf("%d", &count);
        printf("Enter elements into array :");
        for (i = 0; i < count; i++)
        {
            scanf("%d", &original_array[i]);
            sorted_array[i] = original_array[i];            
        }
    }

    // Se envían los datos a todos los procesos
    MPI_Bcast(&count, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Bcast(original_array, count, MPI_INT, 0, MPI_COMM_WORLD);

    // Aquí comienza el algoritmo de ordenamiento Postman
    // Cada proceso ordena su parte del array en paralelo

    for (i = 0; i < count; i++)
    {
        t = original_array[i];        /*primer elemento en t */
        while(t > 0)
        {
            c++;
            t = t / 10;        /* Encuentra el dígito más significativo */
        }
        if (maxdigits < c) 
            maxdigits = c;   /* número de dígitos de cada número */
        c = 0;
    }
    while(--maxdigits) 
        n = n * 10;      

    for (i = 0; i < count; i++)
    {
        max = original_array[i] / n;        /* DMS - Dividiendo por la base particular */
        t = i;
        for (j = i + 1; j < count;j++)    
        {
            if (max > (original_array[j] / n))
            {
                max = original_array[j] / n;   /* DMS más grande */
                t = j;
            }
        }
        temp = sorted_array[t];
        sorted_array[t] = sorted_array[i];
        sorted_array[i] = temp;
        temp = original_array[t];
        original_array[t] = original_array[i];
        original_array[i] = temp;
    }
    while (n >= 1)
    {
        for (i = 0; i < count;)
        {
            t1 = original_array[i] / n;
            for (j = i + 1; t1 == (original_array[j] / n); j++);
                arrange(i, j);
            i = j;
        }
        n = n / 10;
    }
    if (world_rank == 0) {
        printf("\nSorted Array (Postman sort) :");    
        for (i = 0; i < count; i++)
            printf("%d ", sorted_array[i]);
        printf("\n");
    }

    // Finaliza MPI
    MPI_Finalize();
}

/* Función para organizar la secuencia que tiene la misma base */
void arrange(int k, int n) {
    int *indices = (int *)malloc((n - k) * sizeof(int));

    // Almacenar los índices originales antes de ordenar sorted_array
    for (i = k; i < n; i++) {
        indices[i - k] = i;
    }

    // Ordenar los índices basados en el orden de sorted_array
    for (i = k; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (sorted_array[indices[i - k]] > sorted_array[indices[j - k]]) {
                temp = indices[i - k];
                indices[i - k] = indices[j - k];
                indices[j - k] = temp;
            }
        }
    }

    // Reorganizar original_array basado en los índices ordenados
    for (i = k; i < n; i++) {
        temp = original_array[indices[i - k]];
        original_array[indices[i - k]] = original_array[i];
        original_array[i] = temp;
    }

    free(indices);
}
