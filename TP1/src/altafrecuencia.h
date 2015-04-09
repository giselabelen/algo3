#ifndef ALTAFRECUENCIA_H_INCLUDED
#define ALTAFRECUENCIA_H_INCLUDED

#include <list>
#include <cmath>

using namespace std;

/**********************************************************************/
/****************      DEFINICIONES      ******************************/
/**********************************************************************/

typedef struct frecuencia_t
{
	int nombre; // numero que identifica la frecuencia segun el orden en el que viene dada
	int costfminute;  // costo de uso por minuto
    int inicio;	// minuto inicio de transmisión
    int fin;	// minuto fin de transmisión
} frecuencia;

list<frecuencia> frequency_dc(frecuencia* freq, int low, int highs);
list<frecuencia> mezclar_freq(list<frecuencia> trans1, list<frecuencia> trans2);
int costo_transmision(list<frecuencia> trans);
bool compare_time(const frecuencia& freq1, const frecuencia& freq2);
void aux_mezcla_a(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res);
void aux_mezcla_b(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res);
int altafrecuencia(list<frecuencia>& freq_l, list<frecuencia>& res, int n);


/**********************************************************************/
/****************      IMPLEMENTACIÓN      ****************************/
/**********************************************************************/

void aux_mezcla_a(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res)
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

void aux_mezcla_b(list<frecuencia>::iterator& itA, list<frecuencia>::iterator& itB, list<frecuencia>& res)
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

list<frecuencia> mezclar_freq(list<frecuencia> trans1, list<frecuencia> trans2)
{	
	list<frecuencia> res;
	list<frecuencia>::iterator it1 = trans1.begin();
	list<frecuencia>::iterator it2 = trans2.begin();
	
	while((it1 != trans1.end()) && (it2 != trans2.end()))
	{
		if(it1->inicio == it2->inicio)	// inicio1 == inicio2
		{
			if(it1->costfminute <= it2->costfminute){	// costo1 <= costo2
				aux_mezcla_a(it1,it2,res);
			}else{	// costo1 > costo2
				aux_mezcla_a(it2,it1,res);
			}
		}else if(it1->inicio < it2->inicio)	// inicio1 < inicio2
		{
			if(it1->fin <= it2->inicio){	// fin1 <= inicio2
				res.push_back(*it1);
				it1++;
			}else{	// fin1 > inicio2
				if(it1->costfminute <= it2->costfminute){	// costo1 <= costo2
					aux_mezcla_a(it1,it2,res);
				}else{	// costo1 > costo2
					aux_mezcla_b(it1,it2,res);
				}
			}
		}else{	// inicio1 > inicio2
			if(it1->costfminute < it2->costfminute){	// costo1 < costo2
				aux_mezcla_b(it2,it1,res);
			}else{	// costo1 >= costo2
				aux_mezcla_a(it2,it1,res);
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

list<frecuencia> frequency_dc(frecuencia* freq, int low, int high)
{
	int mid;
	list<frecuencia> trans1;
	list<frecuencia> trans2;
	list<frecuencia> trans_final;
	
    if (low < high)	// Divido en 2 y hago recursión
    {
        mid = (low+high)/2;
        trans1 = frequency_dc(freq,low,mid);
        trans2 = frequency_dc(freq,mid+1,high);
		trans_final = mezclar_freq(trans1,trans2);
    }else{	// Es un solo elemento, hago una lista con esa transmisión
		trans_final.push_back(freq[low]);
	}
	trans1.clear();
	trans2.clear();
    return trans_final;
}

int costo_transmision(list<frecuencia> trans)
{
	int res = 0;
	int inicio;
	int fin;
	
	for(list<frecuencia>::iterator it = trans.begin(); it != trans.end(); it++)
	{
		inicio = it->inicio;
		fin = it->fin;
		res = res + (fin-inicio)*(it->costfminute);
	}
	
	return res;
}

bool compare_time(const frecuencia& freq1, const frecuencia& freq2)
{
	return (freq1.inicio < freq2.inicio);
}

int altafrecuencia(list<frecuencia>& freq_l, list<frecuencia>& res, int n)
{
    // Ordeno por tiempo de inicio
    freq_l.sort(compare_time);
    
    // Paso la lista a un arreglo
    int i = 0;
    frecuencia total_freq[n];
    
    for (list<frecuencia>::iterator it = freq_l.begin(); it != freq_l.end(); it++)
    {
		total_freq[i] = *it;
		i++;
	}
    freq_l.clear();
    
    // Hago el divide and conquer
    res = frequency_dc(total_freq,0,n-1);
    
    // Calculo el costo total
    return costo_transmision(res);
}

#endif // ALTAFRECUENCIA_H_INCLUDED
