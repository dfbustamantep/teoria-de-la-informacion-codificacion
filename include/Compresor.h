#ifndef COMPRESOR_H
#define COMPRESOR_H

#include <string>
#include <vector>

class Compresor {
public:
    // Toma los símbolos originales y devuelve un flujo de bits comprimido
    std::string codificar(const std::vector<std::string>& simbolos, const std::string& tipoCodificacion);
    
    // Toma el flujo de bits comprimido y lo reconstruye en símbolos
    std::vector<std::string> decodificar(const std::string& flujoComprimido, const std::string& tipoCodificacion);
};

#endif