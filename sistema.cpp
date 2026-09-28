#include<iostream>

using namespace std;

class Sistema{
    private:
        int bits;
        string tipoFuente;
        string codificacion;
        //string tipoFuente;
        float cantidadInformacion;
        float entropia;
        float informacionMutua;
        float divergenciaKL;

    public:
        Sistema(int bits,string tipoFuente, string codificacion, string tipoFuente){
            this->bits = bits;
            this->tipoFuente = tipoFuente;
            this->codificacion = codificacion;
            this->tipoFuente = tipoFuente;

            this -> cantidadInformacion = 0.0;
            this -> entropia = 0.0;
            this-> informacionMutua = 0.0;
            this-> divergenciaKL = 0.0;
        }
     
        
};