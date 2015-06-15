#ifndef CIDM_EXACTO_H_INCLUDED
#define CIDM_EXACTO_H_INCLUDED

#include <list>
#include <vector>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< list<int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

void backtracking(list<int>& cidm, list<int>& cidm_sol, vector<int>& estado, 
				Vecinos vec, int pos, int n, int& cota, int res, int cont);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void backtracking(list<int>& cidm, list<int>& cidm_sol, vector<int>& estado,
					Vecinos vec, int pos, int n, int& cota, int res, int cont)
{
	// Guardo valores iniciales para deshacer después
	int grado;					// PARA UNA PODA
	int cont_aux = cont;
	int res_aux = res;
	int pos_aux = pos;
	int est_aux = estado[pos];
	
	// si me pasé de la cota ya no me importa
	if(res > cota){ return; }	// PODA CLÁSICA
	
	// si encontré una solución, la guardo y me voy
	if(cont == n)
	{
		cidm_sol.clear();
		for (list<int>::iterator it = cidm.begin(); it != cidm.end(); it++){
			cidm_sol.push_back(*it);
		}
		cota = res;
		return;	
	}
	
	// si terminé de mirar y no encontré nada, me voy
	if(pos == n){ return; }
	
	
	// RAMA SÍ LO ELIJO
	if(est_aux == 0)
	{
		cidm.push_back(pos);
		estado[pos]++;
		res++;
		cont++;
		grado = 0;		// PARA UNA PODA
		
		for (list<int>::iterator it = vec[pos].begin(); it != vec[pos].end(); it++)
		{
			if(estado[*it] == 0){ cont++; }
			estado[*it]++;
			grado++;	// PARA UNA PODA
		}
		
		backtracking(cidm,cidm_sol,estado,vec,pos+1,n,cota,res,cont);
	}
		
	// RAMA NO LO ELIJO
	if((grado != 0) || (cont != n))		// PARA DOS PODAS
	{
		if(est_aux == 0)
		{
			cidm.pop_back();
			estado[pos]--;

			for (list<int>::iterator it = vec[pos].begin(); it != vec[pos].end(); it++)
			{
				if(estado[*it] != 0){
					estado[*it]--;
				}
			}
		}
		
		backtracking(cidm,cidm_sol,estado,vec,pos+1,n,cota,res_aux,cont_aux);
	}
}



#endif // CIDM_EXACTO_H_INCLUDED
