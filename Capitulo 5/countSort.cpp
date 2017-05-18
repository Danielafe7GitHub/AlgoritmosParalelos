#include <iostream>
#include <omp.h>

using namespace std;

int numthreads = 500;

void CountsortSecuencial(int a [], int n)
{
    int i , j , count;
    int* temp;
    temp= new int[n];
    for (i = 0; i < n ; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a [i])
                count++;
            else if ( a[j ] == a[i] && j < i)
                count++;
        temp [count] = a [i];
    }
    for (i = 0; i < n; i++)
        a[i] = temp[i];
    free(temp );
}
void countSortParalelo(int a[],int n)
{
    int i, j, count;
    int *temp;
    temp= new int[n];

    #pragma omp parallel for shared(a, n, temp) private(i, j, count)num_threads(numthreads)
        for (i = 0; i < n; i++) {
        count = 0;
        for (j = 0; j < n; j++)
            if (a[j] < a[i])
                count++;
            else if (a[j] == a[i] && j < i)
                count++;
        temp[count] = a[i];
    }

    #pragma omp parallel for shared(a, n, temp) private(i)num_threads(numthreads)
    for (i = 0; i < n; i++)
        a[i] = temp[i];

    free(temp);
}

int compare (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main()
{

    /******************Time Variables*********************************/
    clock_t time;
    int n = 1000;
    int* lista;

    lista= new int[n];

    for (int i = 0; i < n; i++)
        lista[i] = rand()%100;
    for (int i = 0; i < n; i++)
    {
        lista[i] = rand()%100;

    }
    for (int i = 0; i < n; i++)
    {
        cout<<lista[i]<<" ; ";

    }
    cout<<endl;

    time = clock();
    countSortParalelo(lista,n);
    time = clock() - time;

    cout<<"El Tiempo  es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<lista[i]<<" ; ";

    }


    //Tiempos con qsort

   /* time = clock();
    qsort (lista, n, sizeof(int), compare);
    time = clock() - time;

    cout<<"El Tiempo  es: "<<(((float)time)/CLOCKS_PER_SEC)<<endl;

    for (int i = 0; i < n; i++)
    {
        cout<<lista[i]<<" ; ";

    }
    cout<<endl;*/
    return 0;
}