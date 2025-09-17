

#ifndef LAB02_2025_1_VERSION2_0_STRUCTS_HPP
#define LAB02_2025_1_VERSION2_0_STRUCTS_HPP

struct Conductores {
    int *dnis;
    char ** nombres;
    int cantidad;
};

struct Infracciones {
    int *codigos;
    char ** descripciones;
    char ** tipos;
    double * valores;
    int cantidad;
};

struct Faltas {
    Conductores conductores;
    Infracciones infracciones;
    char***placas;
    int *capacidades;
};

#endif //LAB02_2025_1_VERSION2_0_STRUCTS_HPP