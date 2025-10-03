#include "src/BibliotecaGenerica.hpp"
#include "src/BibliotecaConductores.hpp"
#include "src/BibliotecaInfracciones.hpp"

int main() {
    void* lista;
    generarLista(lista);
    crearLista(lista, leeConductores, cmpConductores, buscaListaConductores,"conductores.csv");
    cargarUnidades(lista,"Unidades.csv");
    imprimeLista(lista,imprimeConductores,"Reporte.txt");
    crearLista(lista,leeInfracciones, cmpInfracciones, buscaListaInfraccion,"faltas.csv");
    imprimeLista(lista,imprimeConductores,"Reporte2.txt");
    return 0;
}