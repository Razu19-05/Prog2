//
// Created by Huarote on 24/09/2025.
//

#ifndef ENTENDIENDOPOO_FIRSTTIME_HEROE_HPP
#define ENTENDIENDOPOO_FIRSTTIME_HEROE_HPP
#include "Utils.hpp"

class Heroe {
public:
    Heroe();

    void get_id(char* id) const;
    void set_id(const char *id);
    void get_nombre(char* nombre) const;
    void set_nombre(const char *nombre);
    int get_hp() const;
    void set_hp(int hp);
    double get_fuerza() const;
    void set_fuerza(double fuerza);
    double get_defensa() const;
    void set_defensa(double defensa);
    int get_pos_x() const;
    void set_pos_x(int pos_x);
    int get_pos_y() const;
    void set_pos_y(int pos_y);

    void cargar_info(ifstream& input);
    void mostrar_info(ofstream &output);

    private:
        char *id;
        char *nombre;
        int hp;
        double fuerza;
        double defensa;
        int posX;
        int posY;
};


#endif //ENTENDIENDOPOO_FIRSTTIME_HEROE_HPP