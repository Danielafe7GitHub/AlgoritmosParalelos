#include <stdio.h>
#include <string.h>
#include <mpi.h>

const int MAX_STRING = 100;

int main(void)
{
    char saludos[MAX_STRING];
    int num_procesos;
    int id_procesos; /*My Rank*/
	
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD , &num_procesos);
    MPI_Comm_rank(MPI_COMM_WORLD , &id_procesos );

	printf("Info numProcesos %d y MyRank %d!\n",num_procesos,id_procesos);
    if(id_procesos != 0)
    {
		printf("entramos al IF \n");
        sprintf(saludos," Saludos desde IF del proceso %d al %d!",id_procesos,num_procesos);
        MPI_Send(saludos,strlen(saludos)+1, MPI_CHAR , 0, 0, MPI_COMM_WORLD);        
    }
    else
    {
		printf("entramos al else \n");
        printf("Saludos dede ELSE del proceso %d al %d!\n",id_procesos,num_procesos);
        for(int q=1; q< num_procesos;q++)
		//for(int q=num_procesos-1; q> 0;q--)
        {
            MPI_Recv(saludos,MAX_STRING,MPI_CHAR,q,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            printf("%s\n",saludos);
        }
    }
    
    MPI_Finalize();
    return 0;

}


