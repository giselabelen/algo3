#include <cstdio>
#include "petroleo.h"

int main()
{
	int n;
	int m;
	int costo_ref;
	int p1;
	int p2;
	int costo_tub;
	int costo_total;
	int cant_ref;
	int cant_tub;
	list<int> refinerias;
	list< pair<int,int> > tuberias;
	
	scanf("%i",&n);	// cantidad de pozos
	scanf("%i",&m);	// cantidad de posibles tuberías
	scanf("%i",&costo_ref);	// costo por refinería
	
	Grafo g(n, Vec(n,-1));	// grafo - en ppio lleno de (-1) - voy a ir agregando las conexiones
	
	// lleno el grafo
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&t1);
		scanf("%i",&t2);
		scanf("%i",&costo_tub);
		
		if(costo_tub <= costo_ref)
		{
			g[t1-1][t2-1] = costo_tub;
			g[t2-1][t1-1] = costo_tub;
		}
	}
	
	// MAGIA
	cant_ref = comp_conexas(g,n,refinerias);	
	cant_tub = petroleo(g,n,tuberias);
	
	
	//SALIDA
	printf("%i %i %i\n",costo_total,cant_ref,cant_tub);
	
	for (list<int>::iterator it = refinerias.begin(); it != refinerias.end(); it++){
		printf("%i ",*it);
	}
	
	for (list<int>::iterator it = tuberias.begin(); it != tuberias.end(); it++){
		printf("\n%i %i",it->first,it->second);
	}
	
	refinerias.clear();
	tuberias.clear();
}
