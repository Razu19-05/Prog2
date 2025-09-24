
#ifndef CLASEDEPUNTEROAFUNCION_FUNCIONESGENERICAS_HPP
#define CLASEDEPUNTEROAFUNCION_FUNCIONESGENERICAS_HPP
#include "Funciones.hpp"
#include "Utils.hpp"

void crearLista(void *&pedidos1,void*(*lee)(ifstream &), const char* nameFile);
void imprimirLista(void *pedidos1, void (*imprime)(ofstream &, void *), const char *nameFile);
void unirListas(void *pedidos1,void *pedidos2,void *&pedidosFinal,int (*cmp)(void *, void *));

#endif //CLASEDEPUNTEROAFUNCION_FUNCIONESGENERICAS_HPP