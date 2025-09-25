//
// Created by Huarote on 24/09/2025.
//

#include "Heroe.hpp"

Heroe::Heroe() {
    cout << "Constructor por Defecto" << endl;
    hp = 0;
    id = nullptr;
    nombre = nullptr;
    posX = 0;
    posY = 0;
}

void Heroe::get_id(char*id) const {
    if (this->id == nullptr) id[0] = '\0'; //si no hay nada en id ent devuelve un nada 0
    else strcpy(id, this->id); //si ID tiene un valor ent lo copias y devuelves la varibale;
}

void Heroe::set_id(const char *id) {
    if (this->id != nullptr) delete this->id;//para borrar todo lo que no sea nullptr
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id);//le doy el valor de id a mi variable privada
}

void Heroe::get_nombre(char* nombre) const {
    if (this->nombre == nullptr) nombre[0] = '\0';
    else strcpy(nombre, this->nombre);
}


void Heroe::set_nombre(const char *nombre) {
    if (this->nombre != nullptr) delete this->nombre;//para borrar todo lo que no sea nullptr
    this->nombre = new char[strlen(nombre) + 1];
    strcpy(this->nombre, nombre);//le doy el valor de id a mi variable privada
}

int Heroe::get_hp() const {
    return hp;
}

void Heroe::set_hp(int hp) {
    this->hp = hp;
}

double Heroe::get_fuerza() const {
    return fuerza;
}

void Heroe::set_fuerza(double fuerza) {
    this->fuerza = fuerza;
}

double Heroe::get_defensa() const {
    return defensa;
}

void Heroe::set_defensa(double defensa) {
    this->defensa = defensa;
}

int Heroe::get_pos_x() const {
    return posX;
}

void Heroe::set_pos_x(int pos_x) {
    posX = pos_x;
}

int Heroe::get_pos_y() const {
    return posY;
}

void Heroe::set_pos_y(int pos_y) {
    posY = pos_y;
}
void Heroe::mostrar_info(ofstream &output) {
    output << "ID: " << id << endl;
    output << "Nombre: " << nombre << endl;
    output << "HP: " << hp << endl;
    output << "FUERZA: " << fuerza << endl;
    output << "DEFENSA: " << defensa << endl;
    output << "POSX: " << posX << endl;
    output << "POSY: " << posY << endl;
}

void Heroe::cargar_info(ifstream& input) {
    // H001,Ayla,100,15,5,1,0
    char buffer[20];
    input.getline(buffer, 20,',');
    set_id(buffer);
    input.getline(buffer, 20,',');
    set_nombre(buffer);
    input>>hp;
    input.get();
    input>>fuerza;
    input.get();
    input>>defensa;
    input.get();
    input>>posX;
    input.get();
    input>>posY;
    input.get();
}


