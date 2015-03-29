#include <cmath>
#include <cstdio>
#include <iostream>
#include "merge.h"
#include "zombieland.h"

using namespace std;

void calcular_costo_de_salvacion (ciudad* city, int n)
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
	int aux;
    for(int i = 0; i < n; i++)
    {
		z = city[i].cant_zombies;
		s = city[i].cant_soldados;
		c = city[i].costfsoldier;
		aux = z - 10*s;
		aux = ceil(aux/10);
		city[i].soldier_req = aux;
		aux = aux*c;
		city[i].costfsafety = aux;
	}
}

int zombie_goloso(ciudad* city, int n, int p)
{
/* Devuelve la cantidad de ciudades que se salvan */

	int i = 0;
	int sum = 0;
	
	while ((i < n) && (sum < p))
	{
		sum = sum + city[i].costfsafety;
		if (sum < p){
			city[i].salvar = 1;
		}
		i++;
	}
	return i;
}

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
    
    scanf("%i",&n);	// Levanto la cantidad de ciudades
    
    ciudad cities[n];		// Arreglo donde voy a ir metiendo las ciudades
    
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
		cities[i] = city;					// Guardo la ciudad en el arreglo
	}
	
	// Calculo y completo soldier_req y costfsafety para cada ciudad
    calcular_costo_de_salvacion(cities,n);
    
    // Ordeno por costo de salvación
    mergesort_ej1(cities,0,n-1,1);
    
    // Busco la solución "greedy"
    salvacion_total = zombie_goloso(cities,n,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    mergesort_ej1(cities,0,n-1,1);
    
    // Armo la salida
    printf("%i ",salvacion_total);
    for (i = 0; i < n; i++)			// Para cada ciudad
    {
		if (cities[i].salvar){
			printf("%i ",cities[i].soldier_req);	// soldados a enviar
		}else{
			printf("%i ",0);
		}
	}
	
}
