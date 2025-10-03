#include "BibliotecaConductores.hpp"

char *leerCadena(ifstream &input, char delim) {
    char *cadena, buffer[200];
    input.getline(buffer, 200, delim);
    cadena = new char[strlen(buffer) + 1];
    strcpy(cadena, buffer);
    return cadena;
}

void *leeConductores(ifstream &input) {
    // 12270502,CUEVA FUENTES CINTHIA DELIA
    int *licencia = new int();
    char *nombre;
    input>>*licencia;
    if (input.eof())return nullptr;
    input.get();
    nombre = leerCadena(input,'\n');
    //registro inicial
    void **registro = new void*[4]{};
    registro[LICENCIA] = licencia;
    registro[NOMBRE] = nombre;
    registro[ARR] = nullptr;
    void **lista = new void*[1]{};
    registro[LISTA] = lista;
    //registro Aux
    return registro;
}

int cmpConductores (void* dato, void*registro) {
    void** _dato = (void**)dato;
    void** _registro = (void**)registro;
    int *licencia1 = (int*)_dato[LICENCIA];
    int *licencia2 = (int*)_dato[LICENCIA];
    return (*licencia1) - (*licencia2);
}
void* buscaListaConductores (void* lista, void* registro) {
    return lista;
}

int buscarPosicion (int licencia,void ** &recorrido) {
    int i=0;
    while (recorrido != nullptr) {
        void **registro = (void**)recorrido[DATO];
        int *ptrLicencia = (int*)registro[LICENCIA];
        if (licencia == *ptrLicencia) break;
        recorrido = (void**)recorrido[SIGUIENTE];
        i++;
    }
    return i;

}

void aumentarMemoria(void **&arr, int &n,int &cap) {
    cap += INCREMENTO;
    if (arr == nullptr) {
        arr = new void*[cap]{};
        n = 1;
    }else {
        void **aux = new void *[cap]{};
        for (int i = 0; i < n; i++)
            aux[i] = arr[i];
        delete []arr;
        arr = aux;
    }
}

void cargarUnidades (void *&lista,const char* fileName) {
    ifstream input(fileName,ios::in);
    if(!input.is_open()) {
        cout << "Erro ao abrir arquivo " << fileName << endl;
        exit(1);
    }
    // 12270502,P7T-999
    int licencia,pos;
    char* placa;
    void **_lista = (void**)lista;
    int cantidad[200]{},capacidad[200]{};
    while (true) {
        input>>licencia;
        if (input.eof())break;
        input.get();
        placa = leerCadena(input,'\n');
        void **recorrido = (void**)_lista[INICIO];
        pos = buscarPosicion (licencia,recorrido);
        if (recorrido!=nullptr) {
            void**registro = (void**)recorrido[DATO];
            void** arr = (void**)registro[ARR];
            if (cantidad[pos]==capacidad[pos]) {
                aumentarMemoria(arr, cantidad[pos],capacidad[pos]);
                registro[ARR] = arr;
            }
            arr[cantidad[pos] - 1] = placa;
            cantidad[pos]++;
        }
    }
}

void imprimeConductores(ofstream& output, void* registro) {
    void **_dato = (void**) registro;
    output << left << setw(12) << *(int *) _dato[LICENCIA] << (char *) _dato[NOMBRE] << endl;
    output << "PLACAS: ";
    void **arr = (void**) _dato[ARR];
    for (int i = 0; arr[i]; i++) {
        output << (char*) arr[i] << ' ';
    }
    output<<endl;
    void **lista = (void**) _dato[LISTA];
    void **recorrido = (void**) lista[INICIO];
    if (lista[INICIO] != nullptr) {
        output << setw(15) << "Fecha" << setw(12) << "Placa" << "Infraccion" << endl;
        int aa, mm, dd;
        for (int i = 0; recorrido; i++) {
            void **data = (void**) recorrido[DATO];
            int fecha = *(int *) data[FECHA];
            //03042023
            dd=fecha/1000000;
            fecha=fecha%1000000;
            mm=fecha/10000;
            aa=fecha%10000;
            output << right << setfill('0') << setw(4) << aa << '/' << setw(2) << mm << '/' << setw(2) << dd << setfill(' ') << left
                    << setw(5) << ' ' << setw(12) << (char *) data[PLACA] << *(int *) data[TIPO] << endl;
            recorrido = (void **) recorrido[SIGUIENTE];
        }
    }else{
        output<<"ESTE CONDUCTOR NO TIENE INFRACCIONES"<<endl;
    }
}