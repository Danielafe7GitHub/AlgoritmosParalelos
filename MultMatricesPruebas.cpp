#include <iostream>
using namespace std;

#define BlockSize  590 /*Tam de la Matriz*/

#define filaM1 BlockSize
#define columnaM1 BlockSize

#define filaM2 BlockSize
#define columnaM2 BlockSize

void imprimirMatrizM1(int matriz[filaM1][columnaM1])
{
    for(int i=0; i<filaM1;i++)
    {
        for(int j=0; j<columnaM1; j++)
        {
            cout <<"["<<matriz[i][j]<<"] ";
        }
        cout<<endl;
    }
}

void imprimirMatrizM2(int matriz[filaM2][columnaM2])
{
    for(int i=0; i<filaM2;i++)
    {
        for(int j=0; j<columnaM2; j++)
        {
            cout <<"["<<matriz[i][j]<<"] ";
        }
        cout<<endl;

    }
}

void imprimirMatrizM3(int matriz[filaM1][columnaM2])
{
    for(int i=0; i<filaM1;i++)
    {
        for(int j=0; j<columnaM2; j++)
        {
            cout <<"["<<matriz[i][j]<<"] ";
        }
        cout<<endl;

    }
}

/* Multiplicación de Matrices 3 bucles Anidados */
void multMatrix( int a[filaM1][columnaM1],int b[filaM2][columnaM2])
{
    int c[filaM1][columnaM2];
    for( int i=0;i<filaM1;++i)
    {
        for(int j=0;j<columnaM2;++j)
        {
            for(int k=0;k<filaM2;++k)
            {

                if(k==0)
                {
                    c[i][j] = a[i][k] * b[k][j];
                    //cout<<"Dato "<<c[i][j]<<endl;

                }
                else
                {
                    c[i][j] = c[i][j] + a[i][k] * b[k][j];
                    //cout<<"Dato "<<c[i][j]<<endl;


                }
            }
        }
    }
    //imprimirMatrizM3(c);
    //return *c;
}



/*Multiplicación de Matrices Versión Blocked*/
void multMatrixBlocked( int b[filaM1][columnaM1],int c[filaM2][columnaM2],int blockSize)
{
    int a[filaM1][columnaM2];
    int n= filaM1;
    int i, j, k, iInner, jInner, kInner ;
    for (i = 0; i < n; i+=blockSize)
        for (k = 0 ; k < n; k+=blockSize)
            for (j=0; j<n ; j+= blockSize)
                for (iInner = i; iInner<i+blockSize; iInner++)
                    for (kInner = k ; kInner<k+blockSize ; kInner++)
                        for (jInner = j ; jInner<j+blockSize; jInner++)
                        {
                            if(kInner==0)
                            {
                                a[iInner][jInner] = b[iInner][kInner] * c[kInner][jInner] ;
                            }
                            else
                                a[iInner][jInner] += b[iInner][kInner] * c[kInner][jInner] ;

                        }


    //imprimirMatrizM3(a);


}



int main() {

    int M1[BlockSize][BlockSize];
    int M2[BlockSize][BlockSize];
    for(int i=0;i<BlockSize;i++)
        for(int j=0;j<BlockSize;j++)
            M1[i][j]=2;

    for(int i=0;i<BlockSize;i++)
        for(int j=0;j<BlockSize;j++)
            M2[i][j]=3;

    clock_t start, end;
    cout<<"Tu primera Matriz es: "<<endl;
    //imprimirMatrizM1(M1);
    cout<<"Tu segunda Matriz es: "<<endl;
    //imprimirMatrizM2(M2);
    cout<<"Multiplicacion 3 Bucles Anidados"<<endl;
    start = clock();
    multMatrix(M1,M2);
    end = clock();
    printf("El tiempo es: %f\n", (end - start) / 1000.0);
    cout<<"Multiplicacion Blocked Version"<<endl;
    start = clock();
    multMatrixBlocked(M1,M2,590);
    end = clock();
    printf("El tiempo es: %f\n", (end - start) / 1000.0);


    return 0;
}