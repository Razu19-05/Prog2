

#ifndef LAB02_2025_1_VERSION2_0_OVERLOADS_HPP
#define LAB02_2025_1_VERSION2_0_OVERLOADS_HPP
#include "Utils.hpp"
#include "../struct/Structs.hpp"

void operator += (Conductores &conductores,const char*nameFile);
void operator += (Infracciones &infracciones,const char*nameFile);
char * leerNombre(ifstream &input,char delim) ;

#endif //LAB02_2025_1_VERSION2_0_OVERLOADS_HPP