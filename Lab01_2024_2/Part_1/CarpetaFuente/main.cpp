#include "src/Overloads.hpp"
#include "structs/Estructuras.h"

int main() {
    Plato platos[150];
    Repartidor repartidores[40];
    Pedido pedidos[200];
    OrdenDeCompra ordenes[3];
    ifstream archPlato("PlatosOfrecidos.csv",ios::in);
    if (!archPlato.is_open()) {
        cout << "Erro ao abrir o arquivo platos" << endl;
        exit(1);
    }
    ifstream archRepartidor("RepartidoresContratados.csv",ios::in);
    if (!archRepartidor.is_open()) {
        cout << "Erro ao abrir o arquivo platos" << endl;
        exit(1);
    }
    ifstream archPedido("OrdenesDeCompra.txt",ios::in);
    if (!archPedido.is_open()) {
        cout << "Erro ao abrir o arquivo platos" << endl;
        exit(1);
    }
    ofstream outPlato ("ReportePlato.txt",ios::out);
    ofstream outRepartidor ("ReporteRepartidor.txt",ios::out);
    int cantPlato = 0, cantRepartidor = 0, cantPedido = 0;
    while (true) {
        archPlato >> platos[cantPlato];
        if (archPlato.eof()) break;                 // usa el estado del stream, no eof() después
        cout << platos[cantPlato].codigo << "  "
             << platos[cantPlato].nombre << "  "
             << platos[cantPlato].precio << endl;
        cantPlato++;
    }
    strcpy(platos[cantPlato].codigo, "FIN");
    while (true) {
        archRepartidor >> repartidores[cantRepartidor];
        if (archRepartidor.eof()) break;
        cout << repartidores[cantRepartidor].codigo << "  "
             << repartidores[cantRepartidor].nombre << "  "
             << repartidores[cantRepartidor].tipoDeVehiculo << endl;
        cantRepartidor++;
    }
    strcpy(repartidores[cantRepartidor].codigo, "FIN"); // <-- centinela real
    while (true) {
        archPedido >> pedidos[cantPedido];
        if (!archPedido) break;
        cout << pedidos[cantPedido].dniDelCliente << " "
             << pedidos[cantPedido].codigoDelPlato << " "
             << pedidos[cantPedido].cantidad << " "
             << pedidos[cantPedido].codigoDelRepartidor << " "
             << pedidos[cantPedido].distanciaARecorrer << endl;

        // Procesa inmediatamente para evitar olvidos:
        pedidos[cantPedido] <= platos;
        repartidores <= pedidos[cantPedido];
        cantPedido++;
    }
    for (int i = 0; strcmp(repartidores[i].codigo, "FIN") != 0; i++) {
        !repartidores[i];
    }
    for (int i = 0; strcmp(platos[i].codigo,"FIN") != 0; i++) {
        outPlato << platos[i] << endl;
    }
    // REPARTIDORES
    // for (int i = 0; strcmp(repartidores[i].codigo,"FIN") != 0; i++) {
    //     outRepartidor << repartidores[i] << endl;
    // }

    return 0;
}