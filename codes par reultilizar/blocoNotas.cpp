#include <iostream>
#include <fstream>
using namespace std;

int main(){

    string texto, linha; 
    int opc; 
do{
    cout << "---BLOCO DE NOTAS---" <<endl;
    cout << "1 - escrever no arquivo" <<endl;
    cout << "2 - ler o arquivo      " <<endl;
    cout << "3 - apagar o conteudo do arquivo" <<endl;
    cout << "4 - sair" <<endl;
    cout << "escolha uma opcao: " <<endl;
    cin >> opc; 
    cin.ignore();

    switch (opc){

        case 1:{
        ofstream arquivo("blocoDeNotas.txt", ios::app);
        if(!arquivo){
            cout << "erro ao abrir o arquivo" << endl;
            break;
        }

        cout <<  "digite o texto(uma linha): ";
        getline(cin, texto);
        arquivo << texto << endl;
        arquivo.close();
        cout << "texto salvo com sucesso: "<<endl;
        break;
    }

    case 2: {
        ifstream arquivo("blocoDeNotas.txt");
        if(!arquivo){
            cout << "nao foi encontrado anotacao" <<endl; 
            break;
        }
        cout << "\n===CONTEUDO DO ARQUIVO==="<< endl;
            while(getline(arquivo, linha)){
                cout << linha << endl;
            }
            arquivo.close();
            break;
    }
    case 3: {
        ofstream arquivo("blocoDeNotas.txt", ios::trunc);
            if(!arquivo){
                cout << "erro ao abrir o arquivo"<<endl; 
                break;
            }
            arquivo.close();
            cout << "conteudo apagado com sucesso" << endl;
            break;
    }
        case 4: 
        cout << "saindo..." << endl;
        break;

        default: 
        cout << "opcao invalida " << endl;
}} while (opc != 4);

return 0;
}