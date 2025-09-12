
#include "Functions.hpp"

int readInt(ifstream &input) {
    int a;
    input >> a;
    return a;
}

double readDouble(ifstream &input) {
    double a;
    input >> a;
    return a;
}

char* readStr(ifstream &input,char delim) {
    char buffer[100], *str;
    input.getline(buffer, 100, delim);
    str = new char[strlen(buffer) + 1]{};
    strcpy(str, buffer);
    return str;
}

char *assign_str(char* source) {
    char *str;
    str = new char[strlen(source) + 1]{};
    strcpy(str, source);
    return str;
}

int lookupInt(int * dates ,int date) {
    for (int i = 0; dates[i]; i++)
        if (dates[i] == date) return i;
    return -1;
}