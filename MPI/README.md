Parcial 2 Introducción a la programación Paralela

Autores: 

2162110 - Oscar Andrés Pérez Carmona
2200134 - Yeferson Valencia Vanegas

Código Postman Sort MPI

Este código utiliza MPI para implementar el algoritmo de ordenamiento Postman, que clasifica números dividiéndolos en grupos según sus dígitos más significativos (MSB) y luego ordenando esos grupos. Inicialmente, se establece la comunicación MPI, obteniendo el número total de procesos y el rango de cada proceso.
El proceso 0 recibe los datos del usuario y los distribuye a todos los procesos mediante la función MPI_Bcast. Luego, se ejecuta el algoritmo Postman, donde cada proceso ordena una parte de los datos. Esto se logra dividiendo los números en grupos basados en sus MSB y ordenando esos grupos.
Finalmente, el código concluye la ejecución de MPI y finaliza. Este enfoque permite el ordenamiento paralelo de datos utilizando el algoritmo Postman en un entorno MPI.
Primero cargar el módulo:  module load devtools/mpi/openmpi/3.1.4
Luego compilar mpic++ PostmanSort_MPI.cpp -o PostmanSort_MPI
ejecutar y guardar la salida mpirun -np 16 ./PostmanSort_MPI > output_PostmanSort_MPI.txt

Output
Process 0 - Unsorted Array:
Process 8 - Unsorted Array:
Process 1 - Unsorted Array:
Process 9 - Unsorted Array:
Process 15 - Unsorted Array:
Process 13 - Unsorted Array:
Process 10 - Unsorted Array:
Process 2 - Unsorted Array:
Process 5 - Unsorted Array:
Process 7 - Unsorted Array:
Process 12 - Unsorted Array:
Process 14 - Unsorted Array:
Process 6 - Unsorted Array:
Process 4 - Unsorted Array:
Process 11 - Unsorted Array:
Process 3 - Unsorted Array:

Sorted Array:
0.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.0000000.000000


Código Binary Search MPI

Este código utiliza MPI para implementar la búsqueda binaria en un conjunto de datos distribuido entre varios procesos.
Se inicia MPI, obteniendo el rango de cada proceso y el número total de procesos.
Se genera un arreglo aleatorio de tamaño 10000 en el proceso 0 y se ordena utilizando el método de ordenación de burbuja.
Se elige aleatoriamente una clave para buscar dentro del arreglo.
La clave se difunde a todos los procesos mediante MPI_Bcast.
El arreglo ordenado se divide y se distribuye entre los procesos utilizando MPI_Scatter.
Cada proceso realiza una búsqueda binaria en su subarreglo local para encontrar la clave.
Si se encuentra la clave, el proceso imprime el índice donde se encontró la clave.
Si no se encuentra la clave en el subarreglo del proceso, el proceso imprime que no se ha encontrado.
Se libera la memoria utilizada y se finaliza MPI.
Este enfoque permite realizar búsquedas paralelas en un conjunto de datos distribuido entre varios procesos utilizando la búsqueda binaria, lo que puede conducir a una mejora en el rendimiento en comparación con un enfoque secuencial.
El algoritmo tarda entre 0,01-0,4 segundos

Output 
Key found at index 442
Time taken: 0.124946 seconds

Conclusiones

En el proceso de paralelización utilizando MPI, conseguimos distribuir eficientemente la carga de trabajo entre los procesos, lo que resultó en una mejora significativa en el tiempo de ejecución en comparación con un enfoque secuencial. Sin embargo, es importante tener en cuenta el costo adicional de la comunicación MPI, que puede afectar el rendimiento en escenarios donde la lista es pequeña o el número de procesos es demasiado grande. Por lo tanto, mientras que MPI puede ser muy útil en ciertos casos, es crucial evaluar las características de cada algoritmo y proceso de paralelización para determinar cuándo es apropiado utilizarlo y cuándo no lo es.