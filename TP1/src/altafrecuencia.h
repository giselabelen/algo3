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

list<frecuencia> frequency_dc(frecuencia* freq, int low, int highs);
list<frecuencia> mezclar_freq(list<frecuencia> trans1, list<frecuencia> trans2);
int costo_transmision(list<frecuencia> trans);
bool compare_time(const frecuencia& freq1, const frecuencia& freq2);
void aux_mezcla_a(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res);
void aux_mezcla_b(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res);

#endif // ALTAFRECUENCIA_H_INCLUDED
