#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
int threads = 3;
int a,b,c = 0;
vector<int> doChunks(string subCadena)
{
    int a,b,c;
    vector<int> numCaracteres;

    for(int i=0; i<subCadena.size();i++)
    {
        if(subCadena[i] == 'a')
            a++;
        if(subCadena[i] == 'b')
            b++;
        if(subCadena[i] == 'c')
            c++;

    }
    numCaracteres.push_back(a);
    numCaracteres.push_back(b);
    numCaracteres.push_back(c);

}
void histogram(string cadena  )
{

    int numChunks = 3; //Subdividimos la Cadena Original en numChunks Partes
    #pragma omp parallel for shared(numChunks) reduction(+:a,b,c) num_threads(threads)
    int my_rank = omp_get_num_threads();
    int inicioCadena = my_rank*numChunks;
    int finalCadena  = inicioCadena + numChunks;
    string subCadena;
    for(int i=inicioCadena;i<finalCadena;i++)
    {
        subCadena += cadena[i];
    }

    vector<int> numCaracteres;
    for (int i = 0; i < numChunks; i++)
    {
       numCaracteres = doChunks(subCadena);
        a += numCaracteres[0];
        b += numCaracteres[1];
        c += numCaracteres[2];
    }
}

void print(int a, int b, int c)
{
    for(int i=0;i<a;i++)
        cout<<"X";
    cout<<endl;

    for(int i=0;i<b;i++)
        cout<<"X";
    cout<<endl;

    for(int i=0;i<c;i++)
        cout<<"X";
    cout<<endl;

}


int main() {
    string cadena = "aabbccbaabbccba";
    histogram(cadena);
    print(a,b,c);
    return 0;
}
