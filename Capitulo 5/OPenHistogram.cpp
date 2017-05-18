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
#pragma omp parallel for shared(numChunks, chunk) reduction(+:counter)

    int a,b,c = 0;
    string subCadena;
    int numChunks = 3;
    vector<int> numCaracteres;
    for (int i = 0; i < numChunks; i++)
    {
       numCaracteres = doChunks(subCadena);
        a += numCaracteres[0];
        b += numCaracteres[1];
        c += numCaracteres[2];
    }
}

}



int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}