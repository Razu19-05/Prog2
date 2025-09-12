

#ifndef CARPETAFUENTE_OVERLOADS_HPP
#define CARPETAFUENTE_OVERLOADS_HPP
#include "Utils.hpp"
#include "../structs/Estructuras.h"
void operator >> (ifstream &input, Plato &plato);
void operator >> (ifstream &input, Repartidor &repartidor);
void operator >> (ifstream &input, Pedido &pedido);
bool operator <= (Pedido &pedido, Plato *platos);
void operator <= (Repartidor *repartidores,const Pedido pedido);
void operator ! (OrdenDeCompra &orden);
void operator ! (Repartidor &repartidor);
ofstream& operator << (ofstream &out, const Plato &plato) ;
ofstream& operator << (ofstream &out, const Repartidor &rep) ;



#endif //CARPETAFUENTE_OVERLOADS_HPP