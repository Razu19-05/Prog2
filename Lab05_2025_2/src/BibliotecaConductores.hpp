#ifndef LAB05_2025_2_BIBLIOTECACONDUCTORES_HPP
#define LAB05_2025_2_BIBLIOTECACONDUCTORES_HPP
#include "Utils.hpp"

void *leeConductores(ifstream &input);
int cmpConductores (void* dato, void*registro);
void* buscaListaConductores (void* lista, void* registro);

void cargarUnidades (void *&lista,const char* fileName);

void imprimeConductores(ofstream& output, void* registro);

#endif //LAB05_2025_2_BIBLIOTECACONDUCTORES_HPP