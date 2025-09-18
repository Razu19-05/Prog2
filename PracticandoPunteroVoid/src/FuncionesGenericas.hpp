#ifndef PRACTICANDOPUNTEROVOID_FUNCIONESGENERICAS_HPP
#define PRACTICANDOPUNTEROVOID_FUNCIONESGENERICAS_HPP
#include "Utils.hpp"
char *leerCadena(ifstream &input, char delim);

void *leerRegistro(ifstream &input);
void reservarMemoria(void **&alumnosArreglo,int &n, int &capacidad);
void cargarAlumnos(void* &alumnos,const char* fileName);

bool sonIguales(int codigo, void* alumno);
int buscarPosicion(int codigo,void **alumnosArreglo);
void* leerCurso(ifstream &input);
void aumentar_memoria(void*&cursos, int &n, int&c);
void agregar_curso(void* curso, void*cursos, int n);
void colocarCurso(ifstream &input,void* alumno,int &cantidad,int &capacidad);
void cargarCursos(void* &alumnos,const char* fileName);

void imprimirCursos(void* curso,ofstream &output);
void imprimirNotas(void* cursos, ofstream &output);
void imprimirAlumno(void* alumno,ofstream &output);
void probarCarga(void* alumnos,const char* fileName);

void* calcularPromedio (void* cursos);
void calcularPromedios(void *&alumno);
void cargarPromedios(void *&alumnos);

void cambiar(void *&a,void *&b);
bool comparar(void* alumnoI,void* alumnoIzq);
void qsort(void** &alumnosArreglo,int izq,int der);
void ordenamiento(void *&alumnos);
#endif //PRACTICANDOPUNTEROVOID_FUNCIONESGENERICAS_HPP