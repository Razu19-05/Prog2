//
// Created by Huarote on 1/10/2025.
//

#include "BibliotecaEnteros.hpp"

void* leeNum(ifstream & input) {
    int num, *ptr_num;
    input>>num;
    if (input.eof())return nullptr;
    ptr_num = new int(num);
    void **registro = new void *[1]{};
    registro[0]=ptr_num;
    return registro;
}

int clasificaNum(void* dato) {
    void **numeros = (void**)dato;
    int *ptr_numero = (int*)numeros[0];
    if (*ptr_numero < 10) return 0;
    return 1;
}

void imprimeNum(ofstream &output, void*registro) {
    void **dato =(void **)registro;
    int *ptr_numero = (int*)dato[0];
    output << *ptr_numero<<endl;
}