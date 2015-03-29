#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

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

//~ void heroe_tactico_del_pais(FILE* a);
void calcular_costo_de_salvacion(ciudad* city, int n);
int zombie_goloso(ciudad* city, int n, int p);

#endif // ZOMBIELAND_H_INCLUDED
