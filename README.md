# Processador de Arquivos de Dados

Este programa em C++ processa um arquivo de dados, onde cada linha contém uma série de números inteiros. Ele mapeia esses números em tuplas `(posição, valor)` e classes, armazenando essas informações em mapas (`unordered_map`) e gravando os resultados em arquivos de saída.

## Estrutura do Projeto

### Estrutura `TupleHash`
Uma estrutura personalizada que define um hash para `std::tuple<int, int>`. O operador `()` é sobrecarregado para calcular um hash baseado nos valores da tupla, combinando-os com uma operação de XOR e deslocamento de bits. Isso permite que tuplas sejam usadas como chaves em um `unordered_map`.

### Classe `DataProcessor`
Esta classe é responsável por processar o arquivo de entrada, armazenar os dados em mapas e gravar os resultados em arquivos de saída.

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

## Scripts Python para Verificação

Além do código C++, dois scripts Python estão disponíveis para verificar a consistência dos cálculos de similaridade entre conjuntos de dados.

### Script 1: Cálculo e Gravação de Similaridades

#### Descrição
Este script calcula a similaridade entre pares de conjuntos de inteiros usando o Índice de Jaccard e grava os resultados em um arquivo.

#### Funções
1. **`load_tuplemap(filename)`**
   - Carrega um mapa de tuplas e conjuntos a partir de um arquivo.
2. **`calculate_jaccard(set1, set2)`**
   - Calcula a similaridade de Jaccard entre dois conjuntos.
3. **`calculate_all_similarities(tuple_map)`**
   - Calcula a similaridade de Jaccard para todos os pares de chaves no mapa de tuplas.
4. **`write_similarities_to_file(similarities, output_filename)`**
   - Grava as similaridades calculadas em um arquivo de saída.

#### Exemplo de Uso
```python
filename = 'caminho/para/tupleMap.txt'
output_filename = 'caminho/para/similaridadePython.txt'

tuple_map = load_tuplemap(filename)
similarities = calculate_all_similarities(tuple_map)
success = write_similarities_to_file(similarities, output_filename)

if success == 1:
    print(f"Similaridades calculadas com sucesso no arquivo {output_filename}")
else:
    print(f"Erro ao calcular similaridades")
```
# Script 2: Comparação de Similaridades

## Descrição
Este script carrega similaridades de dois arquivos (uma implementação Python e outra C++) e compara os resultados para verificar se estão consistentes.

## Funções

### `load_similarities_from_file(filename)`
Carrega similaridades de um arquivo.

### `compare_similarities(similarities_python, similarities_cpp, precision=6)`
Compara as similaridades de dois dicionários e identifica discrepâncias.

### `write_comparison_results(discrepancies, iguais, diferentes, output_file)`
Grava os resultados da comparação em um arquivo.

## Exemplo de Uso
```python
python_similarities_file = 'caminho/para/similaridadePython.txt'
cpp_similarities_file = 'caminho/para/similaridade.txt'
output_file = 'caminho/para/discrepancias.txt'

similarities_python = load_similarities_from_file(python_similarities_file)
similarities_cpp = load_similarities_from_file(cpp_similarities_file)

discrepancies, iguais, diferentes = compare_similarities(similarities_python, similarities_cpp)
write_comparison_results(discrepancies, iguais, diferentes, output_file)

print(f"Comparação concluída. Resultados escritos em '{output_file}'.")
```
## Contribuidores

Feito Por : 

[![Arthur Mendonça](https://img.shields.io/badge/Arthur%20Mendonça-GitHub-black?style=flat&logo=github)](https://github.com/ImArthz)

[![Thiago](https://img.shields.io/badge/Thiago-GitHub-black?style=flat&logo=github)](https://github.com/Thiago-Mi)

[![Arthur Santana](https://img.shields.io/badge/Arthur%20Santana-GitHub-black?style=flat&logo=github)](https://github.com/Rutrama)




