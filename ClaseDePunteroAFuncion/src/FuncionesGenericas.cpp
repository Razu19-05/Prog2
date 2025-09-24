
#include "FuncionesGenericas.hpp"

void generarLista(void *&pedidos1) {
    void ** lista = new void*[2]{};
    lista[FIRST]=nullptr;
    lista[LAST]=nullptr;
    pedidos1 = lista;
}

bool listaVacia(void *pedidos1) {
    void** lista = (void**) pedidos1;
    return lista[FIRST]== nullptr and lista[LAST]== nullptr;
}

//insertar Al final
void insertar(void *&pedidos1, void* dato) {
    void **lista = (void**)pedidos1;
    void **nuevo = new void*[2]{};
    void **ultimo;
    nuevo[DATO]=dato;
    nuevo[SIGUIENTE] = nullptr;
    if (listaVacia(pedidos1)) {
        lista[FIRST]=nuevo;
        lista[LAST]=nuevo;
    }else {
        ultimo = (void**) lista[LAST];
        ultimo[SIGUIENTE] = nuevo;
        lista[LAST]=nuevo;
    }
}

void crearLista(void *&pedidos1,void*(*lee)(ifstream &), const char* nameFile) {
    ifstream input (nameFile, ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << nameFile << endl;
        exit(1);
    }
    void* dato;
    generarLista(pedidos1);
    while (true) {
        dato = lee(input);
        if (dato == nullptr) break;
        insertar(pedidos1, dato);
    }
}

void imprimirLista(void *pedidos1, void (*imprime)(ofstream &, void *), const char *nameFile) {
    ofstream output (nameFile, ios::out);
    void **recorrido, *dato;
    void ** lista = (void**) pedidos1;
    recorrido = (void**) lista[FIRST];//inicio del recorrido
    while (recorrido) {
        dato = recorrido[DATO];
        imprime(output, dato);
        recorrido = (void**) recorrido[SIGUIENTE];
    }
}

void unirListas(void *pedidos1,void *pedidos2,void *&pedidosFinal,int (*cmp)(void *, void *)) {

}