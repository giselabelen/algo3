#ifndef VEAMOS_H_INCLUDED
#define VEAMOS_H_INCLUDED
#include <stdbool.h>
#include <stdio.h>

typedef struct ciudad_t
{
    int    zombies;
    int    soldados;
    int    costfsoldier;
    int    costfsafety;
    struct ciudad_t *sig;
    struct ciudad_t *ant;
}

typedef struct lista_t
{
    struct ciudad_t   *primero;
    struct ciudad_t   *ultimo;
}

#endif // VEAMOS_H_INCLUDED
