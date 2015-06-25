#ifndef CIDM_EXACTO_H_INCLUDED
#define CIDM_EXACTO_H_INCLUDED

#include <list>
#include <vector>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< pair< list<int>, int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

void backtracking(list<int>& cidm, list<int>& cidm_sol, vector<int>& estado, 
				Vecinos vec, int pos, int n, int& cota, int res, int cont,int podas);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void backtracking(list<int>& cidm, list<int>& cidm_sol, vector<int>& estado,
					Vecinos vec, int pos, int n, int& cota, int res, int cont,int podas)
{
	// Guardo valores iniciales para deshacer después
	int grado;					// PARA UNA PODA
	int cont_aux = cont;
	int res_aux = res;
	int pos_aux = pos;
	int est_aux = estado[pos];
	bool pasar;
	bool chequear;
	
	// si me pasé de la cota ya no me importa
	if((podas != 0) && (res > cota)){ return; }	// PODA CLÁSICA
	
	if(podas == 0){ chequear = (cont == n) && (res <= cota); }	// sin podas
	else{ chequear = (cont == n); }								// con podas
	
	// si encontré una solución, la guardo y me voy
	if(chequear)
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
		//~ grado = 0;		// PARA UNA PODA
		
		for (list<int>::iterator it = (vec[pos].first).begin(); it != (vec[pos].first).end(); it++)
		{
			if(estado[*it] == 0){ cont++; }
			estado[*it]++;
			//~ grado++;	// PARA UNA PODA
		}
		
		backtracking(cidm,cidm_sol,estado,vec,pos+1,n,cota,res,cont,podas);
	}
		
	grado = vec[pos].second;
	
	// RAMA NO LO ELIJO	
	switch(podas)
	{
		case 0:		// sin podas
			pasar = true;
			break;
		
		case 1:		// con todas las podas
			pasar = (grado != 0) && (cont != n);
			break;
		
		case 2:		// solo poda clasica
			pasar = true;
			break;
		
		case 3:		// poda clasica + nodos solitarios
			pasar = (grado != 0);
			break;
		
		case 4:		// poda clasica + nodo decisivo
			pasar = (cont != n);
			break;
	}
	
	if(est_aux == 0)
	{
		cidm.pop_back();
		estado[pos]--;

		for (list<int>::iterator it = (vec[pos].first).begin(); it != (vec[pos].first).end(); it++)
		{
			if(estado[*it] != 0){
				estado[*it]--;
			}
		}
	}
	
	if(pasar)
	{		
		backtracking(cidm,cidm_sol,estado,vec,pos+1,n,cota,res_aux,cont_aux,podas);
	}
}



#endif // CIDM_EXACTO_H_INCLUDED
