#include <cmath>
#include <cstdio>
#include <iostream>
//~ #include "merge.h"
#include "altafrecuencia.h"

void aux_igual_i(list<transmision>::iterator& itA, list<transmision>::iterator& itB, list<transmision>& res)
{
	if(itA->fin < itB->fin){
		res.push_back(*itA);
		itB->inicio = itA->fin;
		itA++;		
	}else if(itA->fin == itB->fin){
		res.push_back(*itA);
		itA++;
		itB++;
	}else{
		itB++;
	}
}

void aux_otro_i_a(list<transmision>::iterator& itA, list<transmision>::iterator& itB, list<transmision>& res)
{
	if(itA->fin < itB->fin){
		res.push_back(*itA);
		itB->inicio = itA->fin;
		itA++;
	}else if(itA->fin == itB->fin){
		res.push_back(*itA);
		itA++;
		itB++;
	}else{
		itB++;
	}
}

void aux_otro_i_b(list<transmision>::iterator& itA, list<transmision>::iterator& itB, list<transmision>& res)
{
	res.push_back(*itA);
	(res.back()).fin = itB->inicio;
	
	if(itA->fin < itB->fin){
		itA++;
	}else if(itA->fin == itB->fin){
		res.push_back(*itB);
		itA++;
		itB++;
	}else{
		res.push_back(*itB);
		itA->inicio = itB->fin;
		itB++;
	}
}

list<transmision> mezclar_freq(list<transmision> trans1, list<transmision> trans2)
{	
	list<transmision> res;
	list<transmision>::iterator it1 = trans1.begin();
	list<transmision>::iterator it2 = trans2.begin();
	
	while((it1 != trans1.end()) && (it2 != trans2.end()))
	{
		if(it1->inicio == it2->inicio)	// inicio1 == inicio2
		{
			if((it1->freq).costfminute <= (it2->freq).costfminute){	// costo1 <= costo2
				aux_igual_i(it1,it2,res);
			}else{	// costo1 > costo2
				aux_igual_i(it2,it1,res);
			}
		}else if(it1->inicio < it2->inicio)	// inicio1 < inicio2
		{
			if(it1->fin <= it2->inicio){	// fin1 <= inicio2
				res.push_back(*it1);
				it1++;
			}else{	// fin1 > inicio2
				if((it1->freq).costfminute <= (it2->freq).costfminute){	// costo1 <= costo2
					aux_otro_i_a(it1,it2,res);
				}else{	// costo1 > costo2
					aux_otro_i_b(it1,it2,res);
				}
			}
		}else{	// inicio1 > inicio2
			if((it1->freq).costfminute < (it2->freq).costfminute){	// costo1 < costo2
				aux_otro_i_b(it2,it1,res);
			}else{	// costo1 >= costo2
				aux_otro_i_a(it2,it1,res);
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
			.freq = freq[low],
			.inicio = freq[low].inicio,
			.fin = freq[low].fin,
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
	int inicio;
	int fin;
	
	for(list<transmision>::iterator it = trans.begin(); it != trans.end(); it++)
	{
		inicio = it->inicio;
		fin = it->fin;
		res = res + (fin-inicio)*(it->freq).costfminute;
	}
	
	return res;
}

bool compare_time(const frecuencia& freq1, const frecuencia& freq2)
{
	return (freq1.inicio < freq2.inicio);
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
    list<frecuencia> freq_l;
    list<frecuencia>::iterator it;
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
		freq_l.push_back(freq);			// Guardo la frecuencia en el arreglo
	}
	
    // Ordeno por tiempo de inicio
    //~ mergesort_ej2(total_freq,0,n-1);
    freq_l.sort(compare_time);
    
    // Paso la lista a un arreglo
    i = 0;
    for (it = freq_l.begin(); it != freq_l.end(); it++)
    {
		total_freq[i] = *it;
		i++;
	}
    freq_l.clear();
    
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
