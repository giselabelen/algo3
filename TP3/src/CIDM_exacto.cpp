#include <cstdio>
#include "CIDM_exacto.h"

int main()
{
	int n;					// Cantidad de nodos
	int m;					// Cantidad de vértices
	int e1;					// Para procesar las aristas	
	int e2;					// Idem
	int res = 0;			// Total de nodos de la solución
	list<int> cidm;	
	list<int> cidm_sol;		// Nodos del conjunto solución
	
	scanf("%i",&n);
	scanf("%i",&m);
	
	vector<int> estado(n,0);
	Vecinos vec(n);			// Lista de adyacencia
	int cota = n;
	
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&e1);
		scanf("%i",&e2);
		
		vec[e1-1].push_back(e2-1);
		vec[e2-1].push_back(e1-1);
	}
	
	backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0);
	
	// Armo la salida
	printf("%i \n",res);
	
	for (list<int>::iterator it = cidm.begin(); it != cidm.end(); it++){
		printf("%i \n",*it);
	}
}
