#include "FuncionesGenericas.hpp"
char *leerCadena(ifstream &input, char delim) {
    char cadena[100], *cad;
    input.getline(cadena, 100, delim);
    cad = new char[strlen(cadena) + 1];
    strcpy(cad, cadena);
    return cad;
}

void *leerRegistro(ifstream &input) {
    // 20196975,Hijar Pairazaman Jenny Delicia
    void **registro;
    int codigo, *ptrCodigo;
    char *nombre;
    input >> codigo;
    if (input.eof()) return nullptr;
    input.get();
    nombre = leerCadena(input,'\n');
    ptrCodigo = new int (codigo);
    registro = new void*[4]{};
    registro[CODIGO] = ptrCodigo;
    registro[NOMBRE] = nombre;
    registro[PROMEDIO] = nullptr;
    registro[CURSOS] = nullptr;
    return registro;
}

void reservarMemoria(void **&alumnosArreglo,int &n, int &capacidad) {
    capacidad += INCREMENTO;
    if (alumnosArreglo == nullptr) {
        alumnosArreglo = new void*[capacidad]{};
        n = 1;
    }else {
        void** aux = new void*[capacidad]{};
        for (int i = 0; i < n; i++) aux[i] = alumnosArreglo[i];
        delete alumnosArreglo;
        alumnosArreglo = aux;
    }
}

