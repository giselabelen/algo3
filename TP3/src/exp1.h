#ifndef EXP1_H_INCLUDED
#define EXP1_H_INCLUDED

#include <ctime>
#include <cstdlib>
#include "CIDM_exacto.h"

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef pair<int,list<int> > Sl;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Vecinos generar_aleatorio(int n, int a);
Vecinos generar_completo(int n);
Vecinos generar_k2_ord(int k);
Vecinos generar_k2_rnd(int k);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

Vecinos generar_completo(int n)
{
	Vecinos vec(n);
	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++){
			if(i != j){ vec[i].push_back(j); }
		}
	}
	
	return vec;
}


Vecinos generar_k2_ord(int k)
{
	Vecinos vec(2*k);
	
	for(int i = 0; i < 2*k; i = i+2)
	{
		vec[i].push_back(i+1);
		vec[i+1].push_back(i);
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
		
		vec[n1].push_back(n2);
		vec[n2].push_back(n1);
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
		vec[n1].push_back(n2);
		vec[n2].push_back(n1);
	}
	
	return vec;
}







#endif // EXP1_H_INCLUDED
