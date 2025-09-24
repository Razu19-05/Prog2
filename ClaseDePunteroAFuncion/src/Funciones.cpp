#include "Funciones.hpp"
void* leeNum(ifstream &input) {
    void** dato;
    int numero, *num;
    input>>numero;
    if (input.eof())return nullptr;
    num = new int(numero);
    dato = new void*[1]{};
    dato[PEDIDO] = num;
    return dato;
}

void imprimeNum(ofstream &arch, void *dato) {
    void** datoAlum = (void**) dato;
    int *num = (int*) datoAlum[PEDIDO];
    arch<<*num<<endl;
}