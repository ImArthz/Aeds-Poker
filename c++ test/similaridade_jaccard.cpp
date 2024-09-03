#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <utility>

using namespace std;

// Função para carregar o mapa de tuplas do arquivo
map<pair<int, int>, set<int>> loadTupleMap(const string& filename) {
    map<pair<int, int>, set<int>> tupleMap;
    ifstream file(filename);

    if (!file.is_open()) {
        throw runtime_error("Erro: Não foi possível abrir o arquivo '" + filename + "'.");
    }
    else {
        cout << "Arquivo aberto com sucesso!" << endl;
        cout <<" ------------------------------------------------" << endl;
        cout <<" Iniciando a leitura do arquivo..." << endl;
    }

    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string keyStr, valuesStr;
        getline(iss, keyStr, ':');
        getline(iss, valuesStr);

        // Remove parênteses e separa os números
        keyStr = keyStr.substr(1, keyStr.size() - 2); // Remove os parênteses
        istringstream keyStream(keyStr);
        int x, y;
        char comma;
        keyStream >> x >> comma >> y;
        pair<int, int> key = make_pair(x, y);

        // Converte os valores em um conjunto
        set<int> values;
        istringstream valueStream(valuesStr);
        string value;
        while (valueStream >> value) {
            values.insert(stoi(value));
        }

        tupleMap[key] = values;
    }

    file.close();
    return tupleMap;
}

// Função para calcular a similaridade de Jaccard
double calculateJaccard(const set<int>& set1, const set<int>& set2) {
    set<int> intersection;
    set<int> unionSet;

    // Calcula a interseção e a união
    for (int value : set1) {
        if (set2.find(value) != set2.end()) {
            intersection.insert(value);
        }
        unionSet.insert(value);
    }
    for (int value : set2) {
        unionSet.insert(value);
    }

    // Calcula a similaridade
    if (unionSet.empty()) return 0.0;
    return static_cast<double>(intersection.size()) / unionSet.size();
}

// Função para calcular todas as similaridades
map<pair<pair<int, int>, pair<int, int>>, double> calculateAllSimilarities(const map<pair<int, int>, set<int>>& tupleMap) {
    map<pair<pair<int, int>, pair<int, int>>, double> similarities;
    vector<pair<int, int>> keys;

    // Coleta todas as chaves
    for (const auto& entry : tupleMap) {
        keys.push_back(entry.first);
    }

    // Calcula a similaridade entre todas as combinações de chaves
    for (size_t i = 0; i < keys.size(); ++i) {
        for (size_t j = i + 1; j < keys.size(); ++j) {
            double similarity = calculateJaccard(tupleMap.at(keys[i]), tupleMap.at(keys[j]));
            similarities[make_pair(keys[i], keys[j])] = similarity;
        }
    }

    return similarities;
}

// Função para escrever as similaridades em um arquivo
void writeSimilaritiesToFile(const map<pair<pair<int, int>, pair<int, int>>, double>& similarities, const string& outputFilename) {
    ofstream outFile(outputFilename);

    if (!outFile.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo '" + outputFilename + "' para escrita.");
    }
    else {
        cout << endl;
        cout << "Arquivo de saida aberto com sucesso!" << endl;
        cout << "------------------------------------------------" << endl;
        cout << "Escrevendo similaridades no arquivo..." << endl;
    }

    for (const auto& entry : similarities) {
        outFile << "Similaridade((" << entry.first.first.first << "," << entry.first.first.second << "), "
                << "(" << entry.first.second.first << "," << entry.first.second.second << ")) = " << entry.second << endl;
    }

    outFile.close();
}

int main() {
    string inputFilename = "C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/tupleMap.txt"; // Substitua pelo caminho correto do arquivo
    string outputFilename = "C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/similaridade_cpp.txt"; // Substitua pelo caminho desejado para a saída

    try {
        // Carrega o mapa de tuplas
        auto tupleMap = loadTupleMap(inputFilename);

        // Calcula as similaridades
        auto similarities = calculateAllSimilarities(tupleMap);

        // Escreve as similaridades no arquivo
        writeSimilaritiesToFile(similarities, outputFilename);
        cout << endl;
        cout << "Similaridades calculadas com sucesso no arquivo " << outputFilename << endl;
    } catch (const exception& e) {
        cerr << e.what() << endl;
    }

    return 0;
}