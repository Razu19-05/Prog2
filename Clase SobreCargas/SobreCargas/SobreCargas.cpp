#include  "SobreCargas.hpp"

ostream & operator << (ostream & out, const struct Persona & p) {
    out<<"tengo hambre"<<endl;
    out<<p.dni<<endl;
    out<<p.nombre<<endl;
    out<<p.sueldo<<endl;
    return out;
}

istream & operator >> (istream & in, struct Persona& p){
    cout<<"Ingrese Datos"<<endl;
    in>>p.dni;
    in>>p.nombre;
    in>>p.sueldo;
    return in;
}

void operator += (struct Persona& p, double porcentaje) {
    p.sueldo += (1+p.sueldo/porcentaje);
}

//------------------------------------------------------------------

int f (int a) {
    return a+10;
}

int f(int a, int b) {
    return a+b;
}