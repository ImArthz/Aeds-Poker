import itertools
from collections import defaultdict
import os
from multiprocessing import Pool, cpu_count

def load_tuple_map(filename):
    """Carrega o mapa de tuplas a partir de um arquivo."""
    tuple_map = {}
    try:
        filename = filename.replace('\\', '/')
        with open(filename, 'r') as file:
            for line in file:
                key, values = line.strip().split(':')
                key = tuple(map(int, key.strip('()').split(',')))
                values = set(map(int, values.replace(',', '').split()))
                tuple_map[key] = values
    except FileNotFoundError:
        raise FileNotFoundError(f"Erro: Não foi possível abrir o arquivo '{filename}'. Verifique o caminho e tente novamente.")
    except Exception as e:
        raise Exception(f"Erro inesperado: {e}")
    
    return tuple_map

def load_class_map(filename):
    """Carrega o mapa de classes a partir de um arquivo."""
    class_map = {}
    try:
        filename = filename.replace('\\', '/')
        with open(filename, 'r') as file:
            for line in file:
                class_label, values = line.strip().split(':')
                class_label = int(class_label.strip())
                values = set(map(int, values.replace(',', '').split()))
                class_map[class_label] = values
    except FileNotFoundError:
        raise FileNotFoundError(f"Erro: Não foi possível abrir o arquivo '{filename}'. Verifique o caminho e tente novamente.")
    except Exception as e:
        raise Exception(f"Erro inesperado: {e}")
    
    return class_map

def calculate_support_and_confidence_for_class(args):
    """Calcula suporte e confiança para uma classe específica."""
    class_label, class_lines, tuple_map = args
    support_confidence = defaultdict(lambda: [0, 0])
    keys = list(tuple_map.keys())
    
    for size in range(1, len(keys) + 1):
        for combination in itertools.combinations(keys, size):
            combined_lines = set.intersection(*(tuple_map[key] for key in combination))
            
            if combined_lines:
                intersection_class_lines = combined_lines.intersection(class_lines)
                support = len(intersection_class_lines) / len(class_lines) if class_lines else 0
                confidence = len(intersection_class_lines) / len(combined_lines) if combined_lines else 0

                support_confidence[size][0] += support
                support_confidence[size][1] += confidence

    # Média dos suportes e confianças
    total_combinations = len(list(itertools.combinations(keys, size)))
    for size in support_confidence:
        avg_support = support_confidence[size][0] / total_combinations
        avg_confidence = support_confidence[size][1] / total_combinations
        support_confidence[size] = (avg_support, avg_confidence)

    return class_label, dict(support_confidence)

def calculate_support_and_confidence(tuple_map, class_map):
    """Calcula suporte e confiança para todas as combinações de tuplas e classes usando multiprocessing."""
    args = [(class_label, class_lines, tuple_map) for class_label, class_lines in class_map.items()]

    with Pool(processes=cpu_count()) as pool:
        results = pool.map(calculate_support_and_confidence_for_class, args)

    # Junta os resultados
    return dict(results)

def write_support_and_confidence_to_file(support_confidence, output_filename):
    """Grava o suporte e a confiança calculados em um arquivo."""
    try:
        output_filename = output_filename.replace('\\', '/')
        with open(output_filename, 'w') as file:
            for class_label, supports_confidences in support_confidence.items():
                for size, (avg_support, avg_confidence) in supports_confidences.items():
                    file.write(f"Classe: {class_label}, Tamanho Combinação: {size}, Suporte: {avg_support}, Confiança: {avg_confidence}\n")
    except Exception as e:
        raise Exception(f"Erro ao escrever no arquivo '{output_filename}': {e}")

if __name__ == '__main__':
    print(f"------------- Suporte e Confiança -------------")
    print(f"Calculando suporte e confiança...")

    tuple_map_filename = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/tupleMap.txt'
    class_map_filename = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/c++ test/output/classMap.txt'
    output_filename = 'C:/Users/Usuario/Desktop/Aeds-Poker-suporte_confianca/output_python_test/support_confidence_python.txt'
    # Verifica se os arquivos existem antes de carregar
    for filename in [tuple_map_filename, class_map_filename]:
        if not os.path.isfile(filename):
            raise FileNotFoundError(f"Arquivo não encontrado: {filename}")

    # Carrega os mapas de tuplas e classes
    tuple_map = load_tuple_map(tuple_map_filename)
    class_map = load_class_map(class_map_filename)

    # Calcula o suporte e a confiança
    support_confidence = calculate_support_and_confidence(tuple_map, class_map)

    # Escreve o suporte e a confiança no arquivo
    write_support_and_confidence_to_file(support_confidence, output_filename)

    print(f"Suporte e confiança calculados com sucesso no arquivo {output_filename}")
