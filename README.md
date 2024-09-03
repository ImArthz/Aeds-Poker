# Algoritmo de Classificação Lazy Associative Classification (LAC)

## Descrição do Projeto
Este projeto implementa o algoritmo de classificação Lazy Associative Classification (LAC), conforme especificado na tarefa final do curso de Algoritmos e Estruturas de Dados.

O LAC é uma abordagem preguiçosa para classificação que difere dos métodos tradicionais por construir a base de conhecimento necessária para a classificação somente no momento da predição. Ao invés de realizar um treinamento extensivo antecipadamente, o LAC utiliza tabelas invertidas para associar atributos a classes, permitindo uma classificação mais eficiente e adaptável a novos dados.

### Teste em python

## Código 1: Cálculo de Similaridades de Jaccard

[![Jaccard (Python)](https://img.shields.io/badge/Jaccard%20(Python)-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/python%20test/jaccard%20python.py)

* **load_tuplemap(filename):** Carrega um mapa de tuplas de um arquivo.
* **calculate_jaccard(set1, set2):** Calcula o índice de similaridade de Jaccard.
* **calculate_all_similarities(tuple_map):** Calcula todas as similaridades de Jaccard.
* **write_similarities_to_file(similarities, output_filename):** Escreve as similaridades em um arquivo.
  
[![Output: Jaccard (Python)](https://img.shields.io/badge/Output%20Jaccard-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/python%20test/output_python_test/similaridadePython.txt)

## Código 2: Comparação de Similaridades entre Python e C++
[![Comparação de Similaridade (python)(c++)](https://img.shields.io/badge/Comparacao%20Python%20vs%20c++-Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/python%20test/Similarity%20comparation.py)

* **load_similarities_from_file(filename):** Carrega as similaridades de um arquivo.
* **compare_similarities(similarities_python, similarities_cpp, precision=6):** Compara as similaridades.
* **write_comparison_results(discrepancies, iguais, diferentes, output_file):** Escreve os resultados da comparação.
  
[![output (python vs c++)](https://img.shields.io/badge/output%20python%20vs%20c++-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/python%20test/output_python_test/discrepancias.txt)

## Código 3: Cálculo de Suporte e Confiança

[![Suporte e Confiança (Python)](https://img.shields.io/badge/Suporte%20e%20Confiança%20(Python)-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/python%20test/suport_confidence.py)

* **load_tuple_map(filename):** Carrega o mapa de tuplas.
* **load_class_map(filename):** Carrega o mapa de classes.
* **calculate_support_and_confidence_for_class(args):** Calcula suporte e confiança para uma classe.
* **calculate_support_and_confidence(tuple_map, class_map):** Calcula suporte e confiança para todas as combinações.
* **write_support_and_confidence_to_file(support_confidence, output_filename):** Escreve os resultados.

## Nota Final
O projeto principal está sendo desenvolvido em C++, e estes códigos Python são utilizados para testar as bases de dados e cálculos.
## Explicação do Código dataprocessor.h

[![Header: dataprocessor.h](https://img.shields.io/badge/Dataprocessor-Header-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/dataprocessor.h)

### Descrição Geral
A classe `DataProcessor` é responsável por processar um arquivo de dados contendo registros que são utilizados para a análise e classificação. O arquivo é lido linha por linha, e os dados são armazenados em estruturas apropriadas para processamento posterior.

### Componentes e Funções
* **Construtor `DataProcessor(const string& filename)`:** 
  * Inicializa a classe com o nome do arquivo a ser processado.
  * Armazena o nome do arquivo em uma variável membro `filename`.
* **Função `void processFile()`:**
  * Abre o arquivo de dados.
  * Lê o arquivo linha por linha, separando os valores e armazenando-os em um vetor.
  * Remove o rótulo da classe do vetor.
  * Adiciona os atributos e o rótulo da classe aos mapas `tupleMap` e `classMap`.
* **Função `const map<pair<int, int>, vector<int>>& getTupleMap() const`:** Retorna o mapa `tupleMap` que associa tuplas de atributos a vetores de rótulos de classe.
* **Função `const map<int, vector<int>>& getClassMap() const`:** Retorna o mapa `classMap` que associa rótulos de classe a vetores de atributos.

### Estruturas de Dados
* **`tupleMap`:** Um mapa que associa pares de atributos a vetores de rótulos de classe.
* **`classMap`:** Um mapa que associa rótulos de classe a vetores de atributos.

### Exemplo de Uso
```c++
DataProcessor dp("caminho/para/arquivo-de-entrada.data");
dp.processFile();
const auto& tupleMap = dp.getTupleMap();
const auto& classMap = dp.getClassMap();
```
Esta classe facilita a leitura e o processamento de dados estruturados, preparando-os para análises posteriores, como cálculo de similaridade e suporte/confiabilidade.
## Explicação do Código leitura_input.cpp

[![Leitura Input](https://img.shields.io/badge/Leitura%20Input-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/leitura_input.cpp)

[![Output: classMap](https://img.shields.io/badge/ClassMap-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/output/classMap.txt)

[![Output: tupleMap](https://img.shields.io/badge/tupleMap-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/output/tupleMap.txt)

### Descrição Geral
O código `leitura_input.cpp` é responsável por ler um arquivo de dados e gerar dois arquivos de saída contendo mapeamentos de tuplas e classes, otimizados para análises posteriores.

### Componentes e Funções
* **Estrutura `TupleHash`:**
  * Define uma função de hash personalizada para tuplas de inteiros.
  * Garante um hash único para cada tupla, otimizando a busca em `unordered_map`.
* **Classe `DataProcessor`:**
  * **Construtor:** Inicializa a classe com o nome do arquivo de entrada.
  * **`processFile()`:** Lê o arquivo linha por linha, processa cada linha e escreve os resultados em arquivos de saída.
  * **`getTupleMap()` e `getClassMap()`:** Retornam os mapas `tupleMap` e `classMap`, respectivamente.
  * **`processLine()`:** Processa uma linha individual do arquivo, adicionando informações aos mapas.
  * **`writeTupleMapToFile()` e `writeClassMapToFile()`:** Escrevem os mapas em arquivos de saída.
* **`main()`:** Cria um objeto `DataProcessor` e chama `processFile()`.

### Estruturas de Dados
* **`tupleMap`:** Um `unordered_map` que associa tuplas de inteiros (atributos) a vetores de números de linha.
* **`classMap`:** Um `unordered_map` que associa rótulos de classe a vetores de números de linha.

### Exemplo de Uso
```c++
DataProcessor dp("caminho/para/arquivo-de-entrada.data");
dp.processFile();
const auto& tupleMap = dp.getTupleMap();
const auto& classMap = dp.getClassMap();
```
## Observações

* **Otimização:** O uso de `unordered_map` e da estrutura `TupleHash` otimiza a busca e inserção de dados.
* **Flexibilidade:** A classe `DataProcessor` pode ser adaptada para diferentes formatos de arquivos e tipos de análise.
* **Modularidade:** As funções da classe são bem definidas, facilitando a manutenção e o teste do código.

Este código é fundamental para a preparação dos dados, transformando-os em um formato adequado para análises posteriores, como mineração de dados, aprendizado de máquina e análise estatística.

## Sugestões para Melhorias

* **Tratamento de erros:** Implementar um tratamento de erros mais robusto, como verificação de tipos de dados e validação de entradas.
* **Configuração:** Permitir a configuração de parâmetros como o delimitador de campos e o nome dos arquivos de saída.
* **Documentação:** Adicionar comentários mais detalhados para explicar o propósito de cada função e variável.
* **Testes unitários:** Escrever testes unitários para garantir a corretude do código.

Com essas melhorias, o código `leitura_input.cpp` se tornará ainda mais robusto e reutilizável.
## Explicação do Código similaridade_jaccar.cpp

[![Similaridade Jaccard](https://img.shields.io/badge/Similaridade%20Jaccard-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/similaridade_jaccard.cpp)

[![Output: similaridade_cpp](https://img.shields.io/badge/output%20Jaccard-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/output/similaridade_cpp.txt)

### Descrição Geral
O código `similaridade_jaccar.cpp` calcula a similaridade de Jaccard entre conjuntos de valores associados a tuplas, lidos de um arquivo, e salva os resultados em um arquivo de saída.

### Componentes e Funções
* **`loadTupleMap`:** Carrega o mapa de tuplas a partir de um arquivo, armazenando tuplas e seus conjuntos de valores associados.
* **`calculateJaccard`:** Calcula a similaridade de Jaccard entre dois conjuntos.
* **`calculateAllSimilarities`:** Calcula todas as similaridades de Jaccard entre as tuplas no mapa.
* **`writeSimilaritiesToFile`:** Escreve as similaridades calculadas em um arquivo de saída.
* **`main`:** Função principal que coordena o processo de carregamento, cálculo e escrita.

### Estruturas de Dados
* **`tupleMap`:** Armazena tuplas e seus conjuntos de valores.
* **`similarities`:** Armazena pares de tuplas e suas similaridades de Jaccard.

### Exemplo de Uso
```bash
g++ similaridade_jaccar.cpp -o similaridade_jaccar
./similaridade_jaccar
```
### Entrada e Saída
* **Entrada:** Arquivo `tupleMap.txt` contendo tuplas e seus valores associados.
* **Saída:** Arquivo `similaridade_cpp.txt` contendo as similaridades de Jaccard para cada par de tuplas.

### Observações
* **Similaridade de Jaccard:** É uma medida de similaridade entre conjuntos, calculada como a razão entre a interseção e a união dos conjuntos.
* **Aplicações:**
  * **Análise de dados:** Identificar padrões e relacionamentos em conjuntos de dados.
  * **Aprendizado de máquina:** Utilizada em técnicas de clustering e classificação.

Este código fornece uma ferramenta útil para comparar a similaridade entre diferentes conjuntos de dados representados por tuplas.

### Sugestões para Melhorias
* **Paralelização:** Explorar a paralelização do cálculo das similaridades para melhorar o desempenho em grandes conjuntos de dados.
* **Otimizações:** Analisar e otimizar o algoritmo de cálculo da similaridade de Jaccard para conjuntos grandes.
* **Flexibilidade:** Permitir a configuração de diferentes medidas de similaridade além da de Jaccard (e.g., coeficiente de Dice, distância de cosine).

Com estas melhorias, o código pode ser aplicado a uma variedade de problemas e escalar para conjuntos de dados ainda maiores.

## Explicação do Código calculo_suporte_confianca.cpp

[![Suporte e Confiança](https://img.shields.io/badge/Suporte%20e%20Confiança-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/calculo_suporte_confianca.cpp)

[![Output: Support and Confidence (C++)](https://img.shields.io/badge/Output%20Suporte%20e%20Confianca-Output-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/output/support_confidence_cpp.txt)


## Descrição Geral

O código `calculo_suporte_confianca.cpp` calcula o suporte e a confiança para uma nova entrada de dados, utilizando informações de tuplas e classes previamente carregadas. Os resultados são salvos em um arquivo de saída. Este código é projetado para ser executado em ambientes Linux e utiliza paralelismo para melhorar o desempenho.

### Componentes e Funções

* **calculateSupport:** Calcula o suporte com base na interseção entre conjuntos de linhas. O suporte é a proporção de linhas que contêm o conjunto de itens em relação ao total de linhas da classe.
* **calculateConfidence:** Calcula a confiança, que é a proporção de linhas que contêm tanto o conjunto de itens quanto a classe em relação ao total de linhas que contêm o conjunto de itens.
* **generateCombinations:** Gera todas as combinações possíveis de um determinado tamanho a partir de um vetor de elementos. Utiliza uma abordagem de combinação baseada em permutações.
* **calculateSupportAndConfidence:** Calcula o suporte e a confiança para todas as combinações possíveis de tuplas em uma nova entrada e salva os resultados em um arquivo de saída.
* **main:** Função principal que coordena o processo de cálculo e escrita. Ela processa os arquivos de entrada, cria diretórios se necessário, divide o trabalho entre várias threads para calcular suporte e confiança, e grava os resultados em um arquivo.

### Estruturas de Dados

* **tupleLines:** Mapeia tuplas para os números de linhas correspondentes.
* **classLines:** Mapeia rótulos de classe para os números de linhas correspondentes.

### Exemplo de Uso

```bash
g++ calculo_suporte_confianca.cpp -o calculo_suporte_confianca -lpthread
./calculo_suporte_confianca
```
## Entrada e Saída

* **Entrada:**
    * `poker-hand-training.data` e `poker-hand-testing.data` (caminhos podem variar) - Contêm dados de tuplas e classes.
* **Saída:**
    * `support_confidence_cpp.txt` - Contém os resultados de suporte e confiança.

### Observações

* **Suporte e Confiança:** São medidas utilizadas em mineração de dados para avaliar a frequência e a força de associações entre itens.
* **Aplicações:**
    * **Análise de dados de transações:** Identificar padrões de compra, como "clientes que compram pão também compram leite".
    * **Análise de dados de poker:** Analisar a relação entre diferentes mãos de poker e suas probabilidades de vitória.

Este código é útil para a análise de dados e a descoberta de regras de associação em diversos contextos.

### Sugestões para Melhorias

* **Otimizações:**
    * Explorar algoritmos mais eficientes para gerar combinações e calcular suporte e confiança, especialmente para grandes conjuntos de dados.
    * Considerar o uso de estruturas de dados mais adequadas para os cálculos.
* **Flexibilidade:**
    * Permitir a configuração de diferentes medidas de suporte e confiança (e.g., lift, confiança condicional).
    * Adaptar o código para trabalhar com diferentes formatos de entrada.
* **Visualização:**
    * Implementar uma interface para visualizar os resultados de forma gráfica (e.g., utilizando bibliotecas como Matplotlib ou Plotly).

Com estas melhorias, o código pode ser aplicado a uma variedade de problemas de mineração de dados e se tornar uma ferramenta mais poderosa e versátil.
### Função `main`

[![main](https://img.shields.io/badge/main-View%20Code-blue)](https://github.com/ImArthz/Aeds-Poker/blob/main/c%2B%2B%20test/main.cpp)

A função `main` é o ponto de entrada do programa.

1. **Inicialização:**
    * Exibe uma mensagem indicando o início da execução dos programas.
2. **Execução de programas:**
    * Utiliza a função `runProgram` para executar sequencialmente três programas externos: "leitura_input", "similaridade_jaccard" e "calculo_suporte_confianca".
3. **Finalização:**
    * Exibe uma mensagem indicando que todos os programas foram executados com sucesso.

**Melhorias:**
* A função `runProgram` poderia ser aprimorada para receber o caminho completo do programa externo como argumento, tornando-a mais flexível.
* O código poderia ser refatorado para evitar a duplicação das chamadas a `runProgram`.
## Conclusão Final: Trabalho de Algoritmo de Classificação
Michel Pires, Centro Federal de Educação Tecnológica de Minas Gerais

Data: 16 de Julho de 2024

### 1. Resumo do Trabalho
Neste trabalho, desenvolvemos e avaliamos um algoritmo de classificação baseado no Lazy Associative Classification (LAC). O LAC utiliza uma abordagem "preguiçosa" para a classificação, gerando a base de dados necessária para as previsões apenas durante o processo de classificação. Utilizamos listas, pilhas, filas e tabelas hash para implementar este algoritmo, com o objetivo de classificar novas entradas com base em dados de treinamento fornecidos.

### 2. Implementação e Resultados
![Output Suporte e Confiança](https://img.shields.io/badge/output%20Suporte%20e%20Confiança-Output-blue)]

O algoritmo foi implementado em C++ e validado em um ambiente Linux. A análise dos resultados gerados revelou:


A análise dos resultados de suporte e confiança obtidos mostra variações significativas entre as diferentes linhas e classes de dados. De maneira geral, os valores de suporte e confiança são bastante variados, indicando que a presença de certas características pode influenciar de maneira diferente o suporte e a confiança dependendo da linha e da classe.

Observa-se que a confiança tende a ser um pouco mais alta para a classe 1 em comparação com a classe 0 em várias linhas, o que pode sugerir uma tendência geral de que as características associadas à classe 1 são mais fortemente associadas às classes de interesse no conjunto de dados.

Além disso, o suporte também apresenta variações, com algumas linhas mostrando um suporte relativamente alto para a classe 0, o que pode indicar que essas características específicas ocorrem com maior frequência nesse contexto.

Esses resultados são úteis para entender as relações e padrões nos dados, e podem fornecer insights para futuras análises e decisões relacionadas ao problema em questão. No entanto, uma análise mais detalhada e a consideração de mais linhas de dados podem ser necessárias para obter conclusões mais robustas e para validar essas observações preliminares.

### 3. Considerações sobre a Documentação e Entrega
O trabalho foi documentado de acordo com os requisitos estabelecidos, incluindo:
* Descrição detalhada das fases do projeto.
* Análise de complexidade dos algoritmos.
* Instruções de execução no arquivo README.md.
### 4. Resumo das Complexidades

- **similaridade_jaccard.cpp**: O(L * C + T log T + CL log CL + T^2 * M + S)
- **leitura_input.cpp**: O(L * C + T * M + C * L)
- **calculo_suporte_confianca.cpp**: O(L * C + T log T + CL log CL + CL * 2^N * (M + N))
### 5. Conclusão
O algoritmo LAC mostrou-se eficiente para classificação com base em regras de associação. Apesar de algumas limitações, o trabalho cumpriu os objetivos estabelecidos.

### 6. Contribuidores

Feito Por : 

[![Arthur Mendonça](https://img.shields.io/badge/Arthur%20Mendonça-GitHub-black?style=flat&logo=github)](https://github.com/ImArthz)

[![Thiago](https://img.shields.io/badge/Thiago-GitHub-black?style=flat&logo=github)](https://github.com/Thiago-Mi)

[![Arthur Santana](https://img.shields.io/badge/Arthur%20Santana-GitHub-black?style=flat&logo=github)](https://github.com/Rutrama)
