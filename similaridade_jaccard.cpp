#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <tuple>
#include <fstream> // Biblioteca para manipulação de arquivos
#include "leitura_input.cpp" // Inclui o arquivo leitura_input.cpp

using namespace std;

// Definir uma função de hash personalizada para pair<int, int>
// Isso é necessário para que pares possam ser usados como chave em unordered_map
struct PairIntHash {
    size_t operator()(const pair<int, int>& p) const {
        auto hash1 = hash<int>{}(p.first); // Calcula o hash do primeiro elemento do par
        auto hash2 = hash<int>{}(p.second); // Calcula o hash do segundo elemento do par
        // Combina os dois hashes para gerar um hash único para o par
        return hash1 ^ (hash2 << 1);
    }
};

// Definir uma função de hash personalizada para pair<pair<int, int>, pair<int, int>>
// Necessário para usar pares de pares como chave em unordered_map
struct PairHash {
    size_t operator()(const pair<pair<int, int>, pair<int, int>>& p) const {
        auto hash1 = PairIntHash{}(p.first); // Calcula o hash do primeiro par
        auto hash2 = PairIntHash{}(p.second); // Calcula o hash do segundo par
        // Combina os hashes dos pares internos para gerar um hash único para o par de pares
        return hash1 ^ (hash2 << 1);
    }
};

// Classe para calcular a similaridade de Jaccard
class JaccardSimilarityCalculator {
public:
    // Construtor que recebe o nome do arquivo a ser processado
    JaccardSimilarityCalculator(const string& filename) : filename(filename) {}

    // Função principal que orquestra o cálculo das similaridades
    void process() {
        // Cria uma instância de DataProcessor para processar o arquivo de entrada
        DataProcessor dp(filename);
        dp.processFile(); // Processa o arquivo e popula os mapas de tuplas e classes
        const auto& tupleMap = dp.getTupleMap(); // Obtém o mapa de tuplas processado
        const auto& classMap = dp.getClassMap(); // Obtém o mapa de classes processado

        // Converte unordered_map para map, preservando a ordem dos elementos
        convertMaps(tupleMap, classMap);

        // Calcula parâmetros derivados dos dados de entrada
        calculateParams();

        // Calcula as similaridades de Jaccard entre as tuplas e armazena em um unordered_map
        similarities = calculateSimilarities();

        // Escreve as similaridades calculadas em um arquivo
        writeSimilaritiesToFile(similarities);
    }

    // Função para obter as similaridades calculadas
    const unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash>& getSimilarities() const {
        return similarities;
    }

private:
    string filename; // Nome do arquivo a ser processado
    int k; // Número de tuplas únicas
    int N; // Parâmetro derivado de k, usado no cálculo de b e r
    int b; // Número de bandas (buckets) para o cálculo de similaridade
    int r; // Número de linhas por banda
    double t; // Limite de similaridade para considerar dois conjuntos como similares

    // Mapas para armazenar as linhas em que cada tupla e classe aparece
    map<pair<int, int>, vector<int>> tupleLines;
    map<int, vector<int>> classLines;

    // Mapa para armazenar as similaridades calculadas
    unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash> similarities;

    // Função para converter unordered_map para map
    void convertMaps(const unordered_map<tuple<int, int>, vector<int>, TupleHash>& tupleMap,
                     const unordered_map<int, vector<int>>& classMap) {
        // Converte as tuplas para pair e armazena no map tupleLines
        for (const auto& entry : tupleMap) {
            tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
        }
        // Converte classMap para classLines
        for (const auto& entry : classMap) {
            classLines[entry.first] = entry.second;
        }
    }

    // Função para calcular parâmetros usados no cálculo de similaridade
    void calculateParams() {
        k = tupleLines.size(); // Número de tuplas únicas
        N = 10 * k; // Parâmetro derivado de k
        b = static_cast<int>(sqrt(N)); // Calcula b como a raiz quadrada de N
        r = N / b; // Calcula r como a divisão de N por b
        t = pow((1.0 / b), (1.0 / r)); // Calcula t como (1/b)^(1/r), usado como limite de similaridade

        // Exibe os valores calculados para verificação
        cout << "Valores calculados automaticamente:" << endl;
        cout << "k = " << k << endl;
        cout << "N = " << N << endl;
        cout << "b = " << b << endl;
        cout << "r = " << r << endl;
        cout << "t = " << t << endl;
    }

    // Função para calcular a similaridade de Jaccard entre dois conjuntos
    double jaccardSimilarity(const vector<int>& set1, const vector<int>& set2) {
        set<int> intersection; // Conjunto para armazenar a interseção entre os dois conjuntos
        set<int> unionSet; // Conjunto para armazenar a união dos dois conjuntos

        // Calcula a interseção entre os dois conjuntos e armazena em intersection
        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
        // Calcula a união entre os dois conjuntos e armazena em unionSet
        set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(unionSet, unionSet.begin()));

        // Retorna o coeficiente de Jaccard, que é a razão entre o tamanho da interseção e da união
        return static_cast<double>(intersection.size()) / unionSet.size();
    }

    // Função para calcular e armazenar similaridades em um unordered_map
    unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash> calculateSimilarities() {
        unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash> similarities;

        // Itera sobre todas as combinações de tuplas para calcular a similaridade entre elas
        for (auto it1 = tupleLines.begin(); it1 != tupleLines.end(); ++it1) {
            for (auto it2 = next(it1); it2 != tupleLines.end(); ++it2) {
                double similarity = jaccardSimilarity(it1->second, it2->second); // Calcula a similaridade de Jaccard
                similarities[{{it1->first.first, it1->first.second}, {it2->first.first, it2->first.second}}] = similarity;
            }
        }

        return similarities; // Retorna o mapa de similaridades
    }

    // Função para escrever as similaridades calculadas em um arquivo de saída
    void writeSimilaritiesToFile(const unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash>& similarities) {
        ofstream outFile("similaridade.txt"); // Abre o arquivo de saída

        // Verifica se o arquivo foi aberto com sucesso
        if (!outFile.is_open()) {
            cerr << "Não foi possível abrir o arquivo similaridade.txt para escrita." << endl;
            return;
        }

        // Itera sobre o mapa de similaridades e escreve cada entrada no arquivo
        for (const auto& entry : similarities) {
            outFile << "Similaridade((" << entry.first.first.first << "," << entry.first.first.second << "), "
                    << "(" << entry.first.second.first << "," << entry.first.second.second << ")) = " << entry.second << endl;
        }

        outFile.close(); // Fecha o arquivo de saída
    }
};

// Função principal que inicia o processo de cálculo de similaridade
// int main() {
//     JaccardSimilarityCalculator calculator("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-testing.data");
//     calculator.process(); // Inicia o cálculo das similaridades

// //     // Obtém e exibe as similaridades calculadas
//     const auto& similarities = calculator.getSimilarities();
// //     // for (const auto& entry : similarities) {
// //     //     cout << "Similaridade((" << entry.first.first.first << "," << entry.first.first.second << "), "
// //     //          << "(" << entry.first.second.first << "," << entry.first.second.second << ")) = " << entry.second << endl;
// //     // }

//     return 0;
// }