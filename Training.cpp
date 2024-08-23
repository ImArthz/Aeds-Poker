#include "Training.hpp"
#include <unordered_map>
#include <unordered_set>

using namespace std;
Training::Training(){}

void Training::setPokerTraining(string poker_training)
{
    this->poker_training = poker_training;
}
void Training::setPokerTest(string poker_test)
{
    this->poker_test = poker_test;
}

vector<vector<int>> Training::HashTraining() {
    fstream arquivo;
    arquivo.open(poker_training, ios::in);
    if (!arquivo) {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(0);
    }

    unordered_map<pair<int, int>, unordered_set<int>, hash_pair> feature_map;
    unordered_map<int, unordered_set<int>> class_map;

    string linha;
    int line_index = 0;

    while (getline(arquivo, linha)) {
        stringstream s(linha);
        string valor;
        vector<int> row_values;
        int col_index = 0;

        while (getline(s, valor, ',')) {
            int num = stoi(valor);
            row_values.push_back(num);

            if (col_index < row_values.size() - 1) {
                feature_map[{col_index, num}].insert(line_index);
            }
            ++col_index;
        }

        int classe = row_values.back();
        class_map[classe].insert(line_index);

        ++line_index;
    }

    arquivo.close();

    // Convert maps to vectors for output
    vector<vector<int>> result;
    for (const auto& entry : feature_map) {
        vector<int> record;
        record.push_back(entry.first.first); // Column index
        record.push_back(entry.first.second); // Feature value
        result.push_back(record);
    }

    for (const auto& entry : class_map) {
        vector<int> record;
        record.push_back(-1); // Indicating class data
        record.push_back(entry.first); // Class
        result.push_back(record);
    }

    return result;
}



vector<vector<int>> Training::HashTraining()
{
    fstream arquivo;
    arquivo.open(poker_training, ios::in);
    if (!arquivo)
    {
        cout << "Erro ao abrir o arquivo" << endl;
        exit(0);
    }

    vector<vector<int>> data;
    string linha, valor;
// função parar ler arquivo e fazer a hash 

    while (getline(arquivo, linha))
    {
        stringstream s(linha);
        vector<int> row;
        while (getline(s, valor, ','))
        {
            row.push_back(stoi(valor));
        }
        data.push_back(row);
    }

    arquivo.close();
    return data;
}