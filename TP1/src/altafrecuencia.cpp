#include <cmath>
#include <cstdio>
#include <iostream>
#include "merge.h"
#include "altafrecuencia.h"


list<transmision> mezclar_freq(list<transmision> trans1, list<transmision> trans2)
{	
	list<transmision> res;
	list<transmision>::iterator it1 = trans1.begin();
	list<transmision>::iterator it2 = trans2.begin();
	
	while((it1 != trans1.end()) && (it2 != trans2.end()))
	{
		if(it1->inicio == it2->inicio)	// inicio1 == inicio2
		{
			if((it1->freq).costfminute <= (it2->freq).costfminute)	// costo1 <= costo2
			{
				res.push_back(*it1);
				it1++;
				
				if(it1->fin >= it2->fin){	// fin1 >= fin2
					it2++;		
				}
			}else{	// costo1 > costo2
				if(it1->fin > it2->fin){	// fin1 > fin2
					res.push_back(*it2);
					it1->inicio = it2->fin + 1;
					it2++;
				}else{	// fin1 <= fin2
					it1++;
				}
			}
		}else{	// inicio1 < inicio2
			if(it1->fin < it2->inicio){	// fin1 < inicio2
				res.push_back(*it1);
				it1++;
			}else{	// fin1 >= inicio2
				if((it1->freq).costfminute <= (it2->freq).costfminute)	// costo1 <= costo2
				{
					res.push_back(*it1);
					it1++;
					
					if(it1->fin >= it2->fin){	// fin1 >= fin2
						it2++;
					}else{	// fin1 < fin2
						it2->inicio = it1->fin + 1;
					}
				}else{	// costo1 > costo2
					it1->fin = it2->inicio - 1;
					res.push_back(*it1);
					
					if(it1->fin <= it2->fin){	// fin1 <= fin2
						it1++;
					}else{	// fin1 > fin2
						res.push_back(*it2);
						it1->inicio = it2->fin + 1;
						it2++;
					}
				}
			}
		}
	}

	// si me quedaron cosas en la primera lista, las agrego a la solución
	while(it1 != trans1.end())
	{	
		res.push_back(*it1);
		it1++;
	}
	
	// si me quedaron cosas en la segunda lista, las agrego a la solución
	while(it2 != trans2.end())
	{	
		res.push_back(*it2);
		it2++;
	}
	
	return res;
}


list<transmision> frequency_dc(frecuencia* freq, int low, int high)
{
	int mid;
	transmision tr;
	list<transmision> trans1;
	list<transmision> trans2;
	list<transmision> trans_final;
	
    if (low < high)	// Divido en 2 y hago recursión
    {
        mid = (low+high)/2;
        trans1 = frequency_dc(freq,low,mid);
        trans2 = frequency_dc(freq,mid+1,high);
		trans_final = mezclar_freq(trans1,trans2);
    }else{	// Es un solo elemento, hago una lista con esa transmisión
		tr = (transmision){
			.freq = freq[0],
			.inicio = freq[0].inicio,
			.fin = freq[0].fin,
		};
		trans_final.push_back(tr);
	}
	trans1.clear();
	trans2.clear();
    return trans_final;
}

int costo_transmision(list<transmision> trans)
{
	int res = 0;
	
	for(list<transmision>::iterator it = trans.begin(); it != trans.end(); it++)
	{
		res = res + (it->freq).costfminute;
	}
	
	return res;
}


/**********************************************************************/
/**********************************************************************/

int main()
{
/* Lee los datos, separa la información, y llama a las funciones 
 * correspondientes para:
 * 		- ordenar las frecuencias por tiempo de inicio
 * 		- hacer el divide and conquer
 * 		- calcular el costo total
 * Finalmente, arma la salida.
 */
	int i;
    int n;
    int p;
    int costo_por_minuto;
    int start;
    int end;
	int costo_total;
    frecuencia freq;
    list<transmision> res;
    
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
    
    // Hago el divide and conquer
    res = frequency_dc(total_freq,0,n-1);
    
    // Calculo el costo total
    costo_total = costo_transmision(res);
    
    // Armo la salida
    printf("%i \n",costo_total);
    for(list<transmision>::iterator it = res.begin(); it != res.end(); it++)
    {
		printf("%i %i %i \n",it->inicio,it->fin,(it->freq).nombre);
	}
	printf("%i",-1);
	
	res.clear();
}
