#ifndef SISTEMA_H
#define SISTEMA_H

#include <string>
#include <unordered_map>

class Sistema {
private:
    int bits;
    std::string tipoFuente;
    std::string codificacion;
    
    float cantidadInformacion;
    float entropia;
    float informacionMutua;
    float divergenciaKL;

public:
    Sistema(int bits, std::string tipoFuente, std::string codificacion);
    
    void calcularMetricas(const std::unordered_map<std::string, float>& probabilidades);
    void mostrarResultados();
};

#endif