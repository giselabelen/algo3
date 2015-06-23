#include <cstdio>
#include "exp2.h"


int main()
{
	srand(time(0));
	
	int n = 9;
	int m = rand() % ((n*(n-1)/2)+1);		// Cantidad aleatoria de aristas
	
	//~ Vecinos vec = generar_aleatorio(n,m);
	//~ Vecinos vec = generar_completo(7);
	//~ Vecinos vec = generar_k2_ord(4);
	//~ Vecinos vec = generar_k2_rnd(4);
	
	//~ Vecinos vec = generar_aleatorio(n,m);
	//~ Vecinos vec = generar_estrella(n);
	//~ Vecinos vec = generar_circuito(n);
	Vecinos vec = generar_galaxia(n);
	
	//~ printf("%i %i \n",n,m);
	
	//~ for(int i = 0; i < n; i++)
	//~ {
		//~ for (list<int>::iterator it = vec[i].begin(); it != vec[i].end(); it++){
			//~ printf("%i %i \n",i+1,*it + 1);
		//~ }
	//~ }
	
	for(int i = 0; i < n; i++)
	{
		printf("%i %i ",i+1,vec[i].second);
		
		for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
			printf("%i ",*it + 1);
		}
		
		printf("\n");
	}
}
