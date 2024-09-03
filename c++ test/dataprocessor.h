#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#pragma once
#include <tuple>

using namespace std;

// Classe para processar o arquivo de dados
class DataProcessor {
public:
    DataProcessor(const string& filename) : filename(filename) {}

    void processFile() {
        ifstream file(filename);
        string line;

        if (!file.is_open()) {
            cerr << "Não foi possível abrir o arquivo!" << endl;
            return;
        }

        // Leitura do arquivo linha por linha
        while (getline(file, line)) {
            istringstream iss(line);
            vector<int> values;
            string value;

            // Leitura dos valores separados por vírgula
            while (getline(iss, value, ',')) {
                values.push_back(stoi(value));
            }

            if (values.size() >= 2) {
                int classLabel = values.back(); // Último valor é a classe
                values.pop_back(); // Remove a classe para deixar apenas os atributos
                tupleMap[{values[0], values[1]}].push_back(classLabel); // Supondo que estamos usando 2 atributos
                classMap[classLabel].push_back(values[0]); // Adiciona o atributo à classe
            }
        }

        file.close();
    }

    const map<pair<int, int>, vector<int>>& getTupleMap() const {
        return tupleMap;
    }

    const map<int, vector<int>>& getClassMap() const {
        return classMap;
    }

private:
    string filename;
    map<pair<int, int>, vector<int>> tupleMap;
    map<int, vector<int>> classMap;
};
