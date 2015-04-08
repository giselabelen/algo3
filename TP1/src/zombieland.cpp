#include <cmath>
#include <cstdio>
#include <iostream>
//~ #include "merge.h"
#include "zombieland.h"
#include "testing.h"

//~ void calcular_costo_de_salvacion (ciudad* city, int n)
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
    while(it != city.end() && (sum < p))
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

/**********************************************************************/
/**********************************************************************/

int zombie_test(int n, int p)
{
/* 
 */
    int salvacion_total;
    
    list<ciudad> cities = generar_casos(n);
	
	// Calculo y completo soldier_req y costfsafety para cada ciudad
    calcular_costo_de_salvacion(cities);
    
    // Ordeno por costo de salvación
    cities.sort(compare_cost);
    
    // Busco la solución "greedy"
    salvacion_total = zombie_goloso(cities,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    cities.sort(compare_name);

	cities.clear();


/**********************************************************************/
/**********************************************************************/

int main()
{
/* Lee los datos, separa la información, y llama a las funciones
 * correspondientes para:
 * 		- calcular el costo de salvación de cada ciudad
 * 		- ordenar las ciudades por costo de salvación
 * 		- llevar a cabo la parte "golosa"
 * Finalmente, arma la salida.
 */
	int i;
    int n;
    int p;
    int num_zombis;
    int num_soldados;
    int costo_por_soldado;
    int salvacion_total;
    ciudad city;
    
    list<ciudad> cities;
    list<ciudad>::iterator it;
    
    scanf("%i",&n);	// Levanto la cantidad de ciudades
    
    //~ ciudad cities[n];		// Arreglo donde voy a ir metiendo las ciudades
    
    scanf("%i",&p); // Levanto el presupuesto
	
    for (i = 0; i < n; i++)			// Para cada ciudad
    {
		scanf("%i",&num_zombis);	// Levanto los datos
		scanf("%i",&num_soldados);
		scanf("%i",&costo_por_soldado);
		city = (ciudad){						// Lleno el struct SALVO
			.nombre = i,
			.cant_zombies = num_zombis,
			.cant_soldados = num_soldados,
			.soldier_req = 0,					// soldier _req y costfsafety
			.costfsoldier = costo_por_soldado,
			.costfsafety = 0,					// que se resuelven después
			.salvar = 0,
		};
		//~ cities[i] = city;					// Guardo la ciudad en el arreglo
		cities.push_back(city);
	}
	
	// Calculo y completo soldier_req y costfsafety para cada ciudad
    //~ calcular_costo_de_salvacion(cities,n);
    calcular_costo_de_salvacion(cities);
    
    // Ordeno por costo de salvación
    //~ mergesort_ej1(cities,0,n-1,1);
    cities.sort(compare_cost);
    //~ cities.sort();
    
    // Busco la solución "greedy"
    //~ salvacion_total = zombie_goloso(cities,n,p);
    salvacion_total = zombie_goloso(cities,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    //~ mergesort_ej1(cities,0,n-1,1);
    cities.sort(compare_name);
    
    // Armo la salida
    printf("%i ",salvacion_total);
    
    //~ for (i = 0; i < n; i++)			// Para cada ciudad
    for (it = cities.begin(); it != cities.end(); it++)	// Para cada ciudad
    {
		if (it->salvar){
			printf("%i ",it->soldier_req);	// soldados a enviar
		}else{
			printf("%i ",0);
		}
	}
	cities.clear();
}
