#include "src/Functions.hpp"

int main() {
    char*** users;
    int** datesAges;
    loadUsers("Data/usuarios.csv",users,datesAges);
    displayReport("Report/reportUsers.txt",users,datesAges);
    int** idsDates;
    char*** posts;
    char*** mentions;
    loadPosts("Data/publicaciones.csv",idsDates,posts,mentions);
    displayPosts("Report/reporte_completo.txt",users,datesAges,idsDates,posts,mentions);

    return 0;
}