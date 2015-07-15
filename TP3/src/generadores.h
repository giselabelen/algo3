#ifndef GENERADORES_H_INCLUDED
#define GENERADORES_H_INCLUDED

#include <ctime>
#include <cstdlib>
#include "CIDM_exacto.h"

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef pair<int,list<int> > Sl;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Vecinos generar_solitarios(int n);
Vecinos generar_aleatorio(int n, int a);
Vecinos generar_k2_ord(int k);
Vecinos generar_k2_rnd(int k);
Vecinos generar_completo(int n);
//~ Vecinos generar_estrella(int& n,int min,int max,int& sol);
Vecinos generar_estrella(int grado_int, int& n);
Vecinos generar_circuito_ord(int n);
Vecinos generar_circuito_rnd(int n);
//~ Vecinos generar_galaxia(int& n,int min,int med,int max,int& sol);
Vecinos generar_galaxia(int grado_int,int& n);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

Vecinos generar_k2_ord(int k)
{
	Vecinos vec(2*k);
	
	for(int i = 0; i < 2*k; i = i+2)
	{
		(vec[i].first).push_back(i+1);
		(vec[i+1].first).push_back(i);
		
		vec[i].second = 1;
		vec[i+1].second = 1;
	}
	
	return vec;
}


Vecinos generar_k2_rnd(int k)
{
	int n = 2*k;
	int n1;
	int n2;
	int aux;
	list<int> nodos;
	list<int>::iterator it;
	Vecinos vec(n);
	
	for(int i = 0; i < n; i++){	nodos.push_back(i);	}
		
	while(n > 0)
	{
		// NODO 1
		it = nodos.begin();
		aux = rand() % n;
		advance(it,aux);
		n1 = *it;
		it = nodos.erase(it);
		n--;
		
		// NODO 2
		it = nodos.begin();
		aux = rand() % n;
		advance(it,aux);
		n2 = *it;
		it = nodos.erase(it);
		n--;
		
		(vec[n1].first).push_back(n2);
		(vec[n2].first).push_back(n1);
		
		vec[n1].second = 1;
		vec[n2].second = 1;
	}
	
	return vec;
}


Vecinos generar_solitarios(int n)
{
	Vecinos vec(n);
	
	for(int i; i < n; i++){	vec[i].second = 0; }
	
	return vec;
}


Vecinos generar_completo(int n)
{
	Vecinos vec(n);
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){
			if(i != j){ (vec[i].first).push_back(j); }
		}
		
		vec[i].second = n-1;
	}
	
	return vec;
}


Vecinos generar_aleatorio(int n, int a)
{
	int n1;			// nodo1
	int n2;			// nodo2
	int tamlg = n;
	int aux1;
	int aux2;
	list<int>::iterator itsl;
	Sl sub;
	pair<int,Sl> par;
	list<pair<int,Sl> > lg;
	list<pair<int,Sl> >::iterator itlg;
	
	Vecinos vec(n);
	
	// Armo las posibles relaciones
	for(int i = 0; i < n; i++)
	{
		list<int> sl;
		for(int j = 0; j < n; j++){
			if(i != j){ sl.push_back(j); }
		}
		sub = make_pair(n-1,sl);
		par = make_pair(i,sub);
		lg.push_back(par);
	}
	
	// Creo las aristas
	for(int h = 0; h < a; h++)
	{	
		itlg = lg.begin();		// iterador a lg
		
		// CALCULO NODO 1 
		aux1 = rand() % tamlg;
		advance(itlg,aux1);		// pos random en lg
		n1 = itlg->first;		// nodo 1
		
		itsl = ((itlg->second).second).begin();	// iterador a la sl
		aux2 = (itlg->second).first;			// cant de elementos de sl
		
		// CALCULO NODO 2
		aux1 = rand() % aux2;
		advance(itsl,aux1);		// pos random en la sl
		n2 = *itsl;				// nodo 2
		
		// ACTUALIZO RELACIONES
		((itlg->second).second).erase(itsl);	// elimino esa relacion
		(itlg->second).first--;
		
		if((itlg->second).first == 0){
			lg.erase(itlg);
			tamlg--;
		}
		
		for(itlg = lg.begin(); (itlg->first) != n2; itlg++){}
		
		for(itsl = ((itlg->second).second).begin(); *itsl != n1; itsl++){}
		
		((itlg->second).second).erase(itsl);	// elimino al compadre
		(itlg->second).first--;
		
		if((itlg->second).first == 0){
			lg.erase(itlg);
			tamlg--;
		}
		
		// AGREGO LA ARISTA
		(vec[n1].first).push_back(n2);
		(vec[n2].first).push_back(n1);
		vec[n1].second++;
		vec[n2].second++;
	}
	
	return vec;
}
//~ 
//~ Vecinos generar_estrella(int& n,int min,int max,int& sol)
//~ {
	//~ int aux1 = (rand() % (max-min+1)) + min;
	//~ int aux2;
	//~ int i;
	//~ int j;
	//~ list<int> cant_nodos;
	//~ list<int>::iterator it;
	//~ 
	//~ cant_nodos.push_back(aux1);
	//~ sol = aux1;
	//~ 
	//~ for(i = 0; i < aux1; i++)
	//~ {
		//~ aux2 = (rand() % (aux1 - 4)) + 3;
		//~ cant_nodos.push_back(aux2);
	//~ }
	//~ 
	//~ n = 1;
	//~ for(it = cant_nodos.begin(); it != cant_nodos.end(); it++){	n = n + *it; }
	//~ 
	//~ Vecinos vec(n);
	//~ i = 0;
	//~ j = 1;
	//~ 
	//~ for(it = cant_nodos.begin(); it != cant_nodos.end(); it++)
	//~ {
		//~ for(int h = 0; h < *it; h++)
		//~ {
			//~ (vec[i].first).push_back(j);
			//~ (vec[j].first).push_back(i);
			//~ 
			//~ if(i != 0){ vec[j].second = 1; }
			//~ 
			//~ j++;
		//~ }
		//~ 
		//~ if(i == 0){	vec[i].second = *it; }
		//~ else{ vec[i].second = *it + 1; }
		//~ i++;
	//~ }
	//~ 
	//~ return vec;
