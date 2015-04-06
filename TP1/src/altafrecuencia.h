#ifndef ALTAFRECUENCIA_H_INCLUDED
#define ALTAFRECUENCIA_H_INCLUDED

#include <list>

using namespace std;

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

list<transmision> frequency_dc(frecuencia* freq, int low, int highs);
list<transmision> mezclar_freq(list<transmision> trans1, list<transmision> trans2);
int costo_transmision(list<transmision> trans);
bool compare_time(const frecuencia& freq1, const frecuencia& freq2);
void aux_igual_i(list<transmision>::iterator& itA, list<transmision>::iterator& itB, list<transmision>& res);
void aux_otro_i_a(list<transmision>::iterator& itA, list<transmision>::iterator& itB, list<transmision>& res);

#endif // ALTAFRECUENCIA_H_INCLUDED
