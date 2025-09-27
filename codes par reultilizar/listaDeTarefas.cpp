#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void adicionarTarefa();
void listarTarefas();
void removerTarefa();

int main() {
    int opc;

    do {
        cout << "\n=== LISTA DE TAREFAS ===" << endl;
        cout << "1 - Adicionar tarefa" << endl;
        cout << "2 - Listar tarefas" << endl;
        cout << "3 - Remover tarefa" << endl;
        cout << "4 - Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> opc;
        cin.ignore();

        switch (opc) {
            case 1:
                adicionarTarefa();
                break;
            case 2:
                listarTarefas();
                break;
            case 3:
                removerTarefa();
                break;
            case 4:
                cout << "Saindo..." << endl;
                break;
            default:
                cout << "Opcao invalida!" << endl;
        }
    } while (opc != 4);

    return 0;
}


void adicionarTarefa() {
    ifstream leitura("tarefas.txt");
    int id=1; 
    string linha;
    
    while(getline(leitura, linha)){
        id++;
    }
    leitura.close();

    ofstream arquivo("tarefas.txt",ios::app);
        if(!arquivo){
            cout <<" erro ao abrir o arquivo" << endl; 
        return;
        }
        
        string tarefas;
        cout << "digite a descricao da tarefa: ";
        getline(cin, tarefas);
        arquivo << "[" << id << "]" << tarefas << endl;
        arquivo.close();

        cout << "tarefa registrada com sucesso";
    
}

void listarTarefas() {
    ifstream arquivo("tarefas.txt");
        if(!arquivo){
            cout << "nenhuma anotacao encontrada" << endl;
        return;
        }

        string linha; 
    cout << "\n---LISTA DE TAREFAS---" <<endl;
    while(getline(arquivo, linha)){
        cout << linha << endl;
    }
    arquivo.close();
}


void removerTarefa() {
    ifstream arquivo("tarefas.txt");
    if(!arquivo){
        cout << "nenhum arquivo encontrado";
        return;
    }

    int idRemover; 
    cout << "qual id deseja remover: "; cin >> idRemover; cin.ignore();
    
    ofstream temp("tarefas_temp.txt"); 
    string linha;
    bool removida = false;

        while(getline(arquivo, linha)){
            if(linha.rfind("[" + to_string(idRemover) + "]", 0) == 0){
                removida=true; 
                continue;
            }
            temp << linha << endl;
        }

        arquivo.close();
        temp.close();

        remove("tarefas.txt");
        rename("tarefas_temp.txt", "tarefas.txt");

            if(removida){
                cout << "removida com sucesso" << endl;

            } else{
                cout << "tarefa nao encontrada" << endl;
            }
}
