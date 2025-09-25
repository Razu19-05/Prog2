#include "src/Heroe.hpp"

int main() {
    ifstream input("heroes.csv",ios::in);
    if(!input.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    ofstream output("reporte.txt",ios::out);
    // Heroe heroe;
    Heroe heroes[10];
    int cant = 0;
    while (true) {
        Heroe h;
        h.cargar_info(input);
        if (input.eof())break;
        heroes[cant] = h;
        cant++;
    }
    cout<<cant<<endl;
    for (int i = 0; i < cant; i++) {
        heroes[i].mostrar_info(output);
    }
    return 0;
}