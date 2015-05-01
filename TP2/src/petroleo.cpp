#include <cstdio>
#include "petroleo.h"

int main()
{
	int n;
	int m;
	int costo_ref;
	int t1;
	int t2;
	int costo_tub;
	int costo_total;
	int cant_ref = 0;
	int cant_tub;
	list<int> refinerias;
	list<Arista> tuberias;
	Arista edge;
	pair<Arista,int> con_peso;
	
	
	scanf("%i",&n);	// cantidad de pozos
	scanf("%i",&m);	// cantidad de posibles tuberías
	scanf("%i",&costo_ref);	// costo por refinería
	
	Incidencia inc;	// lista que contendrá las posibles tuberías con sus costos
	
	// lleno la lista de incidencia
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&t1);
		scanf("%i",&t2);
		scanf("%i",&costo_tub);
		
		if(costo_tub <= costo_ref)	// si conviene usar esa tubería
		{			
			edge = make_pair(t1-1,t2-1);	// tubería
			con_peso = make_pair(edge,costo_tub);	// (tubería,peso)
			inc.push_back(con_peso);	// agrego a la lista
		}
	}
	
	// ordeno la lista de incidencia por pesos
	inc.sort(comparar_peso);
	
	// armo el plan y devuelvo el costo total del mismo
	costo_total = petroleo(inc,refinerias,tuberias,n,cant_ref,cant_tub,costo_ref);
		
	// salida
	printf("%i %i %i\n",costo_total,cant_ref,cant_tub);	// K, r, t
	
	// pozos con refinería
	for (list<int>::iterator it = refinerias.begin(); it != refinerias.end(); it++){
		printf("%i ",*it + 1);
	}
	
	// tuberías colocadas
	for (list<Arista>::iterator it = tuberias.begin(); it != tuberias.end(); it++){
		printf("\n%i %i",it->first + 1,it->second + 1);
	}
	
	refinerias.clear();
	tuberias.clear();
	inc.clear();
}
