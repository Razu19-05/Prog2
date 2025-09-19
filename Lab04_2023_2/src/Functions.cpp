#include "Functions.hpp"

char* leerCadena(ifstream &input,char delim) {
    char buffer[MAX_PALABRA], *car;
    input.getline(buffer,MAX_PALABRA,delim);
    if (input.eof())return nullptr;
    car = new char[strlen(buffer)+1];
    strcpy(car,buffer);
    return car;
}

void* leerRegistro(ifstream &input) {
    // BIT-434,Campana Extractora modelo Glass,375.09,S
    char *codigo, *descripcion, *ptrTipo, tipo,c;
    double *ptrPrecio, precio;
    codigo = leerCadena(input,',');
    if (input.eof())return nullptr;
    descripcion = leerCadena(input,',');
    input>>precio>>c>>tipo>>ws;
    ptrPrecio = new double(precio);
    ptrTipo = new char (tipo);
    void** registro = new void*[4]{};
    registro[CODIGO] = codigo;
    registro[DESCRIPCION] = descripcion;
    registro[PRECIO] = ptrPrecio;
    registro[TIPO] = ptrTipo;
    return registro;
}

void reservarMemoria(void **&arreglo,int &cantidad,int &capacidad) {
    capacidad += INCREMENTO;
    if (arreglo == nullptr) {
        arreglo = new void*[capacidad]{};
        cantidad = 1;
    }else {
        void** aux = new void*[capacidad]{};
        for (int i = 0; i < cantidad; i++) aux[i] = arreglo[i];
        delete [] arreglo;
        arreglo = aux;
    }
}

void cargarProductos(void *&productos) {
    ifstream input("Productos2.csv",ios::in);
    if (!input.is_open()) {
        cout<<"Error opening file"<<endl;
        exit(1);
    }
    void** arregloProductos = nullptr, *registro;
    int cantidad = 0, capacidad = 0;
    while (true) {
        registro = leerRegistro(input);
        if (registro == nullptr) break;
        if (cantidad == capacidad) reservarMemoria(arregloProductos,cantidad,capacidad);
        arregloProductos[cantidad - 1] = registro;
        cantidad++;
    }
    productos = arregloProductos;
}

void imprimirProducto(void *producto, ofstream &output) {
    void ** registro = (void**) producto;
    char *codigo = (char*)registro[CODIGO];
    char *descripcion = (char*)registro[DESCRIPCION];
    double *precio = (double*)registro[PRECIO];
    char *tipo = (char*)registro[TIPO];
    output << codigo << " " << descripcion << " " << *precio << " " << *tipo <<endl;
}

void imprimirProductos(void *productos) {
    ofstream output("ReporteProducto.txt",ios::out);
    void** arregloProductos = (void**)productos;
    for (int i = 0; arregloProductos[i] ; i++)
        imprimirProducto(arregloProductos[i],output);
}

void *leerRegistro2(ifstream &input) {
    // 79464412,PORTUGAL RAFFO ALEXANDER,3902394,10000
    int *ptrDni, dni, telefono;
    char *nombre, car;
    double *ptrCredito, credito;
    input>>dni;
    if (input.eof())return nullptr;
    input.get();
    nombre = leerCadena(input,',');
    input>>telefono>>car>>credito;
    ptrDni = new int(dni);
    ptrCredito = new double(credito);
    void** registro = new void*[4]{};
    registro[DNI] = ptrDni;
    registro[NOMBRE] = nombre;
    registro[PEDIDOS] = nullptr;
    registro[CREDITO] = ptrCredito;
    return registro;
}

void cargarClientes(void *&clientes){
    ifstream input("Clientes2.csv",ios::in);
    if (!input.is_open()) {
        cout<<"Error opening file"<<endl;
        exit(1);
    }
    void** arregloClientes = nullptr, * registro;
    int cantidad = 0, capacidad = 0;
    while (true) {
        registro = leerRegistro2(input);
        if (registro == nullptr) break;
        if (cantidad == capacidad) reservarMemoria(arregloClientes,cantidad,capacidad);
        arregloClientes[cantidad - 1] = registro;
        cantidad ++;
    }
    clientes = arregloClientes;
}

void imprimirPedido(void* pedido,ofstream &output) {
    void ** registro = (void**) pedido;
    char *codigo = (char*)registro[CODIGOPRODUCTO];
    int *cantidad = (int*) registro[CANTIDAD];
    double *total = (double*) registro[TOTAL];
    output << codigo << " " << *cantidad << " " << *total << endl;
}

