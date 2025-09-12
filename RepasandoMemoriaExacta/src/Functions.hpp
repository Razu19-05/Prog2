
#ifndef REPASANDOMEMORIAEXACTA_FUNCTIONS_HPP
#define REPASANDOMEMORIAEXACTA_FUNCTIONS_HPP
#include "Utils.hpp"
#include "../structs/Structs.hpp"

int readInt(ifstream &input);

double readDouble(ifstream &input) ;

char* readStr(ifstream &input,char delim);

char *assign_str(char* source) ;

int lookupInt(int * dates ,int date);

#endif //REPASANDOMEMORIAEXACTA_FUNCTIONS_HPP