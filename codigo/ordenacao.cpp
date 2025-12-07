#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;

struct Metricas{
    long long comparacoes = 0;
    long long trocas = 0;
    double tempo = 0.0;
}; typedef struct Metricas metricas;

struct Algoritmos {
    string nome;
    void (*func)(vector<int>&, Metricas&);
}; typedef struct Algoritmos algoritmos;


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


void selectionSort(vector<int>& v, Metricas& m){
    int n = v.size();

    for(int i = 0; i < n; i++){
        int indiceMin = i;
        for(int j = i + 1; j < n; j++){
            m.comparacoes++;
            if(v[j] < v[indiceMin]){
                indiceMin = j;
            }
        }

        if(indiceMin != i){
            swap(v[i], v[indiceMin]);
            m.trocas++;
        }
    }
}

void insertionSort(vector<int>& v, Metricas& m){
    int n = v.size();

    for(int i = 1; i < n; i++){
        int aux = v[i];
        int j = i - 1;

        while(j >= 0){
            m.comparacoes++;
            if(v[j] > aux){
                v[j+1] = v[j];
                j--;
                m.trocas++;
            } else{
                break;
            }
        }

        v[j+1] = aux;
    }
}

void bubbleSortPadrao(vector<int>& v, Metricas& m){
    int tamAux = v.size();

    while(tamAux > 0){
        for(int j = 1; j < tamAux; j++){
            m.comparacoes++;
            if(v[j] < v[j-1]){
                swap(v[j], v[j-1]);
                m.trocas++;
            }
        }
        tamAux--;
    }
}

void bubbleSortOtimizado(vector<int>& v, Metricas& m){
    int tamAux = v.size();
    int flag = 1;

    while(flag){
        flag = 0;
        for(int j = 1; j < tamAux; j++){
            m.comparacoes++;
            if(v[j] < v[j-1]){
                swap(v[j], v[j-1]);
                m.trocas++;
                flag = 1;
            }
        } tamAux--;
    }
}

void executarTeste(const string nomeArquivo, void (*algoritmo)(vector<int>&, Metricas&), const string nomeAlgoritmo){
    vector<int> vetor = lerBinario(nomeArquivo);
    if(vetor.empty()) return;

    Metricas metricas;

    auto start = chrono::high_resolution_clock::now();
    algoritmo(vetor, metricas);
    auto end = chrono::high_resolution_clock::now();

    metricas.tempo = chrono::duration_cast<chrono::milliseconds>(end-start).count();

    cout << "Apresentando os resultados obtidos para a ordenacao " << nomeAlgoritmo << " no arquivo " << nomeArquivo << endl;
    cout << "Tamanho: " << vetor.size() << endl;
    cout << "Tempo de execucao: " << metricas.tempo << endl;
    cout << "Comparacoes: " << metricas.comparacoes << endl;
    cout << "Trocas: " << metricas.trocas << endl;
    cout << endl;

}

int main(){
    string arquivos[] = {
        "Pequeno_aleatorio.bin", "Pequeno_crescente.bin", "Pequeno_decrescente.bin",
        "Medio_aleatorio.bin", "Medio_crescente.bin", "Medio_decrescente.bin",
        "Grande_aleatorio.bin", "Grande_crescente.bin", "Grande_decrescente.bin"
    };

    vector<Algoritmos> algoritmos = {
        {"Selection Sort", selectionSort},
        {"Insertion Sort", insertionSort},
        {"Bubble Sort Padrao", bubbleSortPadrao},
        {"Bubble Sort Otimizado", bubbleSortOtimizado},
    };

    int qntArquivo = sizeof(arquivos) / sizeof(arquivos[0]);
    int qntAlgoritmos = algoritmos.size();

    for(int i = 0; i < qntArquivo; i++){
        string arquivo = arquivos[i];

        for(int j = 0; j < qntAlgoritmos; j++){
            string nome = algoritmos[j].nome;
            auto func = algoritmos[j].func;

            executarTeste(arquivo, func, nome);
        }
    }
    return 0;
}