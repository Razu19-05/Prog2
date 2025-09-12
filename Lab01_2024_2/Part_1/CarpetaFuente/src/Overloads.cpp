
#include "Overloads.hpp"


void operator >> (ifstream &input, Plato &plato) {
    // AP-500,CHORIZOS COCKTAIL,12.90,APERITIVO
    input.getline(plato.codigo,7,',');
    if (input.eof())return;
    input.getline(plato.nombre,60,',');
    input>>plato.precio;
    plato.totalDePedidos = 0;
    plato.totalRecaudado = 0.0;
    while (input.get()!='\n') continue;
}

void operator >> (ifstream &input, Repartidor &repartidor) {
    // JNV387,Justino Norabuena Virginia Karina,Motocicleta
    input.getline(repartidor.codigo,7,',');
    if (input.eof())return;
    input.getline(repartidor.nombre,60,',');
    input.getline(repartidor.tipoDeVehiculo,15,'\n');
    repartidor.cantidadDeOrdenes=0;
    repartidor.pagoPorEntregas = 0.0;
}

void operator >> (ifstream &input, Pedido &pedido) {
    // 15290194  BR-283    1    MCE193    11.69;
    input>>pedido.dniDelCliente;
    if (input.eof())return;
    input>>pedido.codigoDelPlato;
    input>>pedido.cantidad;
    input>>pedido.codigoDelRepartidor;
    input>>pedido.distanciaARecorrer;
    pedido.precio = 0.0;
}

bool operator <= (Pedido &pedido, Plato *platos) {
    for (int i = 0; strcmp(platos[i].codigo,"FIN") != 0; i++)
        if (strcmp(platos[i].nombre,pedido.codigoDelPlato)==0) {
            pedido.precio = pedido.cantidad * platos[i].precio;
            platos[i].totalDePedidos += pedido.cantidad;
            platos[i].totalRecaudado += pedido.precio;
            return true;
        }
    return false;
}

void operator <= (Repartidor *repartidores, const Pedido pedido) {
    for (int i = 0; strcmp(repartidores[i].codigo,"FIN") != 0; i++) {
        if (strcmp(repartidores[i].codigo, pedido.codigoDelRepartidor) == 0) {
            Repartidor &rep = repartidores[i];
            bool clienteEncontrado = false;
            // Buscar si ya existe el cliente en sus ordenes
            for (int j = 0; j < rep.cantidadDeOrdenes; j++) {
                if (rep.ordenesDeCompra[j].dniDelCliente == pedido.dniDelCliente) {
                    clienteEncontrado = true;
                    OrdenDeCompra &orden = rep.ordenesDeCompra[j];
                    bool platoEncontrado = false;
                    // Buscar si ya pidió ese plato
                    for (int k = 0; k < orden.cantidadDePlatos; k++) {
                        if (strcmp(orden.platosSolicitados[k].codigo, pedido.codigoDelPlato) == 0) {
                            orden.platosSolicitados[k].cantidad += pedido.cantidad;
                            orden.platosSolicitados[k].precio += pedido.precio;
                            platoEncontrado = true;
                            break;
                        }
                    }
                    // Si es un nuevo plato
                    if (!platoEncontrado) {
                        strcpy(orden.platosSolicitados[orden.cantidadDePlatos].codigo, pedido.codigoDelPlato);
                        orden.platosSolicitados[orden.cantidadDePlatos].cantidad = pedido.cantidad;
                        orden.platosSolicitados[orden.cantidadDePlatos].precio = pedido.precio;
                        orden.cantidadDePlatos++;
                    }
                    // Actualizar montos
                    orden.montoPorCobrar += pedido.precio;
                    // orden.distancia = pedido.distanciaARecorrer;
                    break;
                }
            }
            // Si no se encontró al cliente → crear nueva orden
            if (!clienteEncontrado) {
                OrdenDeCompra &orden = rep.ordenesDeCompra[rep.cantidadDeOrdenes];
                orden.dniDelCliente = pedido.dniDelCliente;
                orden.distancia = pedido.distanciaARecorrer;
                orden.cantidadDePlatos = 0;

                strcpy(orden.platosSolicitados[0].codigo, pedido.codigoDelPlato);
                orden.platosSolicitados[0].cantidad = pedido.cantidad;
                orden.platosSolicitados[0].precio = pedido.precio;
                orden.cantidadDePlatos ++;
                orden.montoPorCobrar = pedido.precio;
                orden.pagoPorEnvio = 0.0; // se calcula después

                rep.cantidadDeOrdenes++;
            }
            return; // ya encontramos al repartidor, terminamos
        }
    }
}

void operator ! (OrdenDeCompra &orden) {
    if (orden.distancia < 8) orden.pagoPorEnvio = 10.50;
    else if (orden.distancia <= 12) orden.pagoPorEnvio = 14.80;
    else if (orden.distancia <= 20) orden.pagoPorEnvio = 23.60;
    else orden.pagoPorEnvio = 31.70;
}

void operator ! (Repartidor &repartidor) {
    for (int i = 0; i < repartidor.cantidadDeOrdenes; i++) {
        !repartidor.ordenesDeCompra[i];
        repartidor.pagoPorEntregas += repartidor.ordenesDeCompra[i].pagoPorEnvio;
    }
}

ofstream& operator << (ofstream &out, const Plato &plato) {
    out << left << setw(7) << plato.codigo
        << setw(30) << plato.nombre
        << right << fixed << setprecision(2)
        << setw(8) << plato.precio
        << setw(6) << plato.totalDePedidos
        << setw(10) << plato.totalRecaudado;
    return out;
}

ofstream& operator << (ofstream &out, const Repartidor &rep) {
    out << left << setw(7) << rep.codigo
        << setw(40) << rep.nombre
        << setw(15) << rep.tipoDeVehiculo
        << right << fixed << setprecision(2)
        << setw(8) << rep.pagoPorEntregas << endl;
    out << "ORDENES ENTREGADAS:" << endl;
    for (int i = 0; i < rep.cantidadDeOrdenes; i++) {
        const OrdenDeCompra &orden = rep.ordenesDeCompra[i];
        out << setw(10) << orden.dniDelCliente
            << setw(8) << fixed << setprecision(2) << orden.distancia
            << setw(10) << orden.montoPorCobrar
            << setw(8) << orden.pagoPorEnvio << endl;

        out << "   Platos solicitados:" << endl;
        for (int j = 0; j < orden.cantidadDePlatos; j++) {
            const PlatoSolicitado &ps = orden.platosSolicitados[j];
            out << "   - " << setw(7) << ps.codigo
                << setw(8) << ps.precio
                << setw(4) << ps.cantidad
                << setw(10) << ps.precio << endl;
        }
    }
    return out;
}
