#include <stdio.h>
#include <omp.h>

void binary_search(int [], int, int, int);
void bubble_sort(int [], int);

int main()
{
    int key = 7; // Número a buscar
    int size = 10; // Tamaño de la lista
    int list[] = {9, 2, 6, 1, 8, 3, 10, 7, 4, 5}; // Lista desordenada

    // Paralelizar el ordenamiento de la lista
    bubble_sort(list, size);

    printf("Lista ordenada: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");

    // Buscar el número utilizando búsqueda binaria
    binary_search(list, 0, size, key);

    return 0;
}

void bubble_sort(int list[], int size){
    int i=0, j=0;
    int first;

    for(i = 0; i < size-1; i++) {
        first = i % 2; 

        #pragma omp parallel for default(none),shared(list,first,size)
        for(j = first; j < size-1; j += 2) {
            if(list[j] > list[j+1]) {
                // Intercambiar elementos
                int tmp = list[j];
                list[j] = list[j+1];
                list[j+1] = tmp;
            }
        }
    }
}

void binary_search(int list[], int lo, int hi, int key)
{
    int mid;
    if (lo > hi)
    {
        printf("Key not found\n");
        return;
    }
    mid = (lo + hi) / 2;
    if (list[mid] == key)
    {
        printf("Key found at index: %d\n", mid);
    }
    else if (list[mid] > key)
    {
        binary_search(list, lo, mid - 1, key);
    }
    else if (list[mid] < key)
    {
        binary_search(list, mid + 1, hi, key);
    }
}

