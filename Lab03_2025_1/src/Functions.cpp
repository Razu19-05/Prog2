#include "Functions.hpp"

char* leerCadena(ifstream &input,char delim) {
    char buffer[200],*car;
    input.getline(buffer,200,delim);
    car = new char[strlen(buffer)+1];
    strcpy(car,buffer);
    return car;
}

void inicializarTabla(Tabla &tabla) {
    tabla.columnas=nullptr;
    tabla.cant_columnas=0;
    tabla.capacidad_columnas=0;
    tabla.filas=nullptr;
    tabla.cant_filas=0;
    tabla.capacidad_filas=0;
}

void reservarMemoria(void **&datos,int &cant, int &capacidad) {
    capacidad += INCREMENTO_COLUMNA;
    if (datos==nullptr) {
        datos=new void*[capacidad]{};
        cant++;
    }else {
        void** aux = new void*[capacidad]{};
        for (int i; i < cant; i++) aux[i]=datos[i];
        delete datos;
        datos=aux;
    }
}

void insertarColumna(Tabla &tabla, char *tipo) {
    void** datos = (void**)tabla.columnas;//lo convierto en void** para pasar los datos
    if (tabla.cant_columnas == tabla.capacidad_columnas) {
        reservarMemoria(datos,tabla.cant_columnas,tabla.capacidad_columnas);
        cout<<tabla.capacidad_columnas<<endl;
        tabla.columnas=datos;//aqui guardo los datos ya con su separacion de espacios
    }
    //guardar literalmente el nombre del tipo de dato
    char* ptr_tipo = new char[strlen(tipo)+1];
    strcpy(ptr_tipo,tipo);
    datos[tabla.cant_columnas - 1]=ptr_tipo;
    tabla.cant_columnas++;
}

void insertarFila(Tabla &tabla) {
    tabla.cant_filas++;
    void** datos = (void**)tabla.filas;
    if (tabla.cant_filas > tabla.capacidad_filas) {
        reservarMemoria(datos,tabla.cant_filas,tabla.capacidad_filas);
        tabla.filas=datos;
    }
    void**arreglo, *registro;
    arreglo = new void*[tabla.cant_columnas]{};
    //tambie se puede poner directo como el comentario de abajo pero para que entiendas lo paso void * = void**
    registro = arreglo;
    // para luedo poner void* = void*
    datos[tabla.cant_filas - 2] = registro; // se le resta 2 ya que cuando sale de reservarMemoria sale con 2 en cant
    // datos[tabla.cant_filas - 2]=arreglo;

}

void insertarCampo(Tabla &tabla, void* fila, int posColumna, void* dato) {
    //esta validacion puede estar de mas pero para asegurar que esta dentro del rango
    if (posColumna < tabla.cant_columnas) {
        void**info = (void**)fila;
        info[posColumna] = dato;
    }else cout<<"No se encontro en la columna"<<endl;
}

void inicializar(Tabla &tabla) {
    inicializarTabla(tabla);
    // 101;Adelantar o sobrepasar en forma indebida a otro vehículo.;Grave;316.00;
    //lo casteo a char*
    insertarColumna(tabla,(char*)"INT");
    insertarColumna(tabla,(char*)"CHAR*");
    insertarColumna(tabla,(char*)"CHAR*");
    insertarColumna(tabla,(char*)"DOUBLE");

}

void cargarTablaInfraccones(const char* fileName,Tabla &tabla) {
    inicializar(tabla);
    ifstream input(fileName,ios::in);
    if (!input.is_open()) {
        cout<<"Error al abrir el archivo"<<endl;
        exit(1);
    }
    // 101;Adelantar o sobrepasar en forma indebida a otro vehículo.;Grave;316.00
    int codigo, contadorFilas = 0;
    char *descripcion, *tipo;
    double valor;
    while (true) {
        input>>codigo;
        if (input.eof()) break;
        input.get();
        descripcion = leerCadena(input,';');
        tipo = leerCadena(input,';');
        input>>valor;
        int *ptr_codigo = new int(codigo);
        double *ptr_valor = new double(valor);
        insertarFila(tabla);
        void** fila = (void**)tabla.filas;
        insertarCampo(tabla,fila[contadorFilas],0,ptr_codigo);
        insertarCampo(tabla,fila[contadorFilas],1,descripcion);
        insertarCampo(tabla,fila[contadorFilas],2,tipo);
        insertarCampo(tabla,fila[contadorFilas],3,ptr_valor);
        contadorFilas++;
    }
}

void* abrirCursor(Tabla &tabla) {
    // El cursor será un int* que almacena el índice actual
    int* pos = new int(-1);
    return pos;
}

bool haySiguiente(void* &cursor, Tabla &tabla) {
    int* pos = (int*)cursor;
    if (*pos +  1 < tabla.cant_filas) {
        (*pos)++;
        return true;
    }
    return false;
}

void* obtenerCampo(Tabla &tabla, void* cursor, int posColumna) {
    //este me da la posicion del cursor
    int* filaIdx = (int*)cursor;
    //este me da el arreglo de filas de la tabla
    void** filas = (void**)tabla.filas;
    //este me da el arreglo que contiene la fila en la posicion cursor
    void** fila = (void**)filas[*filaIdx];
    //returno el elemento de la posColuma (codigo, descripcion, tipo, valor)
    return fila[posColumna];
}

void recorreTabla(Tabla &tabla,const char* nameFile){
    ofstream output(nameFile,ios::out);
    if (!output.is_open()) {
        cout<<"Error al abrir reporte"<<endl;
        return;
    }

    void* cursor = abrirCursor(tabla);
    while (haySiguiente(cursor,tabla)) {
        int codigo = *(int*)obtenerCampo(tabla,cursor,0);
        char *descripcion = (char*)obtenerCampo(tabla,cursor,1);
        char *tipo = (char*)obtenerCampo(tabla,cursor,2);
        double valor = *(double*)obtenerCampo(tabla,cursor,3);
        output<<codigo<<" "<<descripcion<<" "<<tipo<<' '<<valor<<endl;
    }
}