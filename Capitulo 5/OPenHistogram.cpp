#include <iostream>
#include <vector>
using namespace std;

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


void histogram(string cadena)
{
    #pragma omp parallel for shared(numChunks) reduction(+:a,b,c)

    int a,b,c = 0;
    int numChunks = 3; //Subdividimos la Cadena Original en numChunks Partes
    int my_rank = omp_get_thread_num();
    int inicioCadena = initCadena + my_rank*numChunks;
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
    return 0;
}
