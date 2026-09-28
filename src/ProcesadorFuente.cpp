#include "../include/ProcesadorFuente.h"
#include <fstream>
#include <iostream>

using namespace std;

vector<string> ProcesadorFuente::fragmentarArchivo(const string& rutaArchivo, int nBits) {
    vector<string> fragmentos;
    int nBytes = nBits / 8; 
    
    if (nBytes == 0) return fragmentos;

    ifstream archivo(rutaArchivo, ios::binary);
    if (!archivo.is_open()) return fragmentos;

    vector<char> buffer(nBytes);
    while (archivo.read(buffer.data(), nBytes)) {
        fragmentos.push_back(string(buffer.data(), nBytes));
    }

    if (archivo.gcount() > 0) {
        int bytesLeidos = archivo.gcount();
        string ultimoBloque(buffer.data(), bytesLeidos);
        ultimoBloque.append(nBytes - bytesLeidos, '\0'); 
        fragmentos.push_back(ultimoBloque);
    }

    archivo.close();
    return fragmentos;
}

unordered_map<string, float> ProcesadorFuente::calcularProbabilidades(const vector<string>& simbolos) {
    unordered_map<string, float> probabilidades;
    int totalSimbolos = simbolos.size();
    
    // Contar frecuencias
    unordered_map<string, int> frecuencias;
    for (const string& sim : simbolos) {
        frecuencias[sim]++;
    }
    
    // Calcular P(x)
    for (const auto& par : frecuencias) {
        probabilidades[par.first] = (float)par.second / totalSimbolos;
    }
    
    return probabilidades;
}