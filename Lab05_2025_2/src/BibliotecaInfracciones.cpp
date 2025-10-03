
#include "BibliotecaInfracciones.hpp"
char *leerCad(ifstream &input,char c){
    char *ptr,cadena[200];
    input.getline(cadena,200,c);
    ptr=new char[strlen(cadena)+1];
    strcpy(ptr,cadena);
    return ptr;
}
void *leeInfracciones(ifstream &input){
    int *licencia=new int();
    char *placa,c;
    int *fecha=new int();
    int dd,mm,aa;
    int *tipo=new int();
    input>>*licencia;
    if (input.eof())return nullptr;
    input.get();
    placa=leerCad(input,',');
    input>>dd>>c>>mm>>c>>aa>>c>>*tipo;
    *fecha=dd*1000000+mm*10000+aa;
    void **registro=new void*[4]{};
    registro[LICENCIA1]=licencia;
    registro[PLACA]=placa;
    registro[FECHA]=fecha;
    registro[TIPO]=tipo;
    return registro;
}
int cmpInfracciones(void *dato,void*registro){
    void **_dato=(void**)dato;
    void **_registro=(void**)registro;
    int fecha1=*(int *)_dato[FECHA];
    int fecha2=*(int*)_registro[FECHA];
    return fecha1-fecha2;
}
void *buscaListaInfraccion(void *lista,void *registro){
    void **_registro=(void**)registro;
    void **_lista=(void**)lista;
    void **recorrido=(void**)_lista[INICIO];
    while(recorrido!=nullptr){
        void **data=(void**)recorrido[DATO];
        int licencia=*(int *)data[LICENCIA];
        if(licencia==*(int *)_registro[LICENCIA1])return data[LISTA];
        recorrido=(void**)recorrido[SIGUIENTE];
    }
    // return nullptr;
}