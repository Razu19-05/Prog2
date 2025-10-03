//
// Created by Huarote on 2/10/2025.
//

#ifndef LAB05_2025_2_BIBLIOTECAINFRACCIONES_HPP
#define LAB05_2025_2_BIBLIOTECAINFRACCIONES_HPP
#include "Utils.hpp"
void* leeInfracciones (ifstream& input);
int cmpInfracciones(void *dato,void*registro);
void *buscaListaInfraccion(void *lista,void *registro);

#endif //LAB05_2025_2_BIBLIOTECAINFRACCIONES_HPP