Código Postman Sort MPI

Este código utiliza MPI para implementar el algoritmo de ordenamiento Postman, que clasifica números dividiéndolos en grupos según sus dígitos más significativos (MSB) y luego ordenando esos grupos. Inicialmente, se establece la comunicación MPI, obteniendo el número total de procesos y el rango de cada proceso.
El proceso 0 recibe los datos del usuario y los distribuye a todos los procesos mediante la función MPI_Bcast. Luego, se ejecuta el algoritmo Postman, donde cada proceso ordena una parte de los datos. Esto se logra dividiendo los números en grupos basados en sus MSB y ordenando esos grupos.
Finalmente, el código concluye la ejecución de MPI y finaliza. Este enfoque permite el ordenamiento paralelo de datos utilizando el algoritmo Postman en un entorno MPI.



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
El algoritmo tarda entre 0,01-0,004 segundos.