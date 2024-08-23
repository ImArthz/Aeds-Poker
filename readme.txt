# Processador de Arquivos de Dados

Este programa em C++ processa um arquivo de dados, onde cada linha contém uma série de números inteiros. Ele mapeia esses números em tuplas `(posição, valor)` e classes, armazenando essas informações em mapas (`unordered_map`) e gravando os resultados em arquivos de saída.

## Estrutura do Projeto

### Estrutura `TupleHash`
Uma estrutura personalizada que define um hash para `std::tuple<int, int>`. O operador `()` é sobrecarregado para calcular um hash baseado nos valores da tupla, combinando-os com uma operação de XOR e deslocamento de bits. Isso permite que tuplas sejam usadas como chaves em um `unordered_map`.

### Classe `DataProcessor`
Esta classe é a responsável por processar o arquivo de entrada, armazenar os dados em mapas e gravar os resultados em arquivos de saída.

#### Atributos:
- **`filename`**: Nome do arquivo a ser processado.
- **`tupleMap`**: Um `unordered_map` que associa tuplas `(posição, valor)` a um vetor com os números das linhas onde essa tupla aparece.
- **`classMap`**: Um `unordered_map` que associa classes a um vetor com os números das linhas onde essas classes aparecem.

#### Métodos:
- **`DataProcessor(const std::string &filename)`**: Construtor que inicializa a classe com o nome do arquivo.
  
- **`void processFile()`**:
  - Abre o arquivo especificado.
  - Lê o arquivo linha por linha e chama `processLine` para processar cada linha.
  - Depois de processar todas as linhas, chama `writeTupleMapToFile` e `writeClassMapToFile` para salvar os mapas em arquivos.

- **`void processLine(const std::string &line, int lineNumber)`**:
  - Processa uma linha do arquivo, dividindo-a em valores.
  - Para as primeiras 10 colunas, cria uma tupla `(posição, valor)` e mapeia essa tupla ao número da linha atual em `tupleMap`.
  - A última coluna é tratada como uma classe, mapeando o número da linha em `classMap`.

- **`void writeTupleMapToFile(const std::string &outputFilename)`**:
  - Escreve o conteúdo de `tupleMap` em um arquivo especificado. Para cada tupla, grava as linhas em que ela aparece.

- **`void writeClassMapToFile(const std::string &outputFilename)`**:
  - Escreve o conteúdo de `classMap` em um arquivo especificado. Para cada classe, grava as linhas em que a classe aparece.

### Função `main()`
- Cria um objeto `DataProcessor` com o nome do arquivo de entrada.
- Chama `processFile()` para iniciar o processamento do arquivo e grava os resultados nos arquivos de saída.

## Objetivo
O objetivo do programa é ler um arquivo de dados onde cada linha contém uma série de números inteiros. Esses números são divididos em tuplas `(posição, valor)` e em uma classe. O programa mapeia as tuplas e as classes aos números das linhas em que aparecem, permitindo que essas informações sejam analisadas e salvas em arquivos para futuras consultas.

## Como Usar
1. Compile o código em C++.
2. Especifique o caminho do arquivo de entrada no código.
3. Execute o programa. Ele processará o arquivo e criará dois arquivos de saída:
   - `tupleMap.txt`: Contém as tuplas `(posição, valor)` e as linhas em que aparecem.
   - `classMap.txt`: Contém as classes e as linhas em que aparecem.

## Exemplo de Uso
```cpp
int main()
{
    // Nome do arquivo de entrada
    std::string filename = "caminho/para/o/seu/arquivo.data";
    DataProcessor processor(filename); // Cria um objeto DataProcessor com o nome do arquivo
    processor.processFile();           // Processa o arquivo

    return 0;
}
