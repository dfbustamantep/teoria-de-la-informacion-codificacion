#ifndef PROCESADOR_FUENTE_H
#define PROCESADOR_FUENTE_H

#include <string>
#include <vector>
#include <unordered_map>

class ProcesadorFuente {
public:
    // Fragmenta el archivo en bloques de N bits
    std::vector<std::string> fragmentarArchivo(const std::string& rutaArchivo, int nBits);
    
    // Calcula la probabilidad P(x) de cada símbolo
    std::unordered_map<std::string, float> calcularProbabilidades(const std::vector<std::string>& simbolos);
};

#endif