void cargarAlumnos(void* &alumnos,const char* fileName) {
    ifstream input(fileName,ios::in);
    if(!input.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    //memoria por Incremento
    int cantAlumno = 0, capacidad = 0;
    void** alumnosArreglo = nullptr, *registro;
    while (true) {
        registro = leerRegistro(input);
        if (input.eof()) break;
        if (cantAlumno == capacidad) reservarMemoria(alumnosArreglo,cantAlumno,capacidad);
        alumnosArreglo[cantAlumno-1] = registro;
        cantAlumno++;
    }
    alumnos = alumnosArreglo;
}

bool sonIguales(int codigo, void* alumno) {
    void **registro = (void **)alumno;
    int *ptrCodigo = (int*)registro[CODIGO];
    return codigo == *ptrCodigo;
}

int buscarPosicion(int codigo,void **alumnosArreglo) {
    for (int i = 0; alumnosArreglo[i]; i++)
        if (sonIguales(codigo,alumnosArreglo[i]))return i;
    return -1;
}

void* leerCurso(ifstream &input) {
    // 20189596,MEC289,17
    char *codigo;
    int *ptrNota, nota;
    void** registro;
    codigo = leerCadena(input,',');
    input>>nota;
    ptrNota = new int(nota);
    registro = new void*[2]{};
    registro[CODIGOCURSO] = codigo;
    registro[NOTA] = ptrNota;
    return registro;
}

void aumentar_memoria(void*&cursos, int &n, int&c){
    void **cursos_arreglo = (void**)cursos;
    c+=INCREMENTO;
    if(cursos_arreglo == nullptr){
        cursos_arreglo = new void*[c]{};
        n = 1;
    } else{
        void **aux = new void*[c]{};
        for(int i = 0; i<n; i++)
            aux[i] = cursos_arreglo[i];
        delete cursos_arreglo;
        cursos_arreglo = aux;
    }
    cursos = cursos_arreglo;
}

void agregar_curso(void* curso, void*cursos, int n){
    void ** arr_cursos = (void**)cursos;
    arr_cursos[n] = curso;
}

void colocarCurso(ifstream &input,void* alumno,int &cantidad,int &capacidad) {
    void **registro = (void **)alumno;
    void *curso;
    curso = leerCurso(input);
    if (cantidad == capacidad) aumentar_memoria (registro[CURSOS],cantidad,capacidad);
    agregar_curso(curso, registro[CURSOS], cantidad - 1);
    cantidad++;
}

void cargarCursos(void* &alumnos,const char* fileName) {
    ifstream input(fileName,ios::in);
    if(!input.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
    void** alumnosArreglo = (void**) alumnos;
    int codigo, pos, nCursos[50]{}, capacidad[50]{};
    while (true) {
        input>>codigo;
        if (input.eof())break;
        input.get();
        pos = buscarPosicion(codigo,alumnosArreglo);
        if (pos == -1) continue;
        colocarCurso(input,alumnosArreglo[pos],nCursos[pos],capacidad[pos]);
    }
}

void imprimirCursos(void* curso,ofstream &output) {
    void** registro = (void**)curso;
    char* ptrCodigo = (char*) registro[CODIGOCURSO];
    int* nota = (int*) registro[NOTA];
    output<<left<<setw(8)<<ptrCodigo;
    output<<setw(4)<<*nota<<endl;
}

void imprimirNotas(void* cursos, ofstream &output) {
    void** cursosArreglos = (void**)cursos;
    for(int i = 0; cursosArreglos[i]; i++)
        imprimirCursos(cursosArreglos[i],output);
}

void imprimirAlumno(void* alumno,ofstream &output) {
    void** registro = (void**)alumno;
    int *ptrCodigo = (int*)registro[CODIGO];
    char* ptrNombre = (char*)registro[NOMBRE];
    double *ptrPromedio = (double*)registro[PROMEDIO];
    output<<fixed<<setprecision(2);
    output << left << setw(10) << *ptrCodigo;
    output << left << setw(50) << ptrNombre ;
    output << left << setw(10) << *ptrPromedio<<endl;
    if(registro[CURSOS])
        imprimirNotas(registro[CURSOS], output);
}

void probarCarga(void* alumnos,const char* fileName) {
    ofstream output(fileName,ios::out);
    void ** alumnosArreglos = (void**)alumnos;
    for(int i = 0; alumnosArreglos[i]; i++)
        imprimirAlumno(alumnosArreglos[i],output);
}


void* calcularPromedio (void* cursos) {
    void** cursosArreglo = (void**)cursos;
    double *promedio;
    int cantidad = 0, *ptrNota, nota, suma = 0;
    for (int i = 0; cursosArreglo[i]; i++) {
        void** curso = (void**)cursosArreglo[i];
        ptrNota = (int*) curso[NOTA];
        nota = *ptrNota;
        suma += nota;
        cantidad ++;
    }
    promedio = new double((double)suma/cantidad);
    return promedio;
}

void calcularPromedios(void *&alumno) {
    void** registro = (void**)alumno;
    registro[PROMEDIO] = calcularPromedio (registro[CURSOS]);
}

void cargarPromedios(void *&alumnos) {
    void** alumnosArreglos = (void**)alumnos;
    for(int i = 0; alumnosArreglos[i]; i++)
        calcularPromedios(alumnosArreglos[i]);
}

void cambiar(void *&a,void *&b) {
    void * aux;
    aux = a;
    a = b;
    b = aux;
}

bool comparar(void* alumnoI,void* alumnoIzq) {
    void** arregloAlumnoI = (void**)alumnoI;
    void** arregloAlmnoIzq = (void**)alumnoIzq;
    int *ptrCodigo1 = (int*)arregloAlumnoI[CODIGO];
    int *ptrCodigo2 = (int*)arregloAlmnoIzq[CODIGO];
    return (*ptrCodigo1 < *ptrCodigo2);
}

void qsort(void** &alumnosArreglo,int izq,int der) {
    int limite, medio;
    if(izq>der) return;
    medio = (izq+der)/2;
    cambiar(alumnosArreglo[izq],alumnosArreglo[medio]);
    limite = izq;
    for (int i = izq + 1; i <= der; ++i) {
        if (comparar(alumnosArreglo[i],alumnosArreglo[izq]))
            cambiar(alumnosArreglo[i],alumnosArreglo[++limite]);
    }
    cambiar(alumnosArreglo[izq],alumnosArreglo[limite]);
    qsort(alumnosArreglo,izq,limite-1);
    qsort(alumnosArreglo,limite+1,der);

}

void ordenamiento(void *&alumnos) {
    void** alumnosArreglo = (void**)alumnos;
    int cant = 0;
    for(int i = 0; alumnosArreglo[i]; i++) cant++;
    qsort(alumnosArreglo,0,cant-1);
}