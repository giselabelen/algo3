#ifndef EXP2_H_INCLUDED
#define EXP2_H_INCLUDED

#include <ctime>
#include <cstdlib>
#include "CIDM_goloso.h"

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef pair<int,list<int> > Sl;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Vecinos generar_solitarios(int n);
Vecinos generar_aleatorio(int n, int a);
Vecinos generar_completo(int n);
Vecinos generar_estrella(int& n);
Vecinos generar_circuito(int n);
Vecinos generar_galaxia(int& n);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

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

Vecinos generar_estrella(int& n)
{
	int aux1 = (rand() % 6) + 5;	// PARAMETRIZAR ESTOS VALORES - ahora esta de 5 a 10
	int aux2;
	int i;
	int j;
	list<int> cant_nodos;
	list<int>::iterator it;
	
	cant_nodos.push_back(aux1);
	
	for(i = 0; i < aux1; i++)
	{
		aux2 = (rand() % (aux1 - 5)) + 3;
		cant_nodos.push_back(aux2);
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
			j++;
		}
		
		if(i == 0){	vec[i].second = *it; }
		else{ vec[i].second = *it + 1; }
		i++;
	}
	
	return vec;
}


Vecinos generar_circuito(int n)
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


Vecinos generar_galaxia(int& n)
{
	int aux1 = (rand() % 5) + 6;	// PARAMETRIZAR ESTOS VALORES - ahora esta de 6 a 10
	int aux2;
	int i;
	int j;
	list<int> cant_nodos;
	list<int>::iterator it;
	
	cant_nodos.push_back(aux1);
	
	for(i = 0; i < aux1; i++)
	{
		aux2 = (rand() % (21 - aux1)) + aux1;	// PARAMETRIZAR ESTE VALOR - ahora está hasta 20
		cant_nodos.push_back(aux2);
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
			j++;
		}
		
		if(i == 0){	vec[i].second = *it; }
		else{ vec[i].second = *it + 1; }
		i++;
	}
	
	return vec;
}


#endif // EXP2_H_INCLUDED
