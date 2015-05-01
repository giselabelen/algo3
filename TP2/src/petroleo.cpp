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
	int aux1;
	int aux2;
	list<int> refinerias;
	list<Arista> tuberias;
	Arista edge;
	pair<Arista,int> con_peso;
	
	
	scanf("%i",&n);	// cantidad de pozos
	scanf("%i",&m);	// cantidad de posibles tuberías
	scanf("%i",&costo_ref);	// costo por refinería
	
	//~ Grafo g(n, Vec(n,-1));	// grafo - en ppio lleno de (-1) - voy a ir agregando las conexiones
	
	//~ Adyacencia ady(n);	// arreglo de n elementos que contendrá los vecinos de c/u
	Incidencia inc;	// lista que contendrá las posibles tuberías
	
	// lleno las estructuras
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&t1);
		scanf("%i",&t2);
		scanf("%i",&costo_tub);
		
		if(costo_tub <= costo_ref)
		{
			//~ g[t1-1][t2-1] = costo_tub;
			//~ g[t2-1][t1-1] = costo_tub;
			
			aux1 = min(t1,t2) - 1;
			aux2 = max(t1,t2) - 1;
			
			//~ ady[aux1].push_back(aux2);
			edge = make_pair(aux1,aux2);
			con_peso = make_pair(edge,costo_tub);
			inc.push_back(con_peso);
		}
	}
	
	// MAGIA
	//~ cant_ref = comp_conexas(g,n,refinerias);	
	//~ cant_tub = petroleo(g,n,tuberias);
	
	// ordeno las listas de ady
	//~ for(int i = 0; i < n; i++){
		//~ ady[i].sort();
	//~ }
	
	
	
	// ordeno la lista de incidencia por pesos
	inc.sort(comparar_peso);
	
	//~ int bla = 0;
	//~ for(list< pair<Arista,int> >::iterator it = inc.begin(); it != inc.end(); it++)
	//~ {
		//~ bla++;
	//~ }
	
	costo_total = petroleo(inc,refinerias,tuberias,n,cant_ref,cant_tub,costo_ref);
	
	// cuento la cant de refinerias y guardo los nodos que tendrán refinería
	//~ cant_ref = comp_conexas(ady,n,refinerias);
	//~ costo_total = costo_ref*cant_ref;
	//~ cant_tub = plan(inc,n,tuberias,costo_total);
	
	
	//SALIDA
	printf("%i %i %i\n",costo_total,cant_ref,cant_tub);
	
	for (list<int>::iterator it = refinerias.begin(); it != refinerias.end(); it++){
		printf("%i ",*it + 1);
	}
	
	for (list<Arista>::iterator it = tuberias.begin(); it != tuberias.end(); it++){
		printf("\n%i %i",it->first + 1,it->second + 1);
	}
	
	refinerias.clear();
	tuberias.clear();
	inc.clear();
}
