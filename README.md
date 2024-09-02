# Introdução

Este projeto implementa um algoritmo de classificação baseado em regras associativas, conhecido como Lazy Associative Classification (LAC).  
O LAC é um método de aprendizado de máquina que utiliza regras de associação para classificar novas instâncias com base em dados históricos.  
O projeto é composto por três arquivos principais:

1. `leitura_input.cpp`
2. `similaridade_jaccard.cpp`
3. `calculo_suporte_confianca.cpp`

Cada arquivo desempenha um papel específico no processamento dos dados, cálculo de similaridades e avaliação de suporte e confiança para a classificação.

## Arquivo 1: leitura_input.cpp

### Descrição

Este arquivo é responsável por ler e processar o arquivo de entrada contendo os dados. Ele cria mapas de tuplas e classes que são utilizados posteriormente para cálculos de similaridade e classificação.

### Estruturas e Classes

- **TupleHash**: Estrutura personalizada de hash para `std::tuple<int, int>`.
- **DataProcessor**: Classe principal que processa o arquivo de entrada e popula os mapas de tuplas e classes.

### Funções Principais

- **`processFile()`**: Lê o arquivo de entrada linha por linha e processa cada linha para preencher os mapas de tuplas e classes.
- **`processLine()`**: Processa uma linha do arquivo de entrada, dividindo-a em valores e populando os mapas de tuplas e classes.
- **`writeTupleMapToFile()`**: Escreve o conteúdo do mapa de tuplas em um arquivo de saída.
- **`writeClassMapToFile()`**: Escreve o conteúdo do mapa de classes em um arquivo de saída.

### Exemplo de Uso


-   DataProcessor dp("caminho/para/arquivo-de-entrada.data");
    dp.processFile();

## Arquivo 2: similaridade_jaccard.cpp

### Descrição

Este arquivo calcula a similaridade de Jaccard entre as tuplas processadas no arquivo de entrada. A similaridade de Jaccard é uma métrica que avalia a similaridade entre dois conjuntos, sendo especialmente útil em aplicações que envolvem comparação de conjuntos de itens.

### Estruturas e Classes

- **PairIntHash**: Estrutura de hash personalizada para `std::pair<int, int>`, utilizada para otimizar o armazenamento e a busca de pares de inteiros.
- **PairHash**: Estrutura de hash personalizada para `std::pair<std::pair<int, int>, std::pair<int, int>>`, usada para armazenar pares de pares de inteiros.
- **JaccardSimilarityCalculator**: Classe principal responsável por calcular as similaridades de Jaccard entre as tuplas processadas.

### Funções Principais

- **`process()`**: Coordena o cálculo das similaridades de Jaccard, incluindo a conversão dos mapas de tuplas, cálculo dos parâmetros necessários e escrita dos resultados em um arquivo.
- **`convertMaps()`**: Converte estruturas `unordered_map` para `map`, preservando a ordem dos elementos, o que facilita a análise e a visualização dos dados.
- **`calculateParams()`**: Calcula os parâmetros necessários para a avaliação da similaridade, como a interseção e a união dos conjuntos de tuplas.
- **`jaccardSimilarity()`**: Calcula a similaridade de Jaccard entre dois conjuntos específicos, retornando um valor que varia de 0 a 1, onde 1 indica máxima similaridade.
- **`calculateSimilarities()`**: Realiza o cálculo das similaridades entre todas as combinações possíveis de tuplas e armazena os resultados em um `unordered_map`.
- **`writeSimilaritiesToFile()`**: Escreve as similaridades calculadas em um arquivo de saída para posterior análise.

### Exemplo de Uso


-   JaccardSimilarityCalculator calculator("caminho/para/arquivo-de-entrada.data");
    calculator.process();


## Arquivo 3: calculo_suporte_confianca.cpp

### Descrição

Este arquivo é responsável pelo cálculo do suporte e da confiança para novas instâncias, utilizando os dados processados previamente.  
O suporte é uma métrica que indica a frequência com que uma tupla ocorre dentro de uma classe específica nos dados de entrada.  
A confiança, por outro lado, avalia a probabilidade de uma tupla pertencer a uma classe específica, com base nas ocorrências observadas.

### Funções Principais

- **`calculateSupport()`**: Calcula o suporte de uma tupla, que é definido como a proporção de registros dentro de uma classe que contêm a tupla. Isso ajuda a identificar quão comum uma tupla é dentro de uma classe específica.
  
- **`calculateConfidence()`**: Calcula a confiança, que é a proporção de registros que contêm a tupla e pertencem à classe alvo. Essa métrica é essencial para determinar a precisão de uma regra de associação ao prever uma classe específica.

- **`generateCombinations()`**: Gera todas as combinações possíveis de elementos dentro de um conjunto fornecido. Essa função é útil para avaliar o suporte e a confiança em múltiplas configurações de tuplas, aumentando a flexibilidade da análise.

