#include <cstdio>
#include "CIDM_goloso.h"

int main()
{
	int n;					// Cantidad de nodos
	int m;					// Cantidad de vértices
	int e1;					// Para procesar las aristas	
	int e2;					// Idem
	int res = 0;			// Total de nodos de la solución
	list<int> cidm_sol;		// Nodos del conjunto solución
	
	scanf("%i",&n);
	scanf("%i",&m);

	Vecinos vec(n);			// Lista de adyacencia
	
	for(int i = 0; i < n; i++){
		vec[i].second = 0;
	}
	
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&e1);
		scanf("%i",&e2);
		
		(vec[e1-1].first).push_back(e2-1);
		(vec[e2-1].first).push_back(e1-1);
		
		vec[e1-1].second++;
		vec[e2-1].second++;
	}
	
	//~ backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0);
	res = goloso(cidm_sol,vec,n);
	
	// Armo la salida
	printf("%i ",res);
	
	for (list<int>::iterator it = cidm_sol.begin(); it != cidm_sol.end(); it++){
		printf("%i ",*it + 1);
	}
}