void imprimirPedidos(void *pedidos,ofstream& output) {
    void** arregloPedidos = (void**) pedidos;
    for (int i = 0; arregloPedidos[i] ; i++)
        imprimirPedido(arregloPedidos[i],output);
}

void imprimirCliente(void* cliente, ofstream &output) {
    void ** registro = (void**) cliente;
    int *dni = (int*) registro[DNI];
    char *nombre = (char*) registro[NOMBRE];
    double *credito = (double*) registro[CREDITO];
    output << *dni << " " << nombre << " " << *credito << " "<<endl;
    if (registro[PEDIDOS])
        imprimirPedidos(registro[PEDIDOS],output);
}

void imprimirClientes(void *clientes) {
    ofstream output("CReporteClientes.txt",ios::out);
    void** arregloClientes = (void**) clientes;
    for (int i = 0; arregloClientes[i] ; i++)
        imprimirCliente(arregloClientes[i], output);
}

bool sonIguales(char *codigo,void *producto) {
    void** registro = (void**) producto;
    char *ptrCodigo = (char*)registro[CODIGO];
    return (strcmp(ptrCodigo,codigo)==0);
}

int buscarCodigo(char *codigo,void **arregloProductos) {
    for (int i = 0; arregloProductos[i] ; i++)
        if (sonIguales(codigo,arregloProductos[i]))return i;
    return -1;
}

bool sonIguales(int dni,void *cliente) {
    void** registro = (void**) cliente;
    int *ptrDni = (int*) registro[DNI];
    return (*ptrDni == dni);
}

int buscarDni(int dni,void **arregloClientes) {
    for (int i = 0; arregloClientes[i] ; i++)
        if (sonIguales(dni,arregloClientes[i]))return i;
    return -1;
}

void * llenarPedido (void *producto,int cantProducto) {
    void** registro = (void**) producto;
    char *codigo = (char*) registro[CODIGO];
    double *precio = (double*) registro[PRECIO];
    int *ptrCantProducto = new int (cantProducto);
    double *ptrTotal = new double (*precio * cantProducto);
    void **pedido = new void*[3]{};
    pedido[CODIGOPRODUCTO] = codigo;
    pedido[CANTIDAD] = ptrCantProducto;
    pedido[TOTAL] = ptrTotal;
    return pedido;
}

void aumetarMemoria(void* &pedidos,int &cant,int &cap) {
    void** arregloPedidos = (void**) pedidos;
    cap += INCREMENTO;
    if (arregloPedidos == nullptr) {
        arregloPedidos = new void*[cap]{};
        cant = 1;
    } else {
        void** aux = new void*[cap]{};
        for (int i = 0; i < cant; i++) aux[i] = arregloPedidos[i];
        delete arregloPedidos;
        arregloPedidos = aux;
    }
    pedidos = arregloPedidos;
}

void agregarPedido(void* pedido,void *pedidos,int n) {
    void** arregloPedidos = (void**) pedidos;
    arregloPedidos[n] = pedido;
}

void colocarPedido(void* cliente,void *producto,int cantProducto,int &cantidad,int &capacidad) {
    void** registro = (void**) cliente;
    void* pedido = llenarPedido(producto,cantProducto);

    if (cantidad == capacidad)
        aumetarMemoria(registro[PEDIDOS],cantidad,capacidad);

    agregarPedido(pedido, registro[PEDIDOS], cantidad-1);
    cantidad++;
}

void cargarPedidos(void *productos,void *&clientes) {
    ifstream input("Pedidos2.csv",ios::in);
    if (!input.is_open()) {
        cout<<"Error opening file"<<endl;
        exit(1);
    }
    void** arregloClientes = (void**) clientes;
    void** arregloProductos = (void**) productos;
    char *codigo, car;
    int posCodigo, posDni, dni, cantidad[200]{}, capacidad[200]{}, cantProductos;
    void* registroProducto;
    // JXD-139,50375303,6
    while (true) {
        codigo = leerCadena(input,',');
        if (input.eof())break;
        posCodigo = buscarCodigo(codigo,arregloProductos);
        if (posCodigo == - 1) continue;
        input>>dni;
        posDni = buscarDni(dni,arregloClientes);
        if (posDni == -1)continue;
        input>>car>>cantProductos>>ws;
        colocarPedido(arregloClientes[posDni],arregloProductos[posCodigo],cantProductos,cantidad[posDni],capacidad[posDni]);
    }
}