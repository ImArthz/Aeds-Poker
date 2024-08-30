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
#include "characteristic_matrix.h"
#include "minhash_signature.h"
#include "leitura_input.cpp" // Inclua o arquivo leitura_input.cpp

using namespace std;

// Definir uma função de hash personalizada para std::pair<int, int>
struct PairIntHash {
    std::size_t operator()(const std::pair<int, int>& p) const {
        auto hash1 = std::hash<int>{}(p.first);
        auto hash2 = std::hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

// Definir uma função de hash personalizada para std::pair<std::pair<int, int>, std::pair<int, int>>
struct PairHash {
    std::size_t operator()(const std::pair<std::pair<int, int>, std::pair<int, int>>& p) const {
        auto hash1 = PairIntHash{}(p.first);
        auto hash2 = PairIntHash{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

class JaccardSimilarityCalculator {
public:
    JaccardSimilarityCalculator(const string& filename) : filename(filename) {}

    void process() {
        // Processar o arquivo de entrada e obter os mapas
        DataProcessor dp(filename);
        dp.processFile();
        const auto& tupleMap = dp.getTupleMap();
        const auto& classMap = dp.getClassMap();

        // Converter unordered_map para map
        convertMaps(tupleMap, classMap);

        // Calcular parâmetros
        calculateParams();

        // Calcular similaridades e armazenar em um unordered_map
        auto similarities = calculateSimilarities();

        // Escrever similaridades em um arquivo
        writeSimilaritiesToFile(similarities);
    }

private:
    string filename;
    int k;
    int N;
    int b;
    int r;
    double t;
    int ndocs;

    // Mapas para armazenar linhas de tuplas e classes
    map<pair<int, int>, vector<int>> tupleLines;
    map<int, vector<int>> classLines;

    // Função para converter unordered_map para map
    void convertMaps(const unordered_map<tuple<int, int>, vector<int>, TupleHash>& tupleMap,
                     const unordered_map<int, vector<int>>& classMap) {
        for (const auto& entry : tupleMap) {
            tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
        }
        for (const auto& entry : classMap) {
            classLines[entry.first] = entry.second;
        }
    }

    // Função para calcular parâmetros
    void calculateParams() {
        k = tupleLines.size();
        N = 10 * k;
        b = static_cast<int>(sqrt(N));
        r = N / b;
        t = pow((1.0 / b), (1.0 / r));

        cout << "Valores calculados automaticamente:" << endl;
        cout << "k = " << k << endl;
        cout << "N = " << N << endl;
        cout << "b = " << b << endl;
        cout << "r = " << r << endl;
        cout << "t = " << t << endl;
    }

    // Função para calcular a similaridade de Jaccard
    double jaccardSimilarity(const vector<int>& set1, const vector<int>& set2) {
        set<int> intersection;
        set<int> unionSet;

        set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(intersection, intersection.begin()));
        set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), inserter(unionSet, unionSet.begin()));

        return static_cast<double>(intersection.size()) / unionSet.size();
    }

    // Função para calcular e armazenar similaridades em um unordered_map
    unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash> calculateSimilarities() {
        unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash> similarities;

        for (auto it1 = tupleLines.begin(); it1 != tupleLines.end(); ++it1) {
            for (auto it2 = next(it1); it2 != tupleLines.end(); ++it2) {
                double similarity = jaccardSimilarity(it1->second, it2->second);
                similarities[{{it1->first.first, it1->first.second}, {it2->first.first, it2->first.second}}] = similarity;
            }
        }

        return similarities;
    }

    // Função para escrever similaridades em um arquivo
    void writeSimilaritiesToFile(const unordered_map<pair<pair<int, int>, pair<int, int>>, double, PairHash>& similarities) {
        ofstream outFile("similaridade.txt");

        if (!outFile.is_open()) {
            cerr << "Não foi possível abrir o arquivo similaridade.txt para escrita." << endl;
            return;
        }

        for (const auto& entry : similarities) {
            outFile << "Similaridade((" << entry.first.first.first << "," << entry.first.first.second << "), "
                    << "(" << entry.first.second.first << "," << entry.first.second.second << ")) = " << entry.second << endl;
        }

        outFile.close();
    }
};

int main() {
    JaccardSimilarityCalculator calculator("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data");
    calculator.process();
    return 0;
}