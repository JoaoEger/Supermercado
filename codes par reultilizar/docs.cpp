#include <iostream>
#include <fstream>
using namespace std; 

int main(){

    ofstream arquivo("teste2.txt");

        if(!arquivo){
            cout << "erro ao abrir o arquivo" << endl;
        return 1; 
        }
        arquivo << "ola, mundo" << endl;
        arquivo << "aprendendo o fstream " << endl;

        arquivo.close();
        return 0; 
}