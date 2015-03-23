#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>

typedef struct ciudad_t
{
	int nombre; // numero que identifica la ciudad segun el orden en el que viene dada
    int cant_zombies;
    int cant_soldados;
    int soldier_req;  // numero de soldados que faltan para salvar la ciudad
    int costfsoldier;  // costo de enviar un soldado
    int costfsafety;  // costo de salvar esa ciudad
}

#endif // ZOMBIELAND_H_INCLUDED
