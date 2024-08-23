#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <tuple>
#include <string>

// Estrutura personalizada de hash para std::tuple<int, int>
struct TupleHash
{
    // Operador () sobrecarregado para calcular o hash de uma tupla
    template <typename T1, typename T2>
    std::size_t operator()(const std::tuple<T1, T2> &tuple) const
    {
        // Calcula os hashes dos elementos da tupla
        auto hash1 = std::hash<T1>{}(std::get<0>(tuple));
        auto hash2 = std::hash<T2>{}(std::get<1>(tuple));
        // Combina os hashes usando XOR e deslocamento de bits
        return hash1 ^ (hash2 << 1);
    }
};

// Classe que processa os dados do arquivo
class DataProcessor
{
public:
    // Construtor que inicializa o nome do arquivo
    DataProcessor(const std::string &filename) : filename(filename) {}

    // Função que processa o arquivo
    void processFile()
    {
        // Abre o arquivo para leitura
        std::ifstream file(filename);
        std::string line;
        int lineNumber = 0;

        // Verifica se o arquivo foi aberto com sucesso
        if (file.is_open())
        {
            // Lê o arquivo linha por linha
            while (std::getline(file, line))
            {
                lineNumber++; // Incrementa o número da linha atual
                // Processa a linha atual
                processLine(line, lineNumber);
            }
            file.close(); // Fecha o arquivo após a leitura

            // Escreve o conteúdo do tupleMap no arquivo "readme.txt"
            writeTupleMapToFile("tupleMap.txt");
            writeClassMapToFile("classMap.txt");
        }
        else
        {
            // Mensagem de erro caso o arquivo não possa ser aberto
            std::cerr << "Não foi possível abrir o arquivo: " << filename << std::endl;
        }
    }

private:
    std::string filename; // Nome do arquivo de entrada
    // unordered_map que armazena as tuplas como chaves e vetores de números de linha como valores
    std::unordered_map<std::tuple<int, int>, std::vector<int>, TupleHash> tupleMap;

    // unordered_map que armazena a classe como chave e vetores de números de linha como valores
    std::unordered_map<int, std::vector<int>> classMap;

    // Função que processa uma linha do arquivo
    void processLine(const std::string &line, int lineNumber)
    {
        std::stringstream ss(line); // Cria um stream a partir da linha lida
        std::string value;
        int position = 1; // Posição inicial para as tuplas

        // Divide a linha pelos valores separados por vírgula
        while (std::getline(ss, value, ','))
        {
            int num = std::stoi(value); // Converte o valor lido para inteiro
            // Exclui o último número (classe) do mapeamento de tuplas
            if (position < 11)
            {
                // Cria uma tupla (posição, valor)
                std::tuple<int, int> key = std::make_tuple(position, num);
                // Adiciona o número da linha ao vetor associado à tupla no unordered_map
                tupleMap[key].push_back(lineNumber);
            }
            else if (position == 11)
            {
                // Adiciona o número da linha ao vetor associado à classe no unordered_map
                classMap[num].push_back(lineNumber);
            }

            position++; // Incrementa a posição
        }
    }

    // Função que escreve o conteúdo do tupleMap em um arquivo
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
                    outFile << ln << ", ";
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
                outFile << "[" << pair.first << "]: ";
                for (int value : pair.second)
                {
                    outFile << value << ", ";
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

int main()
{
    // Nome do arquivo de entrada
    std::string filename = "D:/Documentos/cefet/AEDS/Aeds-Poker/Arquivos/poker-hand-training.data";
    DataProcessor processor(filename); // Cria um objeto DataProcessor com o nome do arquivo
    processor.processFile();           // Processa o arquivo

    return 0;
}
