#include "../include/Sistema.h"
#include <iostream>
#include <cmath>

using namespace std;

Sistema::Sistema(int bits, string tipoFuente, string codificacion) {
    this->bits = bits;
    this->tipoFuente = tipoFuente;
    this->codificacion = codificacion;
    this->cantidadInformacion = 0.0;
    this->entropia = 0.0;
    this->informacionMutua = 0.0;
    this->divergenciaKL = 0.0;
}

void Sistema::calcularMetricas(const unordered_map<string, float>& probabilidades) {
    entropia = 0.0;
    float probUniforme = 1.0 / probabilidades.size(); 
    divergenciaKL = 0.0;

    for (auto const& par : probabilidades) {
        float p = par.second;
        if (p > 0) {
            entropia -= p * log2(p);
            divergenciaKL += p * log2(p / probUniforme);
        }
    }
    informacionMutua = entropia; // Asumiendo compresión sin pérdida
}

void Sistema::mostrarResultados() {
    cout << "--- Resultados del Sistema ---\n";
    cout << "Fuente: " << tipoFuente << " | N Bits: " << bits << " | Codificacion: " << codificacion << "\n";
    cout << "Entropia (H): " << entropia << " bits/simbolo\n";
    cout << "Divergencia KL: " << divergenciaKL << "\n";
}