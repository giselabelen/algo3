#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

#include <list>
#include <cmath>

using namespace std;

/**********************************************************************/
/****************      DEFINICIONES      ******************************/
/**********************************************************************/

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
int zombieland(list<ciudad>& cities, int p);


/**********************************************************************/
/****************      IMPLEMENTACIÓN      ****************************/
/**********************************************************************/

void calcular_costo_de_salvacion (list<ciudad>& city)
{
/* Función que calcula la cantidad de soldados que hacen falta y 
 * el correspondiente costo, para salvar cada ciudad.
 * Cálculos: 
 * 		r = (#zombies-10*#soldados)/10 (redondeando hacia arriba) 
 * 				-> cant soldados que hacen falta
 * 		r*costo -> costo total de salvar a esa ciudad	
 * Cada resultado se coloca en el correspondiente campo de ciudad.
*/
	int z;
	int s;
	int c;
	float aux;
	list<ciudad>::iterator it;
	
    //~ for(int i = 0; i < n; i++)
    for(it = city.begin(); it != city.end(); it++)
    {
		z = it->cant_zombies;
		s = it->cant_soldados;
		c = it->costfsoldier;
		aux = z - 10*s;
		if(aux < 0){
			aux = 0;
		}
		aux = ceil(aux/10);
		it->soldier_req = aux;
		aux = aux*c;
		it->costfsafety = aux;
	}
}

//~ int zombie_goloso(ciudad* city, int n, int p)
int zombie_goloso(list<ciudad>& city, int p)
{
/* Devuelve la cantidad de ciudades que se salvan */

	int i = 0;
	int sum = 0;
	list<ciudad>::iterator it = city.begin();
    
    //~ while ((i < n) && (sum < p))
    while(it != city.end() && (sum <= p))
	{
		sum = sum + it->costfsafety;
		if (sum <= p){
			it->salvar = 1;
			i++;
		}
		it++;
	}
	return i;
}

bool compare_cost(const ciudad& city1, const ciudad& city2)
{
	return (city1.costfsafety < city2.costfsafety);
}

bool compare_name(const ciudad& city1, const ciudad& city2)
{
	return (city1.nombre < city2.nombre);
}

int zombieland(list<ciudad>& cities, int p)
{
	// Calculo y completo soldier_req y costfsafety para cada ciudad
    calcular_costo_de_salvacion(cities);
    
    // Ordeno por costo de salvación
    cities.sort(compare_cost);
    
    // Busco la solución "greedy"
    int salvacion_total = zombie_goloso(cities,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    cities.sort(compare_name);
    
    return salvacion_total;
    //return 0;
}

#endif // ZOMBIELAND_H_INCLUDED
