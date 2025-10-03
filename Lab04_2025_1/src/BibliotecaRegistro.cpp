//
// Created by Huarote on 2/10/2025.
//

#include "BibliotecaRegistro.hpp"
char *leerCadena(ifstream &input,char delim) {
    char *cadena, buffer[200];
    input.getline(buffer,200,delim);
    cadena = new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}
void* leeRegistro(ifstream &input) {
    // 47844324	X7J-719	14/09/2019	101	VILCA LEE NESTOR HUGO
    int licencia, *ptrLicencia, *ptrFecha, infraccion, *ptrInfraccion, dd,mm,aa,fecha;
    char null, *placa, *nombre;
    input>>licencia;
    if (input.eof())return nullptr;
    input.get();
    placa = leerCadena(input,',');
    input>>dd>>null>>mm>>null>>aa>>null>>infraccion>>null;
    nombre = leerCadena(input,'\n');
    input>>ws;
    fecha = aa*10000 + mm*100 + dd;
    ptrLicencia = new int(licencia);
    ptrFecha = new int(fecha);
    ptrInfraccion = new int(infraccion);
    void **registro = new void*[5]{};
    registro[LICENCIA] = ptrLicencia;
    registro[PLACA]=placa;
    registro[FECHA] = ptrFecha;
    registro[INFRACCION] = ptrInfraccion;
    registro[NOMBRE] = nombre;
    return registro;
}

int clasificaRegistro(void* dato) {
    void** registro = (void**) dato;
    int *infraccion = (int*) registro[INFRACCION];
    int digito = *infraccion/100;
    if (digito == 1) return 0;
    return 1;
}

void separador(ofstream &output,char car,int num) {
    for(int i=0;i<num;i++) output<<car;
    output<<endl;
}

void imprimeRegistro(ofstream &output, void*dato) {
    static bool imprimirCabezera = true;
    if (imprimirCabezera) {
        output<<left<<setw(13)<<"FECHA"<<setw(13)<<"LICENCIA"<<setw(59)<<"NOMBRE"<<"FALTA"<<endl;
        separador(output,'=',MAX_LINEAS);
        imprimirCabezera=false;
    }
    void **registro = (void**) dato;
    int *infraccion = (int*) registro[INFRACCION];
    int *fecha = (int*) registro[FECHA];
    int *licencia = (int*) registro[LICENCIA];
    char *nombre = (char*) registro[NOMBRE];
    char *placa = (char*) registro[PLACA];
    int dd,mm,aa;
    aa = *fecha/10000;
    *fecha = *fecha%10000;
    mm = *fecha/100;
    dd = *fecha%100;
    output<<right<<setfill('0')<<setw(4)<<aa<<'/'<<setw(2)<<mm<<'/'<<setw(2)<<dd<<setfill(' ')
            <<left<<setw(3)<<' '<<setw(13)<<*licencia<<setw(60)<<nombre<<*infraccion<<endl;
}