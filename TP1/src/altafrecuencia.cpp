#include <cmath>
#include <cstdio>
#include <iostream>
#include "merge.h"
#include "altafrecuencia.h"

using namespace std;

int main()
{
/* Lee los datos, separa la información, y llama a las funciones 
 * correspondientes para:
 * 		- 
 * 		- 
 * 		- 
 */
	int i;
    int n;
    int p;
    int costo_por_minuto;
    int start;
    int end;
    frecuencia freq;
    
    scanf("%i",&n);	// Levanto la cantidad de frecuencias
    
    frecuencia total_freq[n];	// Arreglo donde voy a ir metiendo las frecuencias
       
    for (i = 0; i < n; i++)			// Para cada frecuencia
    {
		scanf("%i",&costo_por_minuto);	// Levanto los datos
		scanf("%i",&start);
		scanf("%i",&end);
		freq = (frecuencia){			// Lleno el struct
			.nombre = i,
			.costfminute = costo_por_minuto,
			.inicio = start,
			.fin = end,
		};
		total_freq[i] = freq;			// Guardo la frecuencia en el arreglo
	}
	
    // Ordeno por tiempo de inicio
    mergesort_ej2(total_freq,0,n-1);
    
    // Busco la solución "greedy"
    costo_total = zombie_goloso(cities,n,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    mergesort_ej1(cities,0,n-1,1);
    
    // Armo la salida
    printf("%i ",costo_total);
    for (i = 0; i < n; i++)			// Para cada ciudad
    {
		if (cities[i].salvar){
			printf("%i ",cities[i].soldier_req);	// Levanto los datos
		}else{
			printf("%i ",0);	// Levanto los datos
		}
	}
	
}
