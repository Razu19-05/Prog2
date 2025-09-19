#include "src/Functions.hpp"

int main() {
    void *productos, *clientes;
    cargarProductos(productos);
    imprimirProductos(productos);
    cargarClientes(clientes);
    // imprimirClientes(clientes);
    cargarPedidos(productos,clientes);
    imprimirClientes(clientes);
    return 0;
}