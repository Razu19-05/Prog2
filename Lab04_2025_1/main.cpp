#include "src/BibliotecaGenerica.hpp"
#include "src/BibliotecaEnteros.hpp"
#include "src/BibliotecaRegistro.hpp"

int main() {
    void *lista;
    // crearLista(lista,leeNum,clasificaNum,"numeros.txt");
    // imprimeLista(lista,imprimeNum,"RepNum.txt");
    crearLista(lista,leeRegistro,clasificaRegistro,"RegistroDeFaltas1.csv");
    imprimeLista(lista,imprimeRegistro,"RepRegistro.txt");
    return 0;
}