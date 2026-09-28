# Sistema Adaptable de Codificación y Compresión 5G/6G

Este repositorio contiene un sistema desarrollado en C++ diseñado para fragmentar, analizar estadísticamente, comprimir y reconstruir grandes volúmenes de datos (audio, video, texto, imagen). El proyecto está orientado a simular las necesidades de procesamiento masivo en redes de telecomunicaciones modernas (5G y 6G), soportando un tamaño de símbolo adaptable desde 8 hasta 32768 bits.

## Arquitectura del Proyecto

El código fuente está estructurado siguiendo las mejores prácticas de C++, separando las definiciones de las implementaciones:

*   **`include/`**: Contiene los archivos de cabecera (`.h`) con las definiciones y contratos de las clases.
*   **`src/`**: Aloja los archivos de código fuente (`.cpp`) donde reside la lógica algorítmica y matemática.
*   **`data/`**: Directorio destinado a almacenar los archivos multimedia binarios que serán procesados por el sistema (ignorado en el control de versiones por tamaño).

## Módulos Principales

El flujo de procesamiento se divide en tres componentes clave basados en la Teoría de la Información de Shannon:

1.  **ProcesadorFuente**: 
    Se encarga de la lectura estricta en modo binario de cualquier archivo. Su función principal es dividir el flujo de datos continuo en bloques exactos de $N$ bits. Adicionalmente, escanea los bloques resultantes para construir un modelo estadístico, calculando la probabilidad de aparición de cada símbolo.

2.  **Compresor**: 
    Implementa los algoritmos de eliminación de redundancia. 
    *   *Codificación Uniforme:* Asigna longitudes fijas sirviendo como línea base de medición.
    *   *Codificación Adaptable (LZW):* Utiliza el algoritmo Lempel-Ziv-Welch para construir un diccionario dinámico al vuelo, permitiendo compresión sin pérdida altamente eficiente para símbolos de longitud masiva (ej. 4096 a 32768 bits), donde los enfoques tradicionales como Huffman no son viables.

3.  **Sistema (Orquestador)**: 
    Clase principal que integra los módulos y calcula matemáticamente las métricas de rendimiento del proceso:
    *   **Cantidad de Información ($I$)**: Sorpresa asociada a cada símbolo.
    *   **Entropía ($H$)**: Límite teórico máximo de compresión de la fuente.
    *   **Información Mutua**: Medición de la información compartida entre la fuente y la reconstrucción.
    *   **Divergencia Kullback-Leibler ($D_{KL}$)**: Diferencia entre la distribución real de la fuente y una distribución uniforme ideal.

## Compilación y Ejecución

Para compilar el proyecto de forma manual utilizando el compilador GCC (`g++`), abre una terminal en el directorio raíz del repositorio y ejecuta:

```bash
g++ src/Main.cpp src/Compresor.cpp src/ProcesadorFuente.cpp src/Sistema.cpp -o codificador_6g.exe
