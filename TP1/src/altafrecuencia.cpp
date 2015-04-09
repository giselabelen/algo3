#include <cstdio>
#include "altafrecuencia.h"

int main()
{
/* Lee los datos, separa la información, y llama a la función
 * ALTAFRECUENCIA que se encarga de:
 * 		- ordenar las frecuencias por tiempo de inicio
 * 		- hacer el divide and conquer
 * 		- calcular el costo total
 * Finalmente, arma la salida.
 */
	int i;
    int n;
    int costo_por_minuto;
    int start;
    int end;
	int costo_total;
    frecuencia freq;
    list<frecuencia> freq_l;
    list<frecuencia>::iterator it;
    list<frecuencia> res;
    
    scanf("%i",&n);	// Levanto la cantidad de frecuencias
       
    for (i = 0; i < n; i++)			// Para cada frecuencia
    {
		scanf("%i",&costo_por_minuto);	// Levanto los datos
		scanf("%i",&start);
		scanf("%i",&end);
		freq = (frecuencia){			// Lleno el struct
			.nombre = i + 1,
			.costfminute = costo_por_minuto,
			.inicio = start,
			.fin = end,
		};
		freq_l.push_back(freq);			// Guardo la frecuencia en el arreglo
	}
	
    costo_total = altafrecuencia(freq_l,res,n);
    
    // Armo la salida
    printf("%i \n",costo_total);
    for(list<frecuencia>::iterator it = res.begin(); it != res.end(); it++)
    {
		printf("%i %i %i \n",it->inicio,it->fin,it->nombre);
	}
	printf("%i",-1);

	res.clear();
}
