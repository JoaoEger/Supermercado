#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <limits>
#include <algorithm>
#include <conio.h>

#define MAX 1000
using namespace std; 

struct produtos
{
    string nome; 
    float quanti; 
    double valorV; 
};

int lerInt(string msg = "Digite um valor: ") {
    string entrada;
    int valor;

    while(true) {
        cout << msg;
        getline(cin, entrada);

        bool valido = true;

        for(int i = 0; i < entrada.size(); i++) {
            char c = entrada[i];
            if (c < '0' || c > '9') {
                valido = false;
                break;
            }
        }

        if (valido && !entrada.empty()) {
            valor = stoi(entrada);
            return valor;
        } else {
            cout << "Entrada invalida! Digite apenas numeros inteiros.\n";
        }
    }
}


double lerDouble(string msg = "Digite um valor: "){
    double valor;
    string entrada;

    while(true){
        cout << msg;
        getline(cin, entrada);

        bool valido = true;
        int pontos = 0;

        for (int i = 0; i < entrada.size(); i++) {
            char c = entrada[i];
            if ((c < '0' || c > '9') && c != '.') {
                valido = false;
                break;
            }
            if (c == '.') {
                pontos++;
                if (pontos > 1) {
                    valido = false;
                    break;
                }
            }
        }

        if (valido && !entrada.empty()) {
            valor = stod(entrada);
            return valor;
        } else {
            cout << "Entrada invalida! Digite apenas numeros.\n";
        }

    };

}

void salvarProduto(produtos &p){

    ofstream arquivo("produtos.txt", ios::app); 
        if (!arquivo.is_open()){
            cout << "Erro ao abrir o arquivo para salvar" << endl;
            return;
        }
    arquivo << p.nome << " " << p.valorV << " " << p.quanti << endl;
    arquivo.close();

}

void carregarProdutos(produtos p[], int &qnt) {
    ifstream arquivo("produtos.txt");
    if (!arquivo.is_open()) {
        cout << "Arquivo nao encontrado. Comecando com estoque vazio." << endl;
        qnt = 0;
        return;
    }

    string linha;
    qnt = 0;
    while (getline(arquivo, linha)) {
        size_t pos1 = linha.find_last_of(' '); //Procura a posição do último espaço na linha
        size_t pos2 = linha.find_last_of(' ', pos1 - 1); //Procura o penúltimo espaço, ou seja, o espaço antes do preço

        p[qnt].nome = linha.substr(0, pos2); //Pega os caracteres do início da linha até o penúltimo espaço pos2
        p[qnt].valorV = atof(linha.substr(pos2 + 1, pos1 - pos2 - 1).c_str()); //pega os caracteres entre o penúltimo e o último espaço, ou seja, o preço do produto
        p[qnt].quanti = atof(linha.substr(pos1 + 1).c_str()); // pega todos os caracteres após o último espaço, que é a quantidade em estoque.
        qnt++;
    }

    arquivo.close();
}

bool nomesIguais(string a, string b) {
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a == b;
}

void cadastro(produtos p[], int &qnt){
    string nomeTempor;
    cout << "---CADASTRO PRODUTOS---" << endl;
    cout << "nome do produto: " << endl; 
    //para limpar o buffer
    getline(cin, nomeTempor); //salvar nome dos produtos com espaço 
    
        //verifica se o produto ja foi cadastrado
        for(int i=0; i<qnt; i++){
           if(nomesIguais(p[i].nome, nomeTempor)){
            cout << "produto ja cadastrado."<<endl;
            return;
           }
        }
    
    p[qnt].nome = nomeTempor;

    p[qnt].valorV = lerDouble("Digite o preco do produto: ");
    p[qnt].quanti = lerDouble("Digite a quantidade do produto: ");
    
    salvarProduto(p[qnt]);

qnt++;

}

void ListarProdutos(produtos p[], int &qnt){
    cout << "--LISTA DE PRODUTOS--\n";
    cout << "cod // nome // preco //     quantidade\n";
    for(int i=0; i<qnt; i++){
        cout << "(" << i+1<<") - " << p[i].nome << " -  R$:" << p[i].valorV << " - " << p[i].quanti << endl;  
    }
}

void Vendas(produtos p[], int &qnt) {
    if (qnt == 0) {
        cout << "Nenhum produto cadastrado!" << endl;
        system("pause");
        return;
    }

    int opc = 0;
    char tecla;
    int quantidade;
    double total = 0.0;
    while (true) {
        system("cls");
        cout << "Use as setas e ENTER para confirmar\n\n";

        for (int i = 0; i < qnt; i++) {
            if (opc == i)
                cout << "> " << p[i].nome << " - R$:" << p[i].valorV << endl;
            else
                cout << "  " << p[i].nome << " - R$:" << p[i].valorV << endl;
        }

        tecla = getch();

        if (tecla == 72) {              
            opc = (opc - 1 + qnt) % qnt;
        } else if (tecla == 80) {
            opc = (opc + 1) % qnt;
        } else if (tecla == 13) {
            system("cls");
            cout << "Você selecionou: " << p[opc].nome << endl;

            do{
                quantidade = lerDouble("Informe a quantidade de produtos: ");
                if(quantidade > p[opc].quanti){
                    cout << "Desculpe, não temos essa quantidade em estoque, temos apenas " << p[opc].quanti << endl;
                    cout << "Por favor! ";
                }
            }while(quantidade > p[opc].quanti);

            p[opc].quanti -= quantidade;
            double subtotal = p[opc].valorV * quantidade;
            total += subtotal;

            cout << "\nSubtotal: " << subtotal << endl;
            cout << "\nTotal: " << total << endl;

            int opc2 = 0;
            cout << "Deeja continuar comprando?" << endl;

        }    
    }
}


