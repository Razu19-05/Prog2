#ifndef LAB05_2025_2_BIBLIOTECAGENERICA_HPP
#define LAB05_2025_2_BIBLIOTECAGENERICA_HPP
#include "Utils.hpp"

void generarLista (void *&lista);
void crearLista (void *&lista,void* (*lee)(ifstream&), int (*cmp)(void*, void*), void* (*buscar)(void*, void*),
    const char* fileName);
void imprimeLista(void *lista,void (*imprime)(ofstream&, void*),const char* fileName);
#endif //LAB05_2025_2_BIBLIOTECAGENERICA_HPP