#include "Functions.hpp"
char* readStr(ifstream &input,char delim) {
    char buffer[MAX_PALABRAS], *cad;
    input.getline(buffer,MAX_PALABRAS,delim);
    cad = new char[strlen(buffer)+1];
    strcpy(cad,buffer);
    return cad;
}

char** readUser(ifstream &input) {
    // @jperez,Juan Perez,juan.perez@pucp.edu.pe,FCI,
    char* cuenta = readStr(input,',');
    if (input.eof())return nullptr;
    char* nombre = readStr(input,',');
    char* correo = readStr(input,',');
    char* facultad = readStr(input,',');
    char **registerUser = new char*[4]{};
    registerUser[CUENTA] = cuenta;
    registerUser[NOMBRE] = nombre;
    registerUser[CORREO] = correo;
    registerUser[FACULTAD] = facultad;
    // cout<<registerUser[CUENTA]<<"  "<<registerUser[NOMBRE]<<"  "<<registerUser[CORREO]<<"  "<<registerUser[FACULTAD]<<"  ";
    return registerUser;
}

int* readDateAge(ifstream &input) {
    // 2020-12-12,22
    int year, month, day, age;
    char car;
    input>>year>>car>>month>>car>>day>>car>>age;
    int fecha = year*10000+month*100+day*10;
    int* registerDateAge = new int[2]{};
    registerDateAge[FECHA] = fecha;
    registerDateAge[EDAD] = age;
    // cout<<registerDateAge[FECHA]<<"  "<<registerDateAge[EDAD]<<endl;
    return registerDateAge;
}

void incremetarMemoria(char*** &users,int** &datesAges,int &capacity,int &nUsers) {
    capacity += INCREMENTO;
    if (users == nullptr and datesAges == nullptr ) {
        users = new char**[capacity]{};
        datesAges = new int*[capacity]{};
        nUsers = 1;
    }else {
        char*** aux = new char**[capacity]{};
        int** aux1 = new int*[capacity]{};
        for (int i = 0; i < nUsers; i++) {
            aux[i] = users[i];
            aux1[i] = datesAges[i];
        }
        delete users;
        delete datesAges;
        users = aux;
        datesAges = aux1;
    }
}

void insertarOrdenado(char **user,int *dateAge,char*** &users,int** &datesAges,int n) {
    int i;
    int *aux;//por fechas;
    for (i = n-1; i >= 0; i--) {
        aux = datesAges[i];
        if (aux[FECHA] <= dateAge[FECHA]) break;
        users[i+1] = users[i];
        datesAges[i+1] = datesAges[i];
    }
    users[i+1] = user;
    datesAges[i+1] = dateAge;
}

void loadUsers(const char* nameFile,char*** &users,int** &datesAges) {
    ifstream inputUsers(nameFile,ios::in);
    if (!inputUsers.is_open()) {
        cout << "Error opening file " << nameFile << endl;
        exit(1);
    }
    //lecturaPorIncremento
    int nUsers = 0, capacity = 0;
    char** user;
    int* dateAge;
    users = nullptr;
    datesAges = nullptr;
    while (true) {
        user = readUser(inputUsers);
        if (user == nullptr) break;
        dateAge = readDateAge(inputUsers);
        if (nUsers == capacity) incremetarMemoria(users,datesAges,capacity,nUsers);
        insertarOrdenado(user,dateAge,users,datesAges,nUsers-1);
        nUsers++;
    }
}

void imprimir_fecha(ofstream &output, int fecha) {
    const int anho = fecha / 10000;
    const int mes = (fecha / 100) % 100;
    const int dia = fecha % 100;
    output << (dia / 10) << (dia % 10) << "-" << (mes / 10) << (mes % 10) << "-" << (anho / 1000) % 10
           << (anho / 100) % 10 << (anho / 10) % 10 << anho % 10;
}