void apagarProd(produtos p[], int &qnt) {
    if (qnt == 0) {
        cout << "Nenhum produto cadastrado." << endl;
        return;
    }
    ListarProdutos(p, qnt);
    cout << "(0) - NÃO QUERO REMOVER NENHUM ITEM\n";

    int indice;
    do{
        indice = lerInt("Digite o numero do produto que deseja remover: ");

        if(indice < 0 || indice > qnt){
            cout << "Indice invalido!" << endl;
        }else if(indice == 0){
            cout << "NÃO REMOVEU NENHUM ITEM" << endl;
            return;
        }
    }while(indice < 0 || indice > qnt);

    string nomeRemover = p[indice-1].nome;

    ifstream arquivo("produtos.txt");
    ofstream temporario("produtos_temp.txt");

    if (!arquivo.is_open() || !temporario.is_open()) {
        cout << "Erro ao abrir arquivos." << endl;
        return;
    }

    string linha;
    bool removido = false;

    while (getline(arquivo, linha)) {
        size_t pos1 = linha.find_last_of(' ');
        size_t pos2 = linha.find_last_of(' ', pos1 - 1);
        string nomeLinha = linha.substr(0, pos2);

        if (nomesIguais(nomeLinha, nomeRemover)) {
            removido = true;
            continue; // não grava
        }
        temporario << linha << endl;
    }

    arquivo.close();
    temporario.close();

    remove("produtos.txt");
    rename("produtos_temp.txt", "produtos.txt");

    if (removido) {
        cout << "Produto removido com sucesso!" << endl;
        carregarProdutos(p, qnt); // atualiza vetor
    } else {
        cout << "Erro: produto nao encontrado no arquivo!" << endl;
    }
}

void MENU(int &opc){
    char tecla;
    do{
        system("cls");
        cout << "                                MNSP-01\n";
        cout << "---MENU SUPERMERCADO---\n";
        cout << (opc == 1 ? "> " : "  ") << "Produtos      \n";
        cout << (opc == 2 ? "> " : "  ") << "Vendas         \n";
        cout << (opc == 3 ? "> " : "  ") << "Relatorios     \n";
        cout << (opc == 0 ? "> " : "  ") << "Sair            \n";
        cout << " ESCOLHA UMA OPCAO \n"; 

        tecla = getch();

        if(tecla == 72){
            opc = (opc - 1 + 4) % 4;
        }else if(tecla == 80){
            opc = (opc + 1) % 4;
        }else if(tecla == 13){
            break;
        }

    }while(true);

}

void MENUProdutos(produtos p[], int &qnt){
    int opc = 1;
    char tecla;
    do{
        while(true){
            system("cls");
            cout << "                                  MNSPP-02\n";
            cout << "---MENU PRODUTOS---\n";
            cout << (opc == 1 ? "> " : "  ") << "Cadastrar produtos\n";
            cout << (opc == 2 ? "> " : "  ") << "Listar produtos \n";
            cout << (opc == 3 ? "> " : "  ") << "Remover item \n";
            cout << (opc == 0 ? "> " : "  ") << "Voltar\n";
            cout << " ESCOLHA UMA OPCAO \n";

            tecla = getch();

            if(tecla == 72){
                opc = (opc - 1 + 4) % 4;
            }else if(tecla == 80){
                opc = (opc + 1) % 4;
            }else if(tecla == 13){
                break;
            }
        }
        switch(opc){

            case 1: cadastro(p, qnt); system("pause"); break;
            case 2: ListarProdutos(p, qnt); system("pause"); break;
            case 3: apagarProd(p, qnt); system("pause"); break;
            case 0: break;
            default: cout << "Opcao invalida\n"; system("pause"); break;
    
        }
    }while(opc != 0); 
}

int main(){
    produtos v[MAX];
    int qnt = 0;
    int opc = 1; 
    
    carregarProdutos(v, qnt);

    do{
        MENU(opc); 

    switch (opc){
        case 1: MENUProdutos(v, qnt); break;
        case 2: Vendas(v, qnt); break;
        case 0:
            cout << "Obrigado por acessar!" <<endl; 
            break;
        default: 
            cout << "Opcao invalida."<<endl;
        }
    }while(opc !=0);

    return 0;
}