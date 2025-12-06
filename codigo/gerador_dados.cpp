#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

struct Tamanho {
    string nome;
    int N;
}; typedef struct Tamanho Tamanho;


void gerarArquivo(const string nomeArquivo, int N, const string cenario){
    int *dados = new int[N];

    for(int i = 0; i < N; i++){
        dados[i] = rand() % 1000000;
    }

    if(cenario == "crescente"){
        sort(dados, dados + N);
    } else if (cenario == "decrescente"){
        sort(dados, dados + N);
        reverse(dados, dados + N);
    }

    string caminho = "../dados/" + nomeArquivo;
    ofstream arq(caminho.c_str(), ios::binary);

    if(!arq){
        cout << "Erro ao tentar criar o arquivo " << caminho << endl;
        return;
    }

    arq.write((char*) dados, sizeof(int) * N);
    arq.close();
    delete[] dados;

    cout << "Arquivo " << caminho << " criado!" << endl;
}



int main(){
    srand(time(0));

    Tamanho tamanhos[]= {
        {"Pequeno", 1000},
        {"Medio", 10000},
        {"Grande", 100000}
    };

    string cenarios[] = {
        "aleatorio",
        "crescente",
        "decrescente"
    };

    int qnt = sizeof(tamanhos) / sizeof(tamanhos[0]);
    for(int i = 0; i < qnt; i++){
        string nomeTamanho = tamanhos[i].nome;
        int N = tamanhos[i].N;

        nomeTamanho[0] = toupper(nomeTamanho[0]);
        for(int j = 1; j < nomeTamanho.size(); j++){
            nomeTamanho[j] = tolower(nomeTamanho[j]);
        }

        int qntCenarios = sizeof(cenarios) / sizeof(cenarios[0]);   
        for(int j = 0; j < qntCenarios; j++){
            string c = cenarios[j];
            string nomeArquivo = nomeTamanho + "_" + c + ".bin";
            gerarArquivo(nomeArquivo, N, c);
        }
    }
}