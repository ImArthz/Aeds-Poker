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
#include <chrono> // Inclua para medir o tempo
#include <thread> // Inclua para usar threads
#include <mutex> // Inclua para usar mutex
#include "DataProcessor.h"

using namespace std;
using namespace std::chrono;

// Função para calcular o suporte
double calculateSupport(const vector<int>& tupleLines, const vector<int>& classLines) {
    set<int> intersection;
    set_intersection(tupleLines.begin(), tupleLines.end(), classLines.begin(), classLines.end(),
                     inserter(intersection, intersection.begin()));
    return static_cast<double>(intersection.size()) / classLines.size();
}

// Função para calcular a confiança
double calculateConfidence(const vector<int>& tupleLines, const vector<int>& classLines) {
    if (tupleLines.empty()) {
        return 0.0; // Evitar divisão por zero
    }
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
void calculateSupportAndConfidence(const vector<tuple<int, int>>& instance, 
                                   const map<tuple<int, int>, vector<int>>& tupleLines, 
                                   const map<int, vector<int>>& classLines,
                                   ofstream& file, int lineNumber, mutex& fileMutex) {
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
    int count = 0;
    // Gravar suporte e confiança em um arquivo
    lock_guard<mutex> guard(fileMutex); // Bloqueia o mutex para acesso ao arquivo
    for (const auto& entry : classSupport) {
        file << "classe " << count << ", linha " << lineNumber << ", suporte " << entry.second 
             << ", confiança " << classConfidence[entry.first] << endl;
        ++count;
    }
}

int main() {
    // Mensagens de status
    cout << "--------------------------------------------" << endl;
    cout << "Calculo de suporte e confianca para o arquivo testing.data" << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Processando arquivo de dados..." << endl;
    cout << "--------------------------------------------" << endl;

    try {
        // Substitua o caminho do arquivo pelo caminho correto
        DataProcessor dptraining("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data");
        dptraining.processFile(); // Processa o arquivo e preenche os mapas de tuplas e classes

        const auto& tupleMap = dptraining.getTupleMap(); // Obtém o mapa de tuplas
        const auto& classMap = dptraining.getClassMap(); // Obtém o mapa de classes

        map<tuple<int, int>, vector<int>> tupleLines;
        map<int, vector<int>> classLines;

        for (const auto& entry : tupleMap) {
            tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
        }

        for (const auto& entry : classMap) {
            classLines[entry.first] = entry.second;
        }

        // Verifica se o diretório de saída existe e cria se necessário
        string output_dir = "D:/Documentos/cefet/AEDS/Aeds-Poker/c++ test/output";
        if (_mkdir(output_dir.c_str()) != 0 && errno != EEXIST) { // Cria diretório no Windows
            cerr << "Erro ao criar o diretório '" << output_dir << "'." << endl;
            return 1;
        }

        string output_filename = output_dir + "/support_confidence_cpp.txt";
        ofstream file(output_filename);
        if (!file.is_open()) {
            throw runtime_error("Erro ao abrir o arquivo '" + output_filename + "' para escrita.");
        }

        cout << "Arquivo de treino processados com sucesso!" << endl;

        DataProcessor dptesting("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-testing.data");
        dptesting.processFile(); // Processa o arquivo e preenche os mapas de tuplas e classes
        const auto& tupleVector = dptesting.getTupleVector(); // Obtém o vetor de tuplas

        // Medir o tempo de execução do loop
        auto start = high_resolution_clock::now();

        // Número de threads a serem usadas
        const int numThreads = thread::hardware_concurrency();
        vector<thread> threads;
        mutex fileMutex;
        mutex lineNumberMutex;
        int lineNumber = 1;

        // Dividir o trabalho entre as threads
        int chunkSize = tupleVector.size() / numThreads;
        for (int i = 0; i < numThreads; ++i) {
            int startIdx = i * chunkSize;
            int endIdx = (i == numThreads - 1) ? tupleVector.size() : (i + 1) * chunkSize;
            threads.emplace_back([&, startIdx, endIdx]() {
                for (int j = startIdx; j < endIdx; ++j) {
                    int currentLineNumber;
                    {
                        lock_guard<mutex> guard(lineNumberMutex);
                        currentLineNumber = lineNumber++;
                    }
                    calculateSupportAndConfidence(tupleVector[j], tupleLines, classLines, file, currentLineNumber, fileMutex);
                }
            });
        }

        // Esperar todas as threads terminarem
        for (auto& t : threads) {
            t.join();
        }

        auto end = high_resolution_clock::now();
        auto duration = duration_cast<seconds>(end - start);

        file.close();
        cout << "--------------------------------------------" << endl;
        cout << "Calculo concluido com sucesso! Resultados gravados em: " << output_filename << endl;
        cout << "Tempo de execucao: " << duration.count() << " segundos" << endl;
        cout << "--------------------------------------------" << endl;
    } catch (const exception& e) {
        cerr << "Erro: " << e.what() << endl;
        return 1;
    }

    return 0;
}