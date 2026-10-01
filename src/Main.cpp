#include <iostream>
#include <fstream> 
#include "../include/ProcesadorFuente.h"
#include "../include/Sistema.h"
#include "../include/Compresor.h"

using namespace std;

int main() {
    int N_BITS = 8;
    string ruta = "data/prueba.txt";

    // 1. Inicializar componentes
    ProcesadorFuente procesador;
    // Ajustado a LZW para mantener coherencia con el resto del código
    Sistema miSistema(N_BITS, "Video", "LZW"); 

    // 2. Procesar fuente
    cout << "Leyendo archivo..." << endl;
    vector<string> simbolos = procesador.fragmentarArchivo(ruta, N_BITS);
    
    if(simbolos.empty()) {
        cout << "Error al procesar el archivo. Verifica que exista en data/prueba.txt" << endl;
        return 1;
    }

    // 3. Analizar probabilidades
    unordered_map<string, float> probs = procesador.calcularProbabilidades(simbolos);

    // 4. Calcular métricas matemáticas
    miSistema.calcularMetricas(probs);
    miSistema.mostrarResultados();

    // 5. Proceso de Codificación (Compresión)
    Compresor compresor;
    cout << "\nIniciando compresion..." << endl;
    string flujoComprimido = compresor.codificar(simbolos, "LZW");
    
    // --> GENERAR ARCHIVO COMPRIMIDO EN DISCO <--
    ofstream archivoSalida("data/comprimido.bin", ios::binary);
    if (archivoSalida.is_open()) {
        archivoSalida.write(flujoComprimido.data(), flujoComprimido.size());
        archivoSalida.close();
        cout << "Archivo comprimido guardado en: data/comprimido.bin" << endl;
    }

    // 6. Proceso de Decodificación (Reconstrucción)
    cout << "\nIniciando reconstruccion..." << endl;
    vector<string> recuperados = compresor.decodificar(flujoComprimido, "LZW");
    
    // --> GENERAR ARCHIVO RECONSTRUIDO EN DISCO <--
    ofstream archivoReconstruido("data/reconstruido.bin", ios::binary);
    if (archivoReconstruido.is_open()) {
        for (const string& sim : recuperados) {
            archivoReconstruido.write(sim.data(), sim.size());
        }
        archivoReconstruido.close();
        cout << "Archivo reconstruido guardado en: data/reconstruido.bin" << endl;
    } 
// Mostrar tamaños de los archivos
    archivoSalida.seekp(0, ios::end); // Va al final del archivo comprimido
    int tamanoComprimido = flujoComprimido.size(); 
    
    // Calcular tamaño original abriendo el archivo de prueba
    ifstream archivoOriginal(ruta, ios::binary | ios::ate);
    int tamanoOriginal = archivoOriginal.tellg();
    archivoOriginal.close();

    cout << "\n--- RESUMEN DE COMPRESION ---" << endl;
    cout << "Tamano Original:   " << tamanoOriginal << " bytes" << endl;
    cout << "Tamano Comprimido: " << tamanoComprimido << " bytes" << endl;
    return 0;
}