#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <iostream>
#include <vector>
using  namespace std;
#define m 4  //Filas
#define n 3	//Columnas
int thread_count;

int	matrixA[m][n];
int matrixX[n];
int matrixY[m];//FilasA*ColumnaX ColumnaX=1 

void *Pth_math_vect(void* rank){
    long my_rank = (long) rank;
	cout<<"Thread  con el Id: "<<my_rank<<endl;
    int i,j;
    int local_m = m/thread_count;
    int my_first_row = my_rank * local_m;
    int my_last_row = (my_rank+1) * local_m - 1;

    for(i = my_first_row; i <= my_last_row; i++){
        matrixY[i] = 0.0;
        for(j = 0; j < n; j++){
            matrixY[i] += matrixA[i][j] * matrixX[j];
        }
    }

//    cout<<"Hola del thread "<<my_rank<<" de "<<thread_count<<endl;
	//cout<<endl;
    return NULL;
}

void initMatrix(int matrix[m][n])
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			matrix[i][j]=2;
		}
	}
}
void initX(int *matrix)
{
	for(int i=0;i<n;i++)
	{
		matrix[i]=2;
	}
		
}
void printMatrix(int *matrix)
{
	for(int i=0;i<m;i++)
	{
		cout<<matrix[i]<<"-";
	}
}
int main(int argc, char* argv[]){

	/***************************************************/
	initX(matrixX);
	initMatrix(matrixA);
	/***************************************************/
    long thread;
    thread_count = strtol(argv[1],NULL,10);
    vector<pthread_t> thread_handles(thread_count);
    for(thread=0;thread<thread_count;thread++)
    {
        pthread_create(&thread_handles[thread],NULL,Pth_math_vect,(void*)thread);
    }
	for(thread=0;thread<thread_count;thread++)
    {
        pthread_join(thread_handles[thread],NULL);
    }
	printMatrix(matrixY);
    //free(thread_handles);
    return 0;
}
