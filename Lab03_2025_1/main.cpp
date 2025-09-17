

#include "src/Functions.hpp"

int main() {
    Tabla tabla;
    cargarTablaInfraccones("infracciones.csv",tabla);
    recorreTabla(tabla,"reporte.txt");
    return 0;
}