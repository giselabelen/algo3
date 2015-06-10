#ifndef CIDM_GRASP_H_INCLUDED
#define CIDM_GRASP_H_INCLUDED

#include <list>
#include <vector>
#include <cmath>
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"

using namespace std;

/**************************** ESTRUCTURAS ****************************/



/********************** DECLARACIÓN DE FUNCIONES **********************/

int grasp(list<int>& cidm_sol, Vecinos vecinos, int n, float alpha, int beta, int parada);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int grasp(list<int>& cidm_sol, Vecinos vecinos, int n, float alpha, int beta, int parada)
{
	int res = n + 1;
	int res_aux;
	int k = 0;
	list<int> cidm_aux;
	list<int>::iterator it;
	Vecinos vecinos_aux;
	
	while(k != parada)
	{
		// COPIO VECINOS A VECINOS_AUX PORQUE EL GOLOSO ROMPE
		for(int i = 0; i < n; i++)
		{
			(vecinos_aux[i].first).clear();
			
			for(it = (vecinos[i].first).begin(); it != (vecinos[i].first).end(); it++)
			{
				(vecinos_aux[i].first).push_back(*it);
			}
			
			vecinos_aux[i].second = vecinos[i].second;
		}
		
		res_aux = goloso(cidm_aux,vecinos_aux,n,alpha,beta);	// goloso
		busqueda1(cidm_aux,vecinos_aux,n,res);				// mejora por local search
		
		if(res_aux < res)
		{
			// SI TENGO UNA SOLUCIÓN MEJOR, ACTUALIZO RES Y CIDM_SOL
			res = res_aux;
			cidm_sol.clear();
			
			for(it = cidm_aux.begin(); it != cidm_aux.end(); it++){
				cidm_sol.push_back(*it);
			}
			
			k = 0;		// PARA CRITERIO DE PARADA
		}
		
		k++;
	}
	
	return res;
}


#endif // CIDM_GRASP_H_INCLUDED
