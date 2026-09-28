#include <iostream>
#include "../include/ProcesadorFuente.h"
#include "../include/Sistema.h"
#include "../include/Compresor.h"

using namespace std;

int main() {
    int N_BITS = 1024;
    string ruta = "data/archivo_prueba.bin";

    // 1. Inicializar componentes
    ProcesadorFuente procesador;
    Sistema miSistema(N_BITS, "Video", "Huffman");
    // Compresor compresor; // (Se implementará luego)

    // 2. Procesar fuente
    cout << "Leyendo archivo..." << endl;
    vector<string> simbolos = procesador.fragmentarArchivo(ruta, N_BITS);
    
    if(simbolos.empty()) {
        cout << "Error al procesar el archivo." << endl;
        return 1;
    }

    // 3. Analizar probabilidades
    unordered_map<string, float> probs = procesador.calcularProbabilidades(simbolos);

    // 4. Calcular métricas matemáticas
    miSistema.calcularMetricas(probs);
    miSistema.mostrarResultados();

    // 5. Aquí iría el proceso de codificación y decodificación
    // string flujo = compresor.codificar(simbolos, "Huffman");
    // vector<string> recuperados = compresor.decodificar(flujo, "Huffman");

    return 0;
}