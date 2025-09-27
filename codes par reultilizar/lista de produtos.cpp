#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <limits>

using namespace std; 

struct produtos 
{
    string nome; 
    double preco;
    int quantidade; 
};

void carregarProdutos( produtos p[], int &qnt){
    ifstream arquivo("produtos.txt");
    if (!arquivo.is_open()){
        cout << "arquivo nao encontrado. Comecando com estoque vazio." << endl;
        qnt=0; 
        return; 
    } 
    while(arquivo >> p[qnt].nome >> p[qnt].preco >> p[qnt].quantidade){
        qnt++;
    }
    arquivo.close(); 

}

void salvarProduto(produtos &p){

    ofstream arquivo("produtos.txt", ios::app); 
        if (!arquivo.is_open()){
            cout << "Erro ao abrir o arquivo para salvar" << endl;
            return;
        }
    arquivo << p.nome << " " << p.preco << " " << p.quantidade << endl;
    arquivo.close();

}


void cadastroProduto(produtos p[], int &qnt){

    cout << "---CADASTRO PRODUTOS---" << endl;
    cout << "nome do produto: " << endl; cin >> p[qnt].nome;
    cout << "digite o preco do produto: " << endl; cin  >> p[qnt].preco; 
    cout << "digite a quantidade em estoque: " << endl; cin >> p[qnt].quantidade; 
    salvarProduto(p[qnt]);
    qnt++; 
    cout << "produto cadastrado com sucesso" << endl;
    cout << "precione ENTER para voltar ao menu...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get(); 
    system("cls"); 
}

void listarProdutos(produtos p[], int &qnt){
    cout << "---LISTA DE PRODUTOS---" << endl; 
    for (int i = 0; i < qnt; i++)
    {
        cout << i+1 << " produto: " << p[i].nome << " |  preco: " << p[i].preco << " |  quantidade em estoque: " << p[i].quantidade << endl;
    }
    cout << "precione ENTER para voltar ao menu...";
    string lixo;
    getline(cin, lixo); 
    system("cls"); 
    
}

double valorTotal(produtos p[], int &qnt){

    double soma=0; 

    for (int i = 0; i < qnt; i++)
    {
        soma+= p[i].preco * p[i].quantidade; 

    }
    return soma; 
}

int main(){

    produtos v[100];
    int qnt=0; 
    int opc; 

    carregarProdutos(v, qnt);

    do{
    
        cout << "---MENU DE PRODUTOS---" << endl;
        cout << "1 - Cadastrar produto" << endl;
        cout << "2 - Listar produtos" << endl;
        cout << "3 - Valor total do estoque" << endl;
        cout << "0 - Sair" << endl;
        cout << "Digite a opcao: ";
        cin >> opc;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
        switch(opc)
        {
        
        case 1: 
            cadastroProduto(v, qnt);
             system("cls");
             break;
        case 2:
            listarProdutos(v, qnt);
            system("cls");
            break;
        case 3: {
            double total = valorTotal(v, qnt);
        cout << "o valor em nosso estoque eh de: " << total << endl; 
        cout << "precione ENTER para voltar ao menu...";
        string lixo; 
        
        }
        case 0: 
            cout << "saindo do sistema..." << endl; 
            break;
        default:
            cout << "opcao invalida, tente novamente" << endl; 
    }
    }while(opc != 0);
}
