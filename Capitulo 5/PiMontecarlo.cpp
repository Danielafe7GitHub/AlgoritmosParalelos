#include <iostream>
#include <cmath>
#include <omp.h>

using namespace std;

int numRocas = 100000;				//Núm de Roquitas que s van a lanzar
double x,y;
int i;
double contador = 0.0;				//Nún de Roquitas que entraron a la circunferencia
double distancia;
double pi;
int numthreads = 16;

double monteCarloPi()
{

    //No hay dependencia en el For, pues aunque el thread 1 se encuentre con el valor de X de thread 0, son Núm aleatorios
    #pragma omp parallel firstprivate(x, y, distancia, i) reduction(+:contador) num_threads(numthreads)
    {
        srand48((int)time(NULL) ^ omp_get_thread_num());	//Para obtener núm aleatorios
        for (i=0; i<numRocas; ++i)
        {
            x = (double)drand48();
            y = (double)drand48();
            distancia = sqrt((x*x)+(y*y));
            if (distancia<=1)
            {
                contador++;
            }
        }
    }
    //pi = 4.0*((double)count/(double)(niter*numthreads));
    pi = 4.0 * contador/((double) numRocas*numthreads);
    return pi;


}



int main() {
    cout<<"El valor de pi es: "<<endl;
    cout<<monteCarloPi()<<endl;
    return 0;
}