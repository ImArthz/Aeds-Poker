#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
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

        int lineNumber = 0;
        // Leitura do arquivo linha por linha
        while (getline(file, line)) {
            lineNumber++;
            processLine(line, lineNumber);
        }
        file.close();
    }

    const map<tuple<int, int>, vector<int>>& getTupleMap() const {
        return tupleMap;
    }

    const map<int, vector<int>>& getClassMap() const {
        return classMap;
    }

    const vector<vector<tuple<int, int>>>& getTupleVector() const {
        return tupleVector;
    }

private:
    string filename;
    map<tuple<int, int>, vector<int>> tupleMap;
    map<int, vector<int>> classMap;
    vector<vector<tuple<int, int>>> tupleVector;

    void processLine(const string& line, int lineNumber) {
        istringstream iss(line);
        string value;
        int position = 1;
        vector<tuple<int, int>> currentLineTuples;

        while (getline(iss, value, ',')) {
            int num = stoi(value);
            if (position < 11) {
                tuple<int, int> tuple = make_tuple(position, num);
                tupleMap[tuple].push_back(lineNumber);
                currentLineTuples.push_back(tuple);
            } else {
                classMap[num].push_back(lineNumber);
            }
            position++;
        }

        tupleVector.push_back(currentLineTuples);
    }
};