//~ }

Vecinos generar_estrella(int grado_int, int& n)
{
	int aux;
	int i;
	int j;
	list<int> cant_nodos;
	list<int>::iterator it;
	
	cant_nodos.push_back(grado_int);
	
	for(i = 0; i < grado_int; i++)
	{
		aux = (rand() % (grado_int - 4)) + 3;
		cant_nodos.push_back(aux);
	}
	
	n = 1;
	for(it = cant_nodos.begin(); it != cant_nodos.end(); it++){	n += *it; }
	
	Vecinos vec(n);
	i = 0;
	j = 1;
	
	for(it = cant_nodos.begin(); it != cant_nodos.end(); it++)
	{
		for(int h = 0; h < *it; h++)
		{
			(vec[i].first).push_back(j);
			(vec[j].first).push_back(i);
			
			if(i != 0){ vec[j].second = 1; }
			
			j++;
		}
		
		if(i == 0){	vec[i].second = *it; }
		else{ vec[i].second = *it + 1; }
		i++;
	}
	
	return vec;
}


Vecinos generar_circuito_ord(int n)
{
	Vecinos vec(n);
	
	for(int i = 0; i < n-1; i++)
	{
		(vec[i].first).push_back(i+1);
		(vec[i+1].first).push_back(i);
		vec[i].second = 2;
	}
	
	(vec[0].first).push_back(n-1);
	(vec[n-1].first).push_back(0);
	vec[n-1].second = 2;
	
	return vec;
}


Vecinos generar_circuito_rnd(int n)
{
	int n1;
	int n2;
	int n_aux;
	int n_copia = n;
	int aux;
	list<int> nodos;
	list<int>::iterator it;
	Vecinos vec(n);
	
	for(int i = 0; i < n; i++){	nodos.push_back(i);	}
	
	// NODO 1
	it = nodos.begin();
	aux = rand() % n;
	advance(it,aux);
	n1 = *it;
	it = nodos.erase(it);
	n--;
	
	n_aux = n1;
	
	while(n > 0)
	{
		// NODO 2
		it = nodos.begin();
		aux = rand() % n;
		advance(it,aux);
		n2 = *it;
		it = nodos.erase(it);
		n--;
		
		(vec[n1].first).push_back(n2);
		(vec[n2].first).push_back(n1);
		
		n1 = n2;
	}
	
	(vec[n1].first).push_back(n_aux);
	(vec[n_aux].first).push_back(n1);
	
	for(int i = 0; i < n_copia; i++){ vec[i].second = 2; }
	
	return vec;
}


//~ Vecinos generar_galaxia(int& n,int min,int med,int max,int& sol)
//~ {
	//~ int aux1 = (rand() % (med-min+1)) + min;
	//~ int aux2;
	//~ int i;
	//~ int j;
	//~ list<int> cant_nodos;
	//~ list<int>::iterator it;
	//~ 
	//~ cant_nodos.push_back(aux1);
	//~ sol = aux1;
	//~ 
	//~ for(i = 0; i < aux1; i++)
	//~ {
		//~ aux2 = (rand() % ((max+1) - aux1)) + aux1;
		//~ cant_nodos.push_back(aux2);
	//~ }
	//~ 
	//~ n = 1;
	//~ for(it = cant_nodos.begin(); it != cant_nodos.end(); it++){	n = n + *it; }
	//~ 
	//~ Vecinos vec(n);
	//~ i = 0;
	//~ j = 1;
	//~ 
	//~ for(it = cant_nodos.begin(); it != cant_nodos.end(); it++)
	//~ {
		//~ for(int h = 0; h < *it; h++)
		//~ {
			//~ (vec[i].first).push_back(j);
			//~ (vec[j].first).push_back(i);
			//~ 
			//~ if(i != 0){ vec[j].second = 1; }
			//~ 
			//~ j++;
		//~ }
		//~ 
		//~ if(i == 0){	vec[i].second = *it; }
		//~ else{ vec[i].second = *it + 1; }
		//~ i++;
	//~ }
	//~ 
	//~ return vec;
//~ }
Vecinos generar_galaxia(int grado_int,int& n)
{
	int max = 2*grado_int;
	int aux;
	int i;
	int j;
	list<int> cant_nodos;
	list<int>::iterator it;
	
	cant_nodos.push_back(grado_int);
	
	for(i = 0; i < grado_int; i++)
	{
		aux = (rand() % ((max+1) - grado_int)) + grado_int;
		cant_nodos.push_back(aux);
	}
	
	n = 1;
	for(it = cant_nodos.begin(); it != cant_nodos.end(); it++){	n = n + *it; }
	
	Vecinos vec(n);
	i = 0;
	j = 1;
	
	for(it = cant_nodos.begin(); it != cant_nodos.end(); it++)
	{
		for(int h = 0; h < *it; h++)
		{
			(vec[i].first).push_back(j);
			(vec[j].first).push_back(i);
			
			if(i != 0){ vec[j].second = 1; }
			
			j++;
		}
		
		if(i == 0){	vec[i].second = *it; }
		else{ vec[i].second = *it + 1; }
		i++;
	}
	
	return vec;
}


#endif // GENERADORES_H_INCLUDED
