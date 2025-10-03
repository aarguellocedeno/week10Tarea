#Ana Gabriela Argüello y Laura Isabel Olivero

import pandas as pd
import sys

def main():
    if len(sys.argv) < 2:
        sys.exit(1)
    archivo = sys.argv[1]

    # Leer el archivo CSV
    df = pd.read_csv(archivo, delimiter=';', header=None)
    df.columns = [f'Columna{i+1}' for i in range(df.shape[1])]

    # Eliminar la última columna vacía si existe
    df = df.dropna(axis=1, how='all')


    for col in df.columns:
        df[col] = pd.to_numeric(df[col], errors='coerce')

    # Calcular el promedio y la mediana
    promedios = df.mean(numeric_only=True)
    mediana = df.median(numeric_only=True)

    # Mostrar resultados
    print("Promedio por columna:")
    print(promedios)

    print("\nMediana por columna:")
    print(mediana)