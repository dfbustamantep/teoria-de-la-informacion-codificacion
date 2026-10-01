#include <iostream>
#include <fstream>
#include <string>
#include "../include/ProcesadorFuente.h"
#include "../include/Sistema.h"
#include "../include/Compresor.h"

using namespace std;

int main(int argc, char* argv[]) {
    // 1. Recibir datos desde Streamlit o usar valores por defecto
    int N_BITS = 1024;
    string ruta = "data/prueba.txt";

    if (argc >= 3) {
        ruta = argv[1];          // Lee la ruta que manda Streamlit
        N_BITS = stoi(argv[2]);  // Lee el tamaño de bits que manda Streamlit
    }

    // 2. Inicializar componentes
    ProcesadorFuente procesador;
    Sistema miSistema(N_BITS, "Archivo", "LZW"); 

    // 3. Procesar fuente
    cout << "Analizando archivo: " << ruta << " (Bloques de " << N_BITS << " bits)" << endl;
    vector<string> simbolos = procesador.fragmentarArchivo(ruta, N_BITS);
    
    if(simbolos.empty()) {
        cout << "Error al procesar el archivo. Verifica la ruta." << endl;
        return 1;
    }

    // 4. Analizar probabilidades y Métricas
    unordered_map<string, float> probs = procesador.calcularProbabilidades(simbolos);
    miSistema.calcularMetricas(probs);
    miSistema.mostrarResultados();

    // 5. Proceso de Codificación (Compresión)
    Compresor compresor;
    string flujoComprimido = compresor.codificar(simbolos, "LZW");
    
    ofstream archivoSalida("data/comprimido.bin", ios::binary);
    if (archivoSalida.is_open()) {
        archivoSalida.write(flujoComprimido.data(), flujoComprimido.size());
        archivoSalida.close();
    }

    // 6. Proceso de Decodificación (Reconstrucción)
    vector<string> recuperados = compresor.decodificar(flujoComprimido, "LZW");
    
    ofstream archivoReconstruido("data/reconstruido.bin", ios::binary);
    if (archivoReconstruido.is_open()) {
        for (const string& sim : recuperados) {
            archivoReconstruido.write(sim.data(), sim.size());
        }
        archivoReconstruido.close();
    }

    // 7. Mostrar Resumen de Tamaños para Streamlit
    ifstream archivoOriginal(ruta, ios::binary | ios::ate);
    int tamanoOriginal = archivoOriginal.tellg();
    archivoOriginal.close();

    cout << "\n===================================" << endl;
    cout << "      RESUMEN DE COMPRESION" << endl;
    cout << "===================================" << endl;
    cout << "Tamano Original:   " << tamanoOriginal << " bytes" << endl;
    cout << "Tamano Comprimido: " << flujoComprimido.size() << " bytes" << endl;
    
    return 0;
}