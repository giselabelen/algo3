#include <cstdio>
#include <ctime>
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"
#include "CIDM_grasp.h"

int main()
{
	srand(time(0));
	int n;					// Cantidad de nodos
	int m;					// Cantidad de aristas
	int e1;					// Para procesar las aristas	
	int e2;					// Idem
	int res = 0;			// Total de nodos de la solución
	list<int> cidm;	
	list<int> cidm_sol;		// Nodos del conjunto solución
	
	scanf("%i",&n);
	scanf("%i",&m);

	int cota = n;
	vector<int> estado(n,0);
	Vecinos vec(n);			// Lista de adyacencia
	Vecinos vec_copia(n);	// Lista de adyacencia
	
	for(int i = 0; i < n; i++){
		vec[i].second = 0;
	}
	
	for(int i = 0; i < m; i++)
	{
		scanf("%i",&e1);
		scanf("%i",&e2);
		
		(vec[e1-1].first).push_back(e2-1);
		(vec[e2-1].first).push_back(e1-1);
		
		(vec_copia[e1-1].first).push_back(e2-1);
		(vec_copia[e2-1].first).push_back(e1-1);
		
		vec[e1-1].second++;
		vec[e2-1].second++;
		
		vec_copia[e1-1].second++;
		vec_copia[e2-1].second++;
	}

	// SOLUCIONES (USAR SÓLO UNA)

	// SOLUCIÓN EXACTA
	//~ backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0,4);
	//~ res = cota;

	// SOLUCIÓN GOLOSA CONSTRUCTIVA
	//~ res = goloso(cidm_sol,vec,n,0,0);

	//~ // SOLUCIÓN DE BÚSQUEDA LOCAL
	//~ // Soluciones iniciales (usar sólo una)
	//~ res = goloso(cidm_sol,vec_copia,n,0,0);
	res = otro_inicio(cidm_sol,vec,n);
	
	// Vecindades
	if(res != 1)
	{
		busqueda(cidm_sol,vec,n,res,2);	// 1 para busq1 y 2 para busq2
	}
	//~ 
	//~ // SOLUCIÓN POR GRASP
	//~ res = grasp(cidm_sol,vec,n,0.5,0,50,1);	// 1 para tantas it sin mejora, 2 para tantas it asi nomas
	
	// Armo la salida
	printf("%i ",res);
	
	for (list<int>::iterator it = cidm_sol.begin(); it != cidm_sol.end(); it++){
		printf("%i ",*it + 1);
	}
	
	printf("\n");
}
