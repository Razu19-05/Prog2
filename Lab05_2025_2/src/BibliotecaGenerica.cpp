#include "BibliotecaGenerica.hpp"

#include "BibliotecaConductores.hpp"

void generarLista(void *&lista) {
    void **_lista = new void *[1]{};
    _lista[INICIO] = nullptr;
    lista = _lista;
}

void insertarLista(void *lista,void *dato,int (*cmp)(void*, void*)) {
    void ** nuevoNodo = new void *[2]{};
    nuevoNodo[DATO] = dato;
    nuevoNodo[SIGUIENTE] = nullptr;
    void ** _lista = (void**)lista;
    void ** recorrido = (void **) _lista[INICIO];
    void ** anterior = nullptr;
    while (recorrido!= nullptr) {
        if (cmp(recorrido[DATO],dato)>0)break;
        anterior = recorrido;
        recorrido = (void**)recorrido[SIGUIENTE];
    }
    nuevoNodo[SIGUIENTE] = recorrido;
    if (anterior == nullptr) _lista[INICIO] = nuevoNodo;
    else anterior[SIGUIENTE] = nuevoNodo;
}

void crearLista(void *&lista,void* (*lee)(ifstream&), int (*cmp)(void*, void*), void* (*buscar)(void*, void*),
    const char* fileName) {
    ifstream input(fileName,ios::in);
    if(!input.is_open()) {
        cout << "Erro ao abrir arquivo " << fileName << endl;
        exit(1);
    }
    void *registro;
    while (true) {
        registro = lee(input);
        if (registro == nullptr) break;
        insertarLista(buscar(lista,registro),registro,cmp);
    }
}

void imprimeLista(void *lista,void (*imprime)(ofstream&, void*),const char* fileName) {
    ofstream output(fileName,ios::out);
    void** _lista = (void**)lista;
    void ** recorrido = (void**)_lista[INICIO];
    while (recorrido!= nullptr) {
        imprime(output,recorrido[DATO]);
        recorrido = (void**)recorrido[SIGUIENTE];
    }
}