- **`calculateSupportAndConfidence()`**: Realiza o cálculo do suporte e da confiança para uma nova entrada. A função percorre todas as classes e suas combinações possíveis de tuplas, proporcionando uma análise abrangente das associações entre as tuplas e as classes.

### Exemplo de Uso


- Criação de um DataProcessor para processar o arquivo de entrada
DataProcessor dp("caminho/para/arquivo-de-entrada.data");
dp.processFile();

- Recuperação dos mapas de tuplas e classes processados
const auto& tupleMap = dp.getTupleMap();
const auto& classMap = dp.getClassMap();

- Inicialização dos mapas de linhas para tuplas e classes
map<pair<int, int>, vector<int>> tupleLines;
map<int, vector<int>> classLines;

- Preenchimento do mapa de linhas de tuplas a partir do tupleMap
for (const auto& entry : tupleMap) {
    tupleLines[{get<0>(entry.first), get<1>(entry.first)}] = entry.second;
}

- Preenchimento do mapa de linhas de classes a partir do classMap
for (const auto& entry : classMap) {
    classLines[entry.first] = entry.second;
}

- Definição de uma nova instância para a qual o suporte e confiança serão calculados
vector<pair<int, int>> newInstance = {{1, 10}, {1, 11}, {1, 13}, {1, 12}, {1, 1}};

- Cálculo do suporte e confiança para a nova instância
calculateSupportAndConfidence(newInstance, tupleLines, classLines);

# Análise de Complexidade dos Códigos

## 1. similaridade_jaccard.cpp

### Função `process`

- **Leitura e processamento do arquivo**: O(L * C)  
  Onde L é o número de linhas e C é o número de colunas.

- **Conversão de `unordered_map` para `map`**: O(T log T) para `tupleMap` e O(CL log CL) para `classMap`  
  Onde T é o número de tuplas e CL é o número de classes.

- **Cálculo de parâmetros**: O(1)

- **Cálculo de similaridades**: O(T^2 * M)  
  Onde T é o número de tuplas e M é o número médio de linhas por tupla.

- **Escrita das similaridades em arquivo**: O(S)  
  Onde S é o número de similaridades calculadas.

### Função `jaccardSimilarity`

- **Interseção e união de conjuntos**: O(M + N)  
  Onde M e N são os tamanhos dos dois conjuntos.

### Função `calculateSimilarities`

- **Iteração sobre combinações de tuplas**: O(T^2 * M)

### Função `writeSimilaritiesToFile`

- **Escrita em arquivo**: O(S)  
  Onde S é o número de similaridades calculadas.

## 2. leitura_input.cpp

### Função `processFile`

- **Leitura do arquivo**: O(L * C)  
  Onde L é o número de linhas e C é o número de colunas.

- **Processamento de cada linha**: O(L * C)

- **Escrita dos mapas em arquivos**: O(T + CL)  
  Onde T é o número de tuplas e CL é o número de classes.

### Função `processLine`

- **Processamento de cada linha**: O(C)  
  Onde C é o número de colunas.

### Função `writeTupleMapToFile`

- **Escrita em arquivo**: O(T * M)  
  Onde T é o número de tuplas e M é o número médio de linhas por tupla.

### Função `writeClassMapToFile`

- **Escrita em arquivo**: O(CL * L)  
  Onde CL é o número de classes e L é o número médio de linhas por classe.

## 3. calculo_suporte_confianca.cpp

### Função `calculateSupport`

- **Interseção de conjuntos**: O(M + N)  
  Onde M e N são os tamanhos dos dois conjuntos.

### Função `calculateConfidence`

- **Interseção de conjuntos**: O(M + N)

### Função `generateCombinations`

- **Geração de combinações**: O(2^N)  
  Onde N é o número de elementos no vetor `elements`.

### Função `calculateSupportAndConfidence`

- **Iteração sobre classes**: O(CL)  
  Onde CL é o número de classes.

- **Iteração sobre tamanhos de combinação**: O(2^N)  
  Onde N é o tamanho da nova entrada.

- **Iteração sobre combinações**: O(2^N)

- **Interseção de conjuntos**: O(M + N) para cada combinação.

### Função `main`

- **Processamento do arquivo**: O(L * C)

- **Conversão de `unordered_map` para `map`**: O(T log T) para `tupleMap` e O(CL log CL) para `classMap`.

- **Cálculo de suporte e confiança**: O(CL * 2^N * (M + N))

## Resumo das Complexidades

- **similaridade_jaccard.cpp**: O(L * C + T log T + CL log CL + T^2 * M + S)
- **leitura_input.cpp**: O(L * C + T * M + C * L)
- **calculo_suporte_confianca.cpp**: O(L * C + T log T + CL log CL + CL * 2^N * (M + N))
