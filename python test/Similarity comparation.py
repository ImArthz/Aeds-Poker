import ast

def load_similarities_from_file(filename):
    similarities = {}
    try:
        with open(filename, 'r') as file:
            for line in file:
                parts = line.split(' = ')
                if len(parts) == 2:
                    pair_str = parts[0].replace('Similaridade', '').strip()
                    similarity = float(parts[1].strip())
                    try:
                        pair_str = pair_str.replace('(', '').replace(')', '').replace(' ', '')
                        pair_elements = pair_str.split(',')
                        pair = ((int(pair_elements[0]), int(pair_elements[1])), (int(pair_elements[2]), int(pair_elements[3])))
                        similarities[pair] = similarity
                    except (ValueError, SyntaxError) as e:
                        print(f"Erro ao avaliar pair_str: {pair_str} - {e}")
    except FileNotFoundError:
        raise FileNotFoundError(f"Erro: Não foi possível abrir o arquivo '{filename}'. Verifique o caminho e tente novamente.")
    except Exception as e:
        raise Exception(f"Erro inesperado ao carregar similaridades: {e}")
    
    return similarities

def compare_similarities(similarities_python, similarities_cpp, precision=6):
    discrepancies = []
    iguais = 0
    diferentes = 0
    
    for pair in similarities_python:
        if pair in similarities_cpp:
            sim_python = round(similarities_python[pair], precision)
            sim_cpp = round(similarities_cpp[pair], precision)
            if sim_python != sim_cpp:
                discrepancies.append((pair, sim_python, sim_cpp))
                diferentes += 1
            else:
                iguais += 1
        else:
            discrepancies.append((pair, similarities_python[pair], None))
            diferentes += 1
    
    for pair in similarities_cpp:
        if pair not in similarities_python:
            discrepancies.append((pair, None, similarities_cpp[pair]))
            diferentes += 1
    
    return discrepancies, iguais, diferentes

def write_comparison_results(discrepancies, iguais, diferentes, output_file):
    with open(output_file, 'w') as file:
        if not discrepancies:
            file.write("Nenhuma discrepância encontrada. As similaridades coincidem!\n")
        else:
            file.write("Discrepâncias encontradas:\n")
            for pair, sim_python, sim_cpp in discrepancies:
                file.write(f"Par {pair}: Python = {sim_python}, C++ = {sim_cpp}\n")
        file.write(f"\nNúmero de pares iguais: {iguais}\n")
        file.write(f"Número de pares diferentes: {diferentes}\n")

# Caminhos dos arquivos
python_similarities_file = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/python test/output_python_test/similaridadePython.txt'
cpp_similarities_file = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/similaridade_cpp.txt'
output_file = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/python test/output_python_test/discrepancias.txt'

# Carregando similaridades dos arquivos
similarities_python = load_similarities_from_file(python_similarities_file)
similarities_cpp = load_similarities_from_file(cpp_similarities_file)

# Comparando as similaridades
discrepancies, iguais, diferentes = compare_similarities(similarities_python, similarities_cpp)

# Escrevendo os resultados da comparação em um arquivo
write_comparison_results(discrepancies, iguais, diferentes, output_file)

print(f"Comparação concluída. Resultados escritos em '{output_file}'.")
