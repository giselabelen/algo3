#ifndef ALTAFRECUENCIA_H_INCLUDED
#define ALTAFRECUENCIA_H_INCLUDED

#include <list>

typedef struct frecuencia_t
{
	int nombre; // numero que identifica la frecuencia segun el orden en el que viene dada
	int costfminute;  // costo de uso por minuto
    int inicio;	// minuto inicio de transmisión
    int fin;	// minuto fin de transmisión
} frecuencia;

typedef struct transmision_t
{
	frecuencia freq; // frecuencia que estoy transmitiendo
	int inicio;	// inicio de transmisión
    int fin;	// fin de transmisión
} transmision;

//~ list<transmision> frequency_dc(frecuencia* freq, int low, int highs, int costo);
//~ list<transmision> mezclar_freq(list<transmision>::iterator it_trans1, list<transmision>::iterator it_trans2);

#endif // ALTAFRECUENCIA_H_INCLUDED
