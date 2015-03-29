#ifndef MERGE_H_INCLUDED
#define MERGE_H_INCLUDED

#include "zombieland.h"
#include "altafrecuencia.h"

/* Funciones para el mergesort con ciudades */
void merge_ej1(ciudad *a, int low, int high, int mid, bool b);
void mergesort_ej1(ciudad *a, int low, int high, bool b);

/* Funciones para el mergesort con frecuencias */
void merge_ej2(frecuencia *a, int low, int high, int mid);
void mergesort_ej2(frecuencia *a, int low, int high);

#endif // MERGE_H_INCLUDED
