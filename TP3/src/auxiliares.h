#ifndef AUXILIARES_H_INCLUDED
#define AUXILIARES_H_INCLUDED

#include <ctime>
#include <cstdlib>

using namespace std;


/**************************** ESTRUCTURAS ****************************/



/********************** DECLARACIÓN DE FUNCIONES **********************/

void imp_instancia(FILE* pIn, int n, int a, Vecinos vec);
void sacar_outliers(list<double>& lista);
double promediar(list<double> lista);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void imp_instancia(FILE* pIn, int n, int a, Vecinos vec)
{
	fprintf(pIn,"%i %i \n",n,a);

	for(int i = 0; i < n; i++)
	{
		for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
			fprintf(pIn,"%i %i \n",i+1,*it + 1);
		}
	}
	
	fprintf(pIn,"\n");
}


void sacar_outliers(list<double>& lista)
{
	list<double>::iterator it;
	list<double>::iterator min;
	list<double>::iterator max;
	
	for(int i = 0; i < 2; i++)
	{
		it = lista.begin();
		min = it;
		max = it;
		it++;
		
		while(it != lista.end())
		{
			if(*it < *min){ min = it; }
			if(*it > *max){ max = it; }
			it++;
		}
		
		min = lista.erase(min);
		max = lista.erase(max);
	}
}


double promediar(list<double> lista)
{
	double suma = 0;
	double valor = 0;
	
	for(list<double>::iterator it = lista.begin(); it != lista.end(); it++)
	{ 
		suma += *it;
		valor++;
	}
	
	return (suma/valor);
}


#endif // AUXILIARES_H_INCLUDED
