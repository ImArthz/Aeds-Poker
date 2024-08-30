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
#include <mutex>

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
            while (std::getline(file, line)) {
                lineNumber++;
                processLine(line, lineNumber);
            }
            file.close();
        } else {
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
        }
        writeTupleMapToFile("tupleMap.txt");
        writeClassMapToFile("classMap.txt");
    }

    const std::unordered_map<std::tuple<int, int>, std::vector<int>, TupleHash>& getTupleMap() const {
        return tupleMap;
    }

    const std::unordered_map<int, std::vector<int>>& getClassMap() const {
        return classMap;
    }

private:
    std::string filename;
    std::unordered_map<std::tuple<int, int>, std::vector<int>, TupleHash> tupleMap;
    std::unordered_map<int, std::vector<int>> classMap;
    std::mutex mtx;

    void processLine(const std::string& line, int lineNumber) {
        std::istringstream iss(line);
        std::string value;
        int position = 1;

        while (std::getline(iss, value, ',')) {
            int num = std::stoi(value);
            if (position < 11) {
                std::tuple<int, int> tuple = std::make_tuple(position, num);
                tupleMap[tuple].push_back(lineNumber);
            } else {
                classMap[num].push_back(lineNumber);
            }
            position++;
        }
        
    }

    void writeTupleMapToFile(const std::string &outputFilename)
    {
        std::ofstream outFile(outputFilename); // Abre o arquivo de saída

        // Verifica se o arquivo foi aberto com sucesso
        if (outFile.is_open())
        {
            // Itera sobre o tupleMap para escrever cada entrada no arquivo
            for (const auto &entry : tupleMap)
            {
                // Escreve a tupla e os números de linha associados
                outFile << "(" << std::get<0>(entry.first) << "," << std::get<1>(entry.first) << "): ";
                // Escreve todos os números de linha onde a tupla aparece
                for (int ln : entry.second)
                {
                    outFile << ln << " ";
                }
                outFile << std::endl; // Nova linha após cada entrada
            }
            outFile.close(); // Fecha o arquivo de saída
        }
        else
        {
            // Mensagem de erro caso o arquivo não possa ser aberto para escrita
            std::cerr << "Não foi possível abrir o arquivo para escrita: " << outputFilename << std::endl;
        }
    }

    void writeClassMapToFile(const std::string &outputFilename)
    {
        std::ofstream outFile(outputFilename); // Abre o arquivo de saída

        // Verifica se o arquivo foi aberto com sucesso
        if (outFile.is_open())
        {
            // Itera sobre o classMap para escrever cada entrada no arquivo
            for (const auto &pair : classMap)
            {
                outFile << pair.first << ": ";
                for (int value : pair.second)
                {
                    outFile << value << " ";
                }
                outFile << std::endl;
            }
            outFile.close(); // Fecha o arquivo de saída
        }
        else
        {
            // Mensagem de erro caso o arquivo não possa ser aberto para escrita
            std::cerr << "Não foi possível abrir o arquivo para escrita: " << outputFilename << std::endl;
        }
    }
};

// int main() {
//     DataProcessor dp("D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data");
//     dp.processFile();
//     const auto& tupleMap = dp.getTupleMap();
//     const auto& classMap = dp.getClassMap();

//     // Exemplo de uso dos mapas
//     // for (const auto& entry : tupleMap) {
//     //     std::cout << "(" << std::get<0>(entry.first) << ", " << std::get<1>(entry.first) << "): ";
//     //     for (const auto& line : entry.second) {
//     //         std::cout << line << " ";
//     //     }
//     //     std::cout << "\n";
//     // }

//     // for (const auto& entry : classMap) {
//     //     std::cout << entry.first << ": ";
//     //     for (const auto& line : entry.second) {
//     //         std::cout << line << " ";
//     //     }
//     //     std::cout << "\n";
//     // }

//     return 0;
// }