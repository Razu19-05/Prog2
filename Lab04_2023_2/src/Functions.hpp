#ifndef LAB04_2023_2_FUNCTIONS_HPP
#define LAB04_2023_2_FUNCTIONS_HPP
#include "Utils.hpp"

char* leerCadena(ifstream &input,char delim);
void reservarMemoria(void **&arreglo,int &cantidad,int &capacidad);

void* leerRegistro(ifstream &input);
void cargarProductos(void *&productos);

void imprimirProducto(void *producto, ofstream &output);
void imprimirProductos(void *productos);

void *leerRegistro2(ifstream &input);
void cargarClientes(void *&clientes);

void imprimirCliente(void* cliente, ofstream &output);
void imprimirClientes(void *clientes);


bool sonIguales(char *codigo,void *producto);
bool sonIguales(int dni,void *cliente) ;
int buscarCodigo(char *codigo,void **arregloProductos) ;
int buscarDni(int dni,void **arregloClientes) ;
void * llenarPedido (void *producto,int cantProducto) ;
void aumetarMemoria(void* &pedidos,int &cant,int &cap);
void agregarPedido(void* pedido,void *pedidos,int n);
void colocarPedido(void* cliente,void *producto,int cantProducto,int &cantidad,int &capacidad);
void cargarPedidos(void *productos,void *&clientes);
#endif //LAB04_2023_2_FUNCTIONS_HPP