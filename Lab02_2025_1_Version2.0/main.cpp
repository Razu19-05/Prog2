#include "src/Functions.hpp"


int main() {
    Conductores conductores;
    Infracciones infracciones;
    Faltas faltas;
    conductores += "Data/conductores.csv";
    // for (int i = 0; i < conductores.cantidad; i++) {
    //     cout<<conductores.dnis[i]<<"  ";
    //     cout<<conductores.nombres[i]<<endl;
    // }
    infracciones += "Data/infracciones.csv";
    // for (int i = 0; i < infracciones.cantidad; i++) {
    //     cout<<infracciones.codigos[i]<<"  ";
    //     cout<<infracciones.descripciones[i]<<"  ";
    //     cout<<infracciones.tipos[i]<<"  ";
    //     cout<<infracciones.valores[i]<<endl;
    // }
    cargarFaltasDeLosConductores(faltas);
    imprimirFaltasDeLosConductores(faltas,"Report/ReporteConductores");



    return 0;
}