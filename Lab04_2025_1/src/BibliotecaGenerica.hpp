//
// Created by Huarote on 1/10/2025.
//

#ifndef LAB04_2025_1_BIBLIOTECAGENERICA_HPP
#define LAB04_2025_1_BIBLIOTECAGENERICA_HPP
#include "Utils.hpp"

void crearLista(void *&lista,void*(*lee)(ifstream &),int (*clasifica)(void*),const char* nameFile);
void imprimeLista(void *lista,void(*imprime)(ofstream &, void*) ,const char* nameFile);

#endif //LAB04_2025_1_BIBLIOTECAGENERICA_HPP