#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

#include <list>

using namespace std;

typedef struct ciudad_t
{
	int nombre; // numero que identifica la ciudad segun el orden en el que viene dada
    int cant_zombies;
    int cant_soldados;
    int soldier_req;  // numero de soldados que faltan para salvar la ciudad
    int costfsoldier;  // costo de enviar un soldado
    int costfsafety;  // costo de salvar esa ciudad
    bool salvar;	// 1 para salvarla, 0 para no salvarla
} ciudad;

void calcular_costo_de_salvacion(list<ciudad>& city);
int zombie_goloso(list<ciudad>& city, int p);
bool compare_cost(const ciudad& city1, const ciudad& city2);
bool compare_name(const ciudad& city1, const ciudad& city2);

#endif // ZOMBIELAND_H_INCLUDED
