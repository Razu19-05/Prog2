
#include "Overloads.hpp"

#include <codecvt>

char * leerNombre(ifstream &input,char delim) {
    char buffer[220], *cad;
    input.getline(buffer,220,delim);
    cad = new char[strlen(buffer)+1];
    strcpy(cad,buffer);
    return cad;
}

void leerConductores(ifstream& input,int *bufferDnis,char **bufferNombres,int &n) {
    int dni;
    char * nombre;
    while (true) {
        input>> dni;
        if (input.eof()) break;
        input.get();
        nombre = leerNombre(input,'\n');
        bufferDnis[n] = dni;
        bufferNombres[n] = nombre;
        n++;
    }
}

void cargarConductores(int *bufferDnis, char **bufferNombres, Conductores &conductores) {
    conductores.dnis = new int [conductores.cantidad+1]{};
    conductores.nombres = new char * [conductores.cantidad+1]{};
    for (int i = 0; i < conductores.cantidad; i++) {
        conductores.nombres[i] =  bufferNombres[i];
        conductores.dnis[i] = bufferDnis[i];
    }
}

void operator += (Conductores &conductores,const char*nameFile) {
    ifstream input(nameFile,ios::in);
    if(!input.is_open()) {
        cout<<"Error in opening file "<<nameFile<<endl;
        exit(1);
    }
    conductores.cantidad = 0;
    int bufferDnis[MAX_CONDUCTORES]{};
    char *bufferNombres[MAX_CONDUCTORES]{};
    leerConductores(input,bufferDnis,bufferNombres,conductores.cantidad);
    cargarConductores(bufferDnis, bufferNombres, conductores);
}

void leerInfracciones(ifstream& input,int *bufferCodigos,char **bufferDescripciones,
                        char **bufferTipos,double *bufferValores,int &n) {
    int codigo;
    char* descripcion, *tipo;
    double valor;
    // 101;Adelantar o sobrepasar en forma indebida a otro vehículo.;Grave;316.00
    while (true) {
        input>>codigo;
        if (input.eof()) break;
        input.get();
        descripcion = leerNombre(input,';');
        tipo = leerNombre(input,';');
        input>>valor;
        bufferCodigos[n] = codigo;
        bufferDescripciones[n] = descripcion;
        bufferTipos[n] = tipo;
        bufferValores[n] = valor;
        n++;
    }
}

void cargarInfracciones(int *bufferCodigos,char **bufferDescripciones,
                        char **bufferTipos,double *bufferValores,Infracciones &infracciones) {
    infracciones.codigos = new int [infracciones.cantidad+1]{};
    infracciones.descripciones = new char * [infracciones.cantidad+1]{};
    infracciones.tipos = new char * [infracciones.cantidad+1]{};
    infracciones.valores = new double[infracciones.cantidad+1]{};
    for (int i = 0; i < infracciones.cantidad; i++) {
        infracciones.codigos[i] = bufferCodigos[i];
        infracciones.descripciones[i] = bufferDescripciones[i];
        infracciones.tipos[i] = bufferTipos[i];
        infracciones.valores[i] = bufferValores[i];
    }
}

void operator += (Infracciones &infracciones,const char*nameFile) {
    ifstream input(nameFile,ios::in);
    if(!input.is_open()) {
        cout<<"Error in opening file "<<nameFile<<endl;
        exit(1);
    }
    infracciones.cantidad = 0;
    int bufferCodigos[MAX_INFRACCIONES]{};
    char *bufferDescripciones[MAX_INFRACCIONES]{};
    char *bufferTipos[MAX_INFRACCIONES]{};
    double bufferValores[MAX_INFRACCIONES]{};
    leerInfracciones(input,bufferCodigos,bufferDescripciones,bufferTipos,bufferValores,infracciones.cantidad);
    cargarInfracciones(bufferCodigos,bufferDescripciones,bufferTipos,bufferValores,infracciones);
}