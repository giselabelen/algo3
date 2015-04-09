#ifndef TESTING_H_INCLUDED
#define TESTING_H_INCLUDED

#include "zombieland.h"
#include "altafrecuencia.h"
//~ #include "caballos.h"

list<ciudad> generar_pais(int n);
list<frecuencia> generar_freq_piramide(int n);
list<frecuencia> generar_freq_tren(int n);
list<frecuencia> generar_freq_cadena(int n);

void testear_1();
void testear_2();
//~ void testear_3();

#endif // TESTING_H_INCLUDED

