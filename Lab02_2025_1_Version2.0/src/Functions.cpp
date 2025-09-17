
#include "Functions.hpp"

int buscarDni(int dni,int * dnis) {
    for (int i = 0; dnis[i]; i++) if (dnis[i] == dni) return i;
    return -1;
}

void reservarMemoria(char** &placas,int &cantidad,int &capacidad) {
    capacidad += INCREMENTO;
    if (placas == nullptr) {
        placas = new char*[capacidad]{};
        cantidad = 1;
    }else {
        char** aux = new char *[capacidad]{};
        for (int i = 0; i < cantidad; i++)
            aux[i] = placas[i];
        delete placas;
        placas = aux;
    }
}

void cargarPlaca(ifstream &input,char** &placas,int &capacidad,int &cantidad) {
    char * placa, car;
    int null;
    bool existe = false;
    placa = leerNombre(input,';');
    input>>null>>car>>null>>car>>null>>car>>null;
    if (capacidad == cantidad) reservarMemoria(placas,cantidad,capacidad);
    //buscar si la placa existe
    for (int i = 0; i< cantidad -1; i++)
        if (strcmp(placa, placas[i])==0) existe = true;
    if (existe) return;
    placas[cantidad-1] = placa;
    cantidad++;
}

void leerFaltas(ifstream &input,Faltas &faltas, int *cantidades) {
    // 81485316;J5T-691;24/12/2020;128
    int dni, pos;
    while (true) {
        input>>dni;
        if (input.eof()) break;
        input.get();
        pos = buscarDni(dni,faltas.conductores.dnis);
        if (pos == - 1)continue;
        cargarPlaca(input,faltas.placas[pos],faltas.capacidades[pos],cantidades[pos]);
    }
}

void cargarFaltasDeLosConductores(Faltas &faltas) {
    faltas.conductores += "Data/conductores.csv";
    faltas.infracciones += "Data/infracciones.csv";
    ifstream input("Data/faltas.csv",ios::in);
    if (!input.is_open()) {
        cout << "Error opening file " << __FILE__ << "\n";
        exit(1);
    }
    int cantidadMax = faltas.conductores.cantidad;
    int cantidades[cantidadMax]{};
    faltas.placas = new char**[cantidadMax]{};
    for (int i = 0; i < cantidadMax; i++) faltas.placas[i] = nullptr;
    faltas.capacidades = new int [cantidadMax]{};
    leerFaltas(input,faltas,cantidades);
}

void imprimirLineas(ofstream &output,char car) {
    for (int i = 0; i<=150; i++) output << car;
    output << endl;
}

int contarPlacas (char **datos) {
    int cant = 0;
    int i = 0;
    while (true) {
        if (datos==nullptr)break;
        if (datos[i]==nullptr) break;
        i++;
        cant ++;
    }
    return cant;
}

void imprimirFaltasDeLosConductores(Faltas faltas,const char* nameFile) {
    ofstream output(nameFile,ios::out);
    imprimirLineas(output,'=');
    output<<right<<setw(6)<<"DNI"<<setw(12)<<"CLIENTE"<<setw(50)<<"CANT VEHICULOS"<<endl;
    imprimirLineas(output,'-');
    for (int i = 0; i< faltas.conductores.cantidad; i++) {
        char **datoPlaca = faltas.placas[i];
        int  cantidad = contarPlacas (datoPlaca);
        output<<left<<setw(11)<<faltas.conductores.dnis[i]<<setw(50)<<faltas.conductores.nombres[i]<<right<<cantidad<<endl;
    }
}