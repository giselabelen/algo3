#include <cstdio>
#include <ctime>
#include "zombieland.h"

int main()
{
/* Lee los datos, separa la información, y llama a la función ZOMBIELAND
 * que se encarga de:
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
    
    salvacion_total = zombieland(cities,p);
	    
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
