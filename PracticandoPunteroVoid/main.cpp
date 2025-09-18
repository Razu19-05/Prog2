#include "src/FuncionesGenericas.hpp"

int main() {
    void *alumnos;
    cargarAlumnos(alumnos,"Alumnos.csv");
    cargarCursos(alumnos,"CursosNotas.csv");
    // probarCarga(alumnos,"Reporte.txt");
    cargarPromedios(alumnos);
    probarCarga(alumnos,"ReporteCompleto.txt");
    ordenamiento(alumnos);
    probarCarga(alumnos,"ReporteCompletoOrdenado.txt");

    return 0;
}