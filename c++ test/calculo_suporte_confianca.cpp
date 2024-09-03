#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <tuple>
#include <fstream>
#include <stdexcept>
#include <sys/stat.h>
#include <direct.h> // Inclua para _mkdir
#include "DataProcessor.h"

using namespace std;

// Função para calcular o suporte
double calculateSupport(const vector<int>& tupleLines, const vector<int>& classLines) {
    set<int> intersection;
    set_intersection(tupleLines.begin(), tupleLines.end(), classLines.begin(), classLines.end(),
                     inserter(intersection, intersection.begin()));
    return static_cast<double>(intersection.size()) / classLines.size();
}

// Função para calcular a confiança
double calculateConfidence(const vector<int>& tupleLines, const vector<int>& classLines) {
    set<int> intersection;
    set_intersection(tupleLines.begin(), tupleLines.end(), classLines.begin(), classLines.end(),
                     inserter(intersection, intersection.begin()));
    return static_cast<double>(intersection.size()) / tupleLines.size();
}

// Função para gerar combinações de tamanho específico a partir de um vetor de elementos
template <typename T>
vector<vector<T>> generateCombinations(const vector<T>& elements, int combinationSize) {
    vector<vector<T>> combinations;
    vector<bool> selector(elements.size(), false);
    fill(selector.end() - combinationSize, selector.end(), true);

    do {
        vector<T> combination;
        for (size_t i = 0; i < selector.size(); ++i) {
            if (selector[i]) {
                combination.push_back(elements[i]);
            }
        }
        combinations.push_back(combination);
    } while (next_permutation(selector.begin(), selector.end()));

    return combinations;
}

// Função para calcular suporte e confiança para uma nova entrada
void calculateSupportAndConfidence(const vector<pair<int, int>>& instance, 
                                   const map<pair<int, int>, vector<int>>& tupleLines, 
                                   const map<int, vector<int>>& classLines,
                                   const string& output_filename) {
    map<int, double> classSupport;
    map<int, double> classConfidence;

    for (const auto& classEntry : classLines) {
        int classLabel = classEntry.first;
        const auto& classLineNumbers = classEntry.second;

        double totalSupport = 0.0;
        double totalConfidence = 0.0;
        int count = 0;

        for (size_t size = 1; size <= instance.size(); ++size) {
            auto combinations = generateCombinations(instance, static_cast<int>(size));
            for (const auto& combination : combinations) {
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
                    totalSupport += calculateSupport(combinedLines, classLineNumbers);
                    totalConfidence += calculateConfidence(combinedLines, classLineNumbers);
                    ++count;
                }
            }
        }

        if (count > 0) {
            classSupport[classLabel] = totalSupport / count;
            classConfidence[classLabel] = totalConfidence / count;
        }
    }

    // Gravar suporte e confiança em um arquivo
    ofstream file(output_filename);
    if (!file.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo '" + output_filename + "' para escrita.");
    }

    file << "Suporte e Confianca para a nova entrada:" << endl;
    for (const auto& entry : classSupport) {
        file << "Classe: " << entry.first << ", Suporte: " << entry.second 
             << ", Confianca: " << classConfidence[entry.first] << endl;
    }

    file.close();
}

int main() {
    // Mensagens de status
    cout << "--------------------------------------------" << endl;
    cout << "Calculo de suporte e confianca para uma nova entrada" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Processando arquivo de dados..." << endl;
    cout << "--------------------------------------------" << endl;


    try {
        // Substitua o caminho do arquivo pelo caminho correto
        DataProcessor dp("C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/Arquivos/poker-hand-testing.data");
        dp.processFile(); // Processa o arquivo e preenche os mapas de tuplas e classes
        const auto& tupleMap = dp.getTupleMap(); // Obtém o mapa de tuplas
        const auto& classMap = dp.getClassMap(); // Obtém o mapa de classes

        map<pair<int, int>, vector<int>> tupleLines;
        map<int, vector<int>> classLines;

        for (const auto& entry : tupleMap) {
            tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
        }

        for (const auto& entry : classMap) {
            classLines[entry.first] = entry.second;
        }

        vector<pair<int, int>> newInstance = {{1, 10}, {1, 11}, {1, 13}, {1, 12}, {1, 1}};

        // Verifica se o diretório de saída existe e cria se necessário
        string output_dir = "C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output";
        if (_mkdir(output_dir.c_str()) != 0 && errno != EEXIST) { // Cria diretório no Windows
            cerr << "Erro ao criar o diretório '" << output_dir << "'." << endl;
            return 1;
        }

        string output_filename = "/support_confidence_cpp.txt";
        string output_path = output_dir;
        calculateSupportAndConfidence(newInstance, tupleLines, classLines, output_filename);
        cout << "--------------------------------------------" << endl;
        cout << "Calculo concluido com sucesso! Resultados gravados em: " << output_filename << endl;
        //cout << " Path do arquivo : "<< output_path+output_filename << endl; 
        cout << "--------------------------------------------" << endl;
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }

    return 0;
}
