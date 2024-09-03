#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <execution>

// Estrutura personalizada de hash para std::tuple<int, int>
struct TupleHash {
    template <typename T1, typename T2>
    std::size_t operator()(const std::tuple<T1, T2>& tuple) const {
        auto hash1 = std::hash<T1>{}(std::get<0>(tuple));
        auto hash2 = std::hash<T2>{}(std::get<1>(tuple));
        return hash1 ^ (hash2 << 1);
    }
};

class DataProcessor {
public:
    DataProcessor(const std::string& filename) : filename(filename) {}

    void processFile() {
        std::ifstream file(filename);
        std::string line;
        int lineNumber = 0;

        if (file.is_open()) {
            std::cout << "Processando o arquivo: " << filename << std::endl;

            while (std::getline(file, line)) {
                lineNumber++;
                processLine(line, lineNumber);
            }
            file.close();
            writeTupleMapToFile("tupleMap.txt");
            writeClassMapToFile("classMap.txt");

            std::cout << "Arquivo processado e mapas gravados com sucesso!" << std::endl;
        } else {
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
        }
    }

    const std::unordered_map<std::tuple<int, int>, std::vector<int>, TupleHash>& getTupleMap() const {
        return tupleMap;
    }

    const std::unordered_map<int, std::vector<int>>& getClassMap() const {
        return classMap;
    }

    const std::vector<std::vector<std::pair<int, int>>>& getTupleVector() const {
        return tupleVector;
    }

private:
    std::string filename;
    std::unordered_map<std::tuple<int, int>, std::vector<int>, TupleHash> tupleMap;
    std::unordered_map<int, std::vector<int>> classMap;
    std::vector<std::vector<std::pair<int, int>>> tupleVector;

    void processLine(const std::string& line, int lineNumber) {
        std::istringstream iss(line);
        std::string value;
        int position = 1;
        std::vector<std::pair<int, int>> currentLineTuples;

        while (std::getline(iss, value, ',')) {
            int num = std::stoi(value);
            if (position < 11) {
                std::tuple<int, int> tuple = std::make_tuple(position, num);
                tupleMap[tuple].push_back(lineNumber);
                currentLineTuples.push_back(tuple);
            } else {
                classMap[num].push_back(lineNumber);
            }
            position++;
        }

        tupleVector.push_back(currentLineTuples);
    }

    void writeTupleMapToFile(const std::string& outputFilename) {
        std::ofstream outFile(outputFilename); // Abre o arquivo de saída

        if (outFile.is_open()) {
            for (const auto& entry : tupleMap) {
                outFile << "(" << std::get<0>(entry.first) << "," << std::get<1>(entry.first) << "): ";
                for (int ln : entry.second) {
                    outFile << ln << " ";
                }
                outFile << std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "Não foi possivel abrir o arquivo para escrita: " << outputFilename << std::endl;
        }
    }

    void writeClassMapToFile(const std::string& outputFilename) {
        std::ofstream outFile(outputFilename); // Abre o arquivo de saída

        if (outFile.is_open()) {
            for (const auto& pair : classMap) {
                outFile << pair.first << ": ";
                for (int value : pair.second) {
                    outFile << value << " ";
                }
                outFile << std::endl;
            }
            outFile.close();
        } else {
            std::cerr << "Não foi possivel abrir o arquivo para escrita: " << outputFilename << std::endl;
        }
    }
};

int main() {
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Iniciando o processamento do arquivo..." << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    DataProcessor dp("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data");
    dp.processFile();
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << "Processamento concluido." << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;

    // Exemplo de como acessar o tupleVector
    // const auto& tupleVector = dp.getTupleVector();
    // for (size_t i = 0; i < tupleVector.size(); ++i) {
    //     std::cout << "Linha " << i + 1 << ": ";
    //     for (const auto& tuple : tupleVector[i]) {
    //         std::cout << "{" << std::get<0>(tuple) << ", " << std::get<1>(tuple) << "} ";
    //     }
    //     std::cout << std::endl;
    // }

    return 0;
}