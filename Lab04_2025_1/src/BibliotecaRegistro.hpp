//
// Created by Huarote on 2/10/2025.
//

#ifndef LAB04_2025_1_BIBLIOTECAREGISTRO_HPP
#define LAB04_2025_1_BIBLIOTECAREGISTRO_HPP
#include "Utils.hpp"
void* leeRegistro(ifstream &);
int clasificaRegistro(void*);
void imprimeRegistro(ofstream &, void*);
#endif //LAB04_2025_1_BIBLIOTECAREGISTRO_HPP