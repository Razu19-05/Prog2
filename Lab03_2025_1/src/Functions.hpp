
#ifndef LAB03_2025_1_FUNCTIONS_HPP
#define LAB03_2025_1_FUNCTIONS_HPP
#include "Utils.hpp"
#include "Structs.hpp"

void inicializarTabla(Tabla &tabla);
void insertarColumna(Tabla &tabla, char *tipo);
void insertarFila(Tabla &tabla);
void insertarCampo(Tabla &tabla, void* fila, int posColumna, void* dato);
void cargarTablaInfraccones(const char* fileName,Tabla &tabla);
void* abrirCursor(Tabla &tabla);
void recorreTabla(Tabla &tabla,const char* nameFile);

#endif //LAB03_2025_1_FUNCTIONS_HPP