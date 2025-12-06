#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>


using namespace std;

vector<int> lerBinario(const string nomeArquivo){
    string caminho = "../dados/" + nomeArquivo;
    ifstream arquivo(caminho, ios::binary);
    
    if(!arquivo){
        cout << "Não foi possível abrir o arquivo presente no caminho: " << caminho << endl;
        return {};
    }

    arquivo.seekg(0, ios::end);
    long tam = arquivo.tellg();
    arquivo.seekg(0, ios::beg);

    int quantidade = tam / sizeof(int);
    vector<int> vec(quantidade);

    arquivo.read((char*)vec.data(), tam);

    return vec;
}

bool buscaSequencial(const vector<int>& v, int chave, long& comp){
    int n = v.size();
    for(int i = 0; i < n; i++){
        comp++;
        if(v[i] == chave){
            return true;
        }
    }
    return false;
}

bool buscaBinaria(const vector<int>& v, int chave, long& comp){
    int n = v.size();
    int inicio = 0;
    int fim = n - 1;

    while(inicio <= fim){
        int meio = inicio + (fim - inicio) / 2;
        comp++;

        if(v[meio] == chave){
            return true;
        } else if(v[meio] < chave){
            inicio = meio + 1;
        } else{
            fim = meio - 1;
        }
    }
    return false;
}

struct Teste {
    string nome;
    int valor;
}; typedef struct Teste teste;

int main(){
    const string nomeArquivo = "Grande_aleatorio.bin";

    vector<int> vetor = lerBinario(nomeArquivo);
    if(vetor.empty()) return 1;
    int n = vetor.size();

    vector<int> vecOrdenado = vetor;
    sort(vecOrdenado.begin(), vecOrdenado.end());

    int valExistente = vecOrdenado.back();
    int valInexistente = vecOrdenado.back() + 1;

    Teste teste[] = {
        {"Valor Existente", valExistente},
        {"Valor Inexistente", valInexistente},
    };

    for(int i = 0; i < 2; i++){
        cout << "Realizacao do teste com um " << teste[i].nome << ": " << teste[i].valor << endl;

        long comparacoesSeq = 0;
        auto inicioSeq = chrono::high_resolution_clock::now();
        buscaSequencial(vetor, teste[i].valor, comparacoesSeq);
        auto fimSeq = chrono::high_resolution_clock::now();;
        double tempoSeq = chrono::duration_cast<chrono::microseconds>(fimSeq - inicioSeq).count() / 1000.0;

        cout << "Busca sequencial:" << endl;
        cout << "Tempo -> " << tempoSeq << "ms" << endl;
        cout << "Comparacoes -> " <<comparacoesSeq << endl;
        cout << endl;


        long comparacoesBin = 0;
        auto inicioBin = chrono::high_resolution_clock::now();
        buscaBinaria(vecOrdenado, teste[i].valor, comparacoesBin);
        auto fimBin = chrono::high_resolution_clock::now();;
        double tempoBin = chrono::duration_cast<chrono::microseconds>(fimBin - inicioBin).count() / 1000.0;

        cout << "Busca binaria:" << endl;
        cout << "Tempo -> " << tempoBin << "ms" << endl;
        cout << "Comparacoes -> " <<comparacoesBin << endl;
        cout << endl;

    }

    return 0;
}