void printUser(ofstream& output,int* registerDateAge,char **registerUser) {
    const char *cuenta = registerUser[CUENTA];
    const char *nombre = registerUser[NOMBRE];
    const char *correo = registerUser[CORREO];
    const char *facultad = registerUser[FACULTAD];
    const int fecha = registerDateAge[FECHA];
    const int edad = registerDateAge[EDAD];
    output << setfill('=') << setw(40) << "" << setfill(' ') << endl;
    output << "REPORTE DE USUARIO" << endl;
    output << setfill('=') << setw(40) << "" << setfill(' ') << endl;

    output << left << setw(10) << "Cuenta: "  << cuenta << endl
           << setw(10) << "Nombre:" << setw(20) << nombre << endl
           << setw(10) << "Correo:" << setw(25) << correo << endl
           << setw(10) << "Facultad:" << setw(15) << facultad << endl
           << setw(10) << "Fecha: ";
    imprimir_fecha(output, fecha);
    output << endl;
    output << setw(10) << "Edad:" << setw(3) << edad << endl;
}

void displayReport(const char* nameFile,char*** users,int** datesAges) {
    ofstream output(nameFile,ios::out);
    for (int i = 0; users[i]; i++) {
        char** registerUser = users[i];
        int* registerDateAge = datesAges[i];
        printUser(output,registerDateAge,registerUser);
    }
}

int* readIdDate(ifstream &input) {
    // 1,2024-02-02,
    int id, year, month, day, date;
    char car;
    input >> id >>car >> year >> car >> month >> car >> day >> car;
    if (input.eof())return nullptr;
    date = year * 10000 + month * 100 + day;
    int *registerIdDate = new int[2]{};
    registerIdDate[ID] = id;
    registerIdDate[FECHA_PUB] = date;
    return registerIdDate;
}

void readMention(ifstream &input,char** &mention) {
    // @mlopez @rrojas]
    int cantidad = 0;
    char* bufferArregki[10];
    char buffer[20], *ment;
    while (true) {
        input>>buffer;
        ment = new char[strlen(buffer) + 1];
        strcpy(ment,buffer);
        bufferArregki[cantidad++] = ment;
        if (input.get()!=']')break;
    }
    mention = new char*[cantidad+1]{};
    for (int i = 0; i < cantidad; i++) {
        mention[i] = bufferArregki[i];
    }

}

void readPostMention(ifstream &input,char** &post,char** &mention) {
    // @psalazar,[@jperez] Realizando un estudio sobre redes neuronales.
    char *cuenta = readStr(input,',');
    input.get();
    readMention(input,mention);
    input.get();
    char *comentario = readStr(input,'\n');
    post = new char*[2]{};
    post[CUENTA_PUB] = cuenta;
    post[TEXTO] = comentario;
}

void incremetarMemoria(int** &idsDates,char*** &posts,char*** &mentions,int &nPosts,int &capacity) {
    capacity += INCREMENTO;
    if (posts == nullptr and mentions == nullptr and idsDates == nullptr) {
        posts = new char**[capacity]{};
        mentions = new char**[capacity]{};
        idsDates = new int*[capacity]{};
        nPosts = 1;
    }else {
        char*** aux = new char**[capacity]{};
        char*** aux2 = new char**[capacity]{};
        int** aux3 = new int*[capacity]{};
        for (int i = 0; i < nPosts; i++) {
            aux[i] = posts[i];
            aux2[i] = mentions[i];
            aux3[i] = idsDates[i];
        }
        delete posts;
        delete mentions;
        delete idsDates;
        posts = aux;
        mentions = aux2;
        idsDates = aux3;
    }
}

void insertarOrdenado(int **&idsDates,char*** &posts,char*** &mentions,int num,int* idDate,char **post,char** mention) {
    int i;
    int * aux;
    for (i= num - 1 ; i>=0;i--) {
        aux = idsDates[i];
        if (aux[FECHA_PUB] <= idDate[FECHA_PUB]) break;
        posts[i+1] = posts[i];
        mentions[i+1] = mentions[i];
        idsDates[i+1] = idsDates[i];
    }
    posts[i+1] = post;
    mentions[i+1] = mention;
    idsDates[i+1] = idDate;
}

