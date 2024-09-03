def load_tuplemap(filename):
    tuple_map = {}
    
    try:
        with open(filename, 'r') as file:
            for line in file:
                key, values = line.strip().split(':')
                key = tuple(map(int, key.strip('()').split(',')))
                # Removendo vírgulas antes de converter para inteiros
                values = set(map(int, values.replace(',', '').split()))
                tuple_map[key] = values
    except FileNotFoundError:
        raise FileNotFoundError(f"Erro: Não foi possível abrir o arquivo '{filename}'. Verifique o caminho e tente novamente.")
    except Exception as e:
        raise Exception(f"Erro inesperado: {e}")
    
    return tuple_map

def calculate_jaccard(set1, set2):
    intersection = len(set1.intersection(set2))
    union = len(set1.union(set2))
    return intersection / union

def calculate_all_similarities(tuple_map):
    similarities = {}
    keys = list(tuple_map.keys())
    
    for i in range(len(keys)):
        for j in range(i + 1, len(keys)):
            key1 = keys[i]
            key2 = keys[j]
            similarity = calculate_jaccard(tuple_map[key1], tuple_map[key2])
            similarities[(key1, key2)] = similarity
            
    return similarities

def write_similarities_to_file(similarities, output_filename):
    similarity_aux = 0
    try:
        with open(output_filename, 'w') as file:
            for pair, similarity in similarities.items():
                file.write(f"Similaridade {pair} = {similarity}\n")
                similarity_aux = 1  # Indicador de que a escrita foi bem-sucedida
    except Exception as e:
        raise Exception(f"Erro ao escrever no arquivo '{output_filename}': {e}")
    return similarity_aux

# Exemplo de uso com path:
print(f"------------- Jaccard Similarity -------------")
print(f"Calculando similaridades...")

filename = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/tupleMap.txt'  # Substitua pelo caminho correto do arquivo
output_filename = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/python test/output_python_test/similaridadePython.txt'  # Substitua pelo caminho desejado para a saída

# Carrega o mapa de tuplas
tuple_map = load_tuplemap(filename)

# Calcula as similaridades
similarities = calculate_all_similarities(tuple_map)

# Escreve as similaridades no arquivo e verifica o status de sucesso
success = write_similarities_to_file(similarities, output_filename)

if success == 1:
    print(f"Similaridades calculadas com sucesso no arquivo {output_filename}")
else:
    print(f"Erro ao calcular similaridades")
