#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <unordered_map>
#include <tuple>
#include <fstream>
#include <sstream>
#include "similaridade_jaccard.cpp" // Inclui o arquivo similaridade_jaccard.cpp

using namespace std;

// Função para calcular o suporte
// O suporte é a proporção de linhas da classe que contêm a tupla
double calculateSupport(const vector<int>& tupleLines, const vector<int>& classLines) {
    set<int> intersection;
    // Calcula a interseção entre as linhas da tupla e as linhas da classe
    set_intersection(tupleLines.begin(), tupleLines.end(), classLines.begin(), classLines.end(),
                     inserter(intersection, intersection.begin()));
    // Retorna o suporte como a razão entre o tamanho da interseção e o tamanho das linhas da classe
    return static_cast<double>(intersection.size()) / classLines.size();
}

// Função para calcular a confiança
// A confiança é a proporção de linhas da tupla que pertencem à classe
double calculateConfidence(const vector<int>& tupleLines, const vector<int>& classLines) {
    set<int> intersection;
    // Calcula a interseção entre as linhas da tupla e as linhas da classe
    set_intersection(tupleLines.begin(), tupleLines.end(), classLines.begin(), classLines.end(),
                     inserter(intersection, intersection.begin()));
    // Retorna a confiança como a razão entre o tamanho da interseção e o tamanho das linhas da tupla
    return static_cast<double>(intersection.size()) / tupleLines.size();
}

template <typename T>
vector<vector<T>> generateCombinations(const vector<T>& elements, int combinationSize) {
    vector<vector<T>> combinations; // Vetor para armazenar as combinações geradas.
    vector<bool> selector(elements.size()); // Vetor de seleção para gerar combinações.
    fill(selector.end() - combinationSize, selector.end(), true); // Marca os últimos 'combinationSize' elementos como verdadeiros.

    do {
        vector<T> combination; // Vetor para armazenar a combinação atual.
        for (size_t i = 0; i < elements.size(); ++i) {
            if (selector[i]) {
                combination.push_back(elements[i]); // Adiciona o elemento à combinação se o seletor correspondente for verdadeiro.
            }
        }
        combinations.push_back(combination); // Adiciona a combinação gerada ao vetor de combinações.
    } while (next_permutation(selector.begin(), selector.end())); // Gera a próxima permutação do seletor.

    return combinations; // Retorna o vetor contendo todas as combinações geradas.
}

// Função para calcular suporte e confiança para uma nova entrada
void calculateSupportAndConfidence(const vector<pair<int, int>>& instance, 
                                   const map<pair<int, int>, vector<int>>& tupleLines, 
                                   const map<int, vector<int>>& classLines) {
    map<int, double> classSupport; // Mapa para armazenar o suporte de cada classe
    map<int, double> classConfidence; // Mapa para armazenar a confiança de cada classe

    // Itera sobre todas as classes
    for (const auto& classEntry : classLines) {
        int classLabel = classEntry.first; // Rótulo da classe
        const auto& classLineNumbers = classEntry.second; // Linhas da classe

        double totalSupport = 0.0; // Suporte total para a classe atual
        double totalConfidence = 0.0; // Confiança total para a classe atual
        int count = 0; // Contador de características encontradas na nova entrada

        // Itera sobre todos os tamanhos de combinação possíveis (de 1 até o tamanho da nova entrada)
        for (int size = 1; size <= instance.size(); ++size) {
            auto combinations = generateCombinations(instance, size);
            for (const auto& combination : combinations) {
                // Converte a combinação para um formato que pode ser procurado no mapa de tuplas
                vector<int> combinedLines;
                bool found = true;
                for (const auto& feature : combination) {
                    auto it = tupleLines.find(feature);
                    if (it != tupleLines.end()) {
                        if (combinedLines.empty()) {
                            combinedLines = it->second;
                        } else {
                            vector<int> temp;
                            set_intersection(combinedLines.begin(), combinedLines.end(),
                                             it->second.begin(), it->second.end(),
                                             back_inserter(temp));
                            combinedLines = temp;
                        }
                    } else {
                        found = false;
                        break;
                    }
                }
                if (found) {
                    // Calcula e acumula o suporte e a confiança para a combinação
                    totalSupport += calculateSupport(combinedLines, classLineNumbers);
                    totalConfidence += calculateConfidence(combinedLines, classLineNumbers);
                    count++;
                }
            }
        }

        // Calcula a média do suporte e da confiança para a classe atual, se houver características encontradas
        if (count > 0) {
            classSupport[classLabel] = totalSupport / count;
            classConfidence[classLabel] = totalConfidence / count;
        }
    }

    // Exibe os resultados de suporte e confiança para a nova entrada
    cout << "Suporte e Confianca para a nova entrada:" << endl;
    for (const auto& entry : classSupport) {
        cout << "Classe: " << entry.first << ", Suporte: " << entry.second 
             << ", Confianca: " << classConfidence[entry.first] << endl;
    }
}

// Função principal
int main() {
    // Processa o arquivo de entrada
    DataProcessor dp("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-testing.data");
    dp.processFile(); // Processa o arquivo e preenche os mapas de tuplas e classes
    const auto& tupleMap = dp.getTupleMap(); // Obtém o mapa de tuplas
    const auto& classMap = dp.getClassMap(); // Obtém o mapa de classes

    // Converte unordered_map para map, preservando a ordem dos elementos
    map<pair<int, int>, vector<int>> tupleLines;
    map<int, vector<int>> classLines;

    // Converte o mapa de tuplas para um mapa ordenado
    for (const auto& entry : tupleMap) {
        tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
    }

    // Converte o mapa de classes para um mapa ordenado
    for (const auto& entry : classMap) {
        classLines[entry.first] = entry.second;
    }

    // Nova entrada para calcular suporte e confiança
    vector<pair<int, int>> newInstance = {{1, 10}, {1, 11}, {1, 13}, {1, 12}, {1, 1}};

    // Calcula suporte e confiança para a nova entrada
    calculateSupportAndConfidence(newInstance, tupleLines, classLines);

    return 0;
}