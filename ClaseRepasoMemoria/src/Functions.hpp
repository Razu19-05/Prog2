

#ifndef CLASEREPASOMEMORIA_FUNCTIONS_HPP
#define CLASEREPASOMEMORIA_FUNCTIONS_HPP
#include "Utils.hpp"

void loadUsers(const char* nameFile,char*** &users,int** &datesAges) ;
void displayReport(const char* nameFile,char*** users,int** datesAges);
void loadPosts(const char* nameFile,int** &idsDates,char*** &posts,char*** &mentions);
void displayPosts(const char *nombreArchivo, char ***usuarios,
                      int **fechasEdades,
                      int **idsFechas, char ***publicaciones,
                      char ***menciones);

#endif //CLASEREPASOMEMORIA_FUNCTIONS_HPP