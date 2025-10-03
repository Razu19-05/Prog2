//
// Created by Huarote on 1/10/2025.
//

#include "BibliotecaGenerica.hpp"

#include <pstl/unseq_backend_simd.h>

void generarLista(void *&lista) {
    void**_lista = new void*[2]{};
    void** bloque1 = new void*[2]{};
    void** bloque2 = new void*[2]{};
    bloque1[DATO] = nullptr;
    bloque1[SIGUIENTE] = bloque2;
    bloque2[DATO] = nullptr;
    bloque2[SIGUIENTE] = nullptr;
    _lista[INICIO] = bloque1;
    _lista[FINAL] = bloque2;
    lista = _lista;

}

void insertar(void *lista,void *registro, int (*clasifica)(void*)) {
    int pos = clasifica(registro);
    void **_lista = (void**) lista;
    void **nodo = (void**)_lista[pos];//en que bloque se encuentra
    if (nodo[DATO] == nullptr)
        nodo[DATO] = registro;
    else {
        void **nuevonodo = new void*[2];
        nuevonodo[DATO] = registro;
        nuevonodo[SIGUIENTE] = nullptr;
        void **recorrer=(void**)_lista[pos];//para recorrer el bloque que esta
        void **anterior=nullptr;
        while(true){
            if(pos==0){ //si esta en el bloq1
                if(recorrer==nullptr)break;
                else {
                    if(recorrer[DATO]!=nullptr){
                        int dato=clasifica(recorrer[DATO]);
                        if(pos!=dato)break;//pregunta si ya llego al segundo bloque
                    }else break;
                }
            }else
                if(recorrer==nullptr)break;
            anterior=recorrer;
            recorrer=(void**)recorrer[SIGUIENTE];//es el recorrer ++
        }
        //unir el nuevoNodo
        nuevonodo[SIGUIENTE]=anterior[SIGUIENTE];
        anterior[SIGUIENTE]=nuevonodo;
    }
}

void crearLista(void *&lista,void*(*lee)(ifstream &),int (*clasifica)(void*),const char* nameFile) {
    ifstream input (nameFile, ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << nameFile << endl;
        exit(1);
    }
    void *registro;
    generarLista(lista);
    while (true) {
        registro = lee(input);
        if (registro == nullptr) break;
        insertar(lista, registro, clasifica);
    }
}

void imprimeLista(void *lista,void(*imprime)(ofstream &, void*) ,const char* nameFile) {
    ofstream output (nameFile, ios::out);
    void **recorrer_lista = (void**)lista;
    void **imprimir = (void**)recorrer_lista[INICIO];//INICIA DEL PRIMER BLOQ
    while (imprimir) {
        if (imprimir[DATO] == nullptr)break;
        imprime(output, imprimir[DATO]);
        imprimir = (void **)imprimir[SIGUIENTE];
    }
}