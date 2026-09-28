#include "../include/Compresor.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// --- CODIFICACIÓN ---
string Compresor::codificar(const vector<string>& simbolos, const string& tipoCodificacion) {
    if (simbolos.empty()) return "";

    if (tipoCodificacion == "Uniforme") {
        // En codificación uniforme, no hay compresión real.
        // Simplemente concatenamos los símbolos originales.
        cout << "[Compresor] Aplicando codificacion Uniforme..." << endl;
        string flujo = "";
        for (const string& sim : simbolos) {
            flujo += sim;
        }
        return flujo;
    } 
    else if (tipoCodificacion == "LZW") {
        cout << "[Compresor] Aplicando compresion LZW adaptable..." << endl;
        
        unordered_map<string, int> diccionario;
        vector<int> salidaComprimida;
        int codigoActual = 256; // Empezamos después de los 256 valores ASCII básicos

        // 1. Inicializar el diccionario con los símbolos únicos base
        // Para N bits, idealmente inicializamos con los bloques únicos básicos.
        // Por simplicidad, agregaremos los símbolos sobre la marcha.
        
        string p = simbolos[0];
        
        // 2. Bucle principal de LZW
        for (size_t i = 1; i < simbolos.size(); i++) {
            string c = simbolos[i];
            string pc = p + c;

            if (diccionario.find(pc) != diccionario.end()) {
                // Si la secuencia ya existe en el diccionario, la concatenamos
                p = pc;
            } else {
                // Si no existe, guardamos el código de 'p' en la salida
                // (Aquí simulamos guardar el código int, en la realidad se serializa a binario)
                if (p.length() == 1) salidaComprimida.push_back((unsigned char)p[0]);
                else salidaComprimida.push_back(diccionario[p]);

                // Agregamos la nueva secuencia 'pc' al diccionario
                diccionario[pc] = codigoActual++;
                p = c;
            }
        }
        
        // Guardar el último patrón
        if (p.length() == 1) salidaComprimida.push_back((unsigned char)p[0]);
        else salidaComprimida.push_back(diccionario[p]);

        // 3. Serializar el vector de enteros a un string binario para simular el archivo comprimido
        string flujoComprimido = "";
        for (int codigo : salidaComprimida) {
            flujoComprimido.append((char*)&codigo, sizeof(int));
        }
        
        cout << "[Compresor] Simbolos comprimidos: " << salidaComprimida.size() << " codigos generados." << endl;
        return flujoComprimido;
    }

    return "";
}

// --- DECODIFICACIÓN ---
vector<string> Compresor::decodificar(const string& flujoComprimido, const string& tipoCodificacion) {
    vector<string> simbolosReconstruidos;

    if (tipoCodificacion == "Uniforme") {
        cout << "[Decodificador] Decodificando Uniforme..." << endl;
        // Aquí dividiríamos el string nuevamente en bloques de N bits.
        // Se requiere pasar N como parámetro en una versión final.
    } 
    else if (tipoCodificacion == "LZW") {
        cout << "[Decodificador] Reconstruyendo mediante LZW..." << endl;
        
        // 1. Deserializar el string binario de vuelta a un vector de enteros
        vector<int> codigos;
        for (size_t i = 0; i < flujoComprimido.length(); i += sizeof(int)) {
            int codigo = *(int*)(flujoComprimido.data() + i);
            codigos.push_back(codigo);
        }

        if (codigos.empty()) return simbolosReconstruidos;

        // 2. Inicializar el diccionario inverso
        unordered_map<int, string> diccionario;
        int codigoActual = 256;

        // El primer código se procesa directamente
        int viejoCodigo = codigos[0];
        string s(1, (char)viejoCodigo); // Simulando el caso base
        simbolosReconstruidos.push_back(s);

        string c = s;

        // 3. Bucle principal de reconstrucción
        for (size_t i = 1; i < codigos.size(); i++) {
            int nuevoCodigo = codigos[i];
            string entrada;

            if (diccionario.find(nuevoCodigo) != diccionario.end()) {
                entrada = diccionario[nuevoCodigo];
            } else if (nuevoCodigo < 256) {
                entrada = string(1, (char)nuevoCodigo);
            } else if (nuevoCodigo == codigoActual) {
                // Caso especial de LZW
                entrada = s + c[0];
            }

            simbolosReconstruidos.push_back(entrada);
            
            // Reconstruir el diccionario exactamente igual que el codificador
            c = entrada;
            diccionario[codigoActual++] = s + c[0];
            s = entrada;
        }
        cout << "[Decodificador] Archivo reconstruido exitosamente." << endl;
    }

    return simbolosReconstruidos;
}