#include "src/FuncionesGenericas.hpp"
#include "src/Funciones.hpp"

int main () {
    void *pedidos1, *pedidos2, *pedidosFinal;
    crearLista(pedidos1,leeNum, "RegistroNum1.txt");
    imprimirLista(pedidos1,imprimeNum, "ReporteNum1.txt");
    crearLista(pedidos2,leeNum, "RegistroNum2.txt");
    imprimirLista(pedidos2,imprimeNum, "ReporteNum2.txt");
    unirListas(pedidos1,pedidos2,pedidosFinal,cmpNum);
    return 0;
}