void loadPosts(const char* nameFile,int** &idsDates,char*** &posts,char*** &mentions) {
    ifstream inputPosts(nameFile,ios::in);
    if (!inputPosts.is_open()) {
        cout << "Error opening file " << nameFile << endl;
        exit(1);
    }
    //lectura por incrementos
    int nPosts = 0, capacity = 0;
    int* idDate;
    char** post;
    char** mention;
    idsDates = nullptr;
    posts = nullptr;
    mentions = nullptr;
    while (true) {
        idDate = readIdDate(inputPosts);
        if (idDate == nullptr)break;
        readPostMention(inputPosts,post,mention);
        if (nPosts == capacity) incremetarMemoria(idsDates,posts,mentions,nPosts,capacity);
        insertarOrdenado(idsDates,posts,mentions,nPosts-1,idDate,post,mention);
        nPosts++;
    }
}

void imprimirPubUsuario(ofstream &archivo, char **publicacion, int *idFecha) {
    int fecha = idFecha[FECHA_PUB];
    char *texto = publicacion[TEXTO];

    archivo << "  - [";
    imprimir_fecha(archivo, fecha);
    archivo << "] " << texto << endl;
}

bool mencionadoEnPublicacion(char *cuentaUsuario, char **mencionesPub) {
    for (int i = 0; mencionesPub[i]; i++) {
        char *cuenta = mencionesPub[i];

        if (strcmp(cuenta, cuentaUsuario) == 0) {
            return true;
        }
    }
    return false;
}

void imprimirMencion(ofstream &archivo, int *idFecha, char **publicacion, char *cuentaUsuario) {
    int fecha = idFecha[FECHA_PUB];
    const char *cuentaPublicacion = publicacion[CUENTA_PUB];
    const char *textoPublicacion = publicacion[TEXTO];

    archivo << "  - En [";
    imprimir_fecha(archivo, fecha);
    archivo << "], " << cuentaPublicacion
            << " publicó: \"" << textoPublicacion << "\""
            << " y mencionó a " << cuentaUsuario << endl;
}

void imprimir_menciones_usuario(ofstream &archivo, char *cuentaUsuario, int **idsFechas,
                                char ***publicaciones, char ***menciones) {
    archivo << setfill('-') << setw(40) << "" << setfill(' ') << endl;
    archivo << "PUBLICACIONES DONDE FUE MENCIONADO" << endl;
    archivo << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    for (int i = 0; publicaciones[i]; i++) {
        char **mencionesPub = menciones[i];
        if (mencionadoEnPublicacion(cuentaUsuario, mencionesPub)) {
            int *idFecha = idsFechas[i];
            char **publicacion = publicaciones[i];
            imprimirMencion(archivo, idFecha, publicacion, cuentaUsuario);
        }
    }
}


void imprimir_publicaciones_usuario(ofstream &archivo, char *cuentaUsuario,
                                    int **idsFechas,
                                    char ***publicaciones) {
    archivo << setfill('-') << setw(40) << "" << setfill(' ') << endl;
    archivo << "PUBLICACIONES REALIZADAS" << endl;
    archivo << setfill('-') << setw(40) << "" << setfill(' ') << endl;

    for (int i = 0; idsFechas[i]; i++) {
        char **publicacion = publicaciones[i];
        char *cuenta = publicacion[CUENTA_PUB];

        if (strcmp(cuenta, cuentaUsuario) == 0) {
            int *idFecha = idsFechas[i];
            imprimirPubUsuario(archivo, publicacion, idFecha);
        }
    }
}

void displayPosts(const char *nombreArchivo,
                  char ***usuarios, int **fechasEdades,
                  int **idsFechas, char ***publicaciones, char ***menciones) {
    ofstream archivo(nombreArchivo, ios::out);

    for (int i = 0; usuarios[i]; i++) {
        archivo << setfill('*') << setw(60) << "" << setfill(' ') << endl;
        archivo << "REPORTE COMPLETO DE USUARIO " << (i+1) << endl;
        archivo << setfill('*') << setw(60) << "" << setfill(' ') << endl;

        char **usuario = usuarios[i];
        int *fechasEdad = fechasEdades[i];
        char *cuentaUsuario = usuario[CUENTA];

        // Datos generales
        printUser(archivo, fechasEdad, usuario);

        // Publicaciones propias
        imprimir_publicaciones_usuario(archivo, cuentaUsuario, idsFechas, publicaciones);

        // Publicaciones donde fue mencionado
        imprimir_menciones_usuario(archivo, cuentaUsuario, idsFechas, publicaciones, menciones);

        archivo << endl << endl;
    }
}
