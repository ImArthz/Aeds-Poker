#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

void processLine(const std::vector<int>& lineData) {
    // Exemplo de processamento para cada linha lida
    std::cout << "Processando linha: ";
    for (int num : lineData) {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

void readDataFile(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (file.is_open()) {
        while (std::getline(file, line)) {
            std::vector<int> lineData;
            std::stringstream ss(line);
            std::string value;

            // Separar a linha pelos valores inteiros
            while (std::getline(ss, value, ',')) {
                lineData.push_back(std::stoi(value));
            }

            // Chama uma função para processar a linha lida
            processLine(lineData);
        }
        file.close();
    } else {
        std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
    }
}

int main() {
    std::string filename = "D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data";
    readDataFile(filename);
    return 0;
}
