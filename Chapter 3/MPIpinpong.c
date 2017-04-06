#include <stdio.h>
#include <mpi.h>

int main(int argc, char *argv[])
{

  MPI_Status status;
  int num, rank, size, next, from;
  
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
 
  next = (rank + 1) % size;
  from = (rank + size - 1) % size;

  /* En uno de los procesos, el "primario", preguntamos un parametro */
  /*Pregunta pregunta hasta qye rank = 0*/
  if (rank == 0) {
    
	printf("Ping Pong de Procesos:Introduce el Numero: \n");
    scanf("%d", &num);
    printf("Proceso %d envia %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, 0, MPI_COMM_WORLD); 
  }

 

	MPI_Recv(&num, 1, MPI_INT, from, 0, MPI_COMM_WORLD, &status);
    printf("Proceso %d ha recibido %d\n", rank, num);

    

    printf("Proceso %d envia %d al proceso %d\n", rank, num, next);
    MPI_Send(&num, 1, MPI_INT, next, 0, MPI_COMM_WORLD);

  
 	// printf("Proceso %d termina\n", rank);

  /* El proceso "primario debe esperar el ultimo envio del ultimo proceso antes de terminar */


  MPI_Finalize();
  return 0;

  // Comandos:  mpicc -g -Wall -o mpi mpi.c  mpiexec -n 2 ./mpi
}
