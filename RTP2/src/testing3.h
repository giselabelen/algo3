#ifndef TESTING3_H_INCLUDED
#define TESTING3_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "petroleo.h"

using namespace std;

typedef pair<int,list<int> > Sl;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Incidencia generar_grafo(int n, int a);
void unir_grafos(Incidencia& inc1, Incidencia& inc2, int& n1, int n2);
void agrandar_grafo(Incidencia& inc, int n, bool b, int a, int costo);
void testear_3_A();
void testear_3_B();
void testear_3_C();


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

Incidencia generar_grafo(int n, int a)
{
	int n1;
	int n2;
	int p;
	int tamlg = n;
	int aux1;
	int aux2;
	list<int>::iterator itsl;
	Sl sub;
	pair<int,Sl> par;
	list<pair<int,Sl> > lg;
	list<pair<int,Sl> >::iterator itlg;
	
	Arista edge;
	pair<Arista,int> con_peso;
	Incidencia inc;
	
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
	{	//cout << "a " << a << " h " << h << " tamlg " << tamlg << endl;
		itlg = lg.begin();		// iterador a lg
		p = (20 + rand() % 50);	// peso
		//~ cout << tamlg << endl;
		aux1 = rand() % tamlg;
		//~ cout << h << aux1 << endl;
		/*if (aux1 =! 0){*/ advance(itlg,aux1);	//}	// pos random en lg
		n1 = itlg->first;		// nodo 1
		itsl = ((itlg->second).second).begin();	// iterador a la sl
		aux2 = (itlg->second).first;			// cant de elementos de sl
		aux1 = rand() % aux2;
		/*if (aux1 =! 0){*/ advance(itsl,aux1);// }		// pos random en la sl
		n2 = *itsl;				// nodo 2
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
		
		edge = make_pair(n1,n2);
		con_peso = make_pair(edge,p);
		inc.push_back(con_peso);
	}
	
	return inc;
}

void unir_grafos(Incidencia& inc1, Incidencia& inc2, int& n1, int n2)
{
	int c;
	Arista edge;
	pair<Arista,int> par;
	
	for(Incidencia::iterator it = inc2.begin(); it != inc2.end(); it++)
	{
		//~ par = *it;
		//~ (par.first).first = (par.first).first + n1;
		//~ (par.first).second = (par.first).second + n1;
		(it->first).first = (it->first).first + n1;
		(it->first).second = (it->first).second + n1;
		inc1.push_back(*it);
	}
	
	n1 = n1 + n2;
	//~ inc2.clear();
	return;
}

void agrandar_grafo(Incidencia& inc, int n, bool b, int a, int costo)
{
	int n1;
	int n2;
	int p;
	int tamlg = n;
	int aux1;
	int aux2;
	list<int>::iterator itsl;
	Sl sub;
	pair<int,Sl> par;
	list<pair<int,Sl> > lg;
	list<pair<int,Sl> >::iterator itlg;
	
	Arista edge;
	pair<Arista,int> con_peso;
	
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
	
	// Quito las posibilidades que ya se usaron
	for(Incidencia::iterator it = inc.begin(); it != inc.end(); it++)
	{
		n1 = (it->first).first;
		n2 = (it->first).second;
		for(itlg = lg.begin(); (itlg->first) != n1; itlg++){ bool q = false; }
		for(itsl = ((itlg->second).second).begin(); *itsl != n2; itsl++){ bool q = false; }
		((itlg->second).second).erase(itsl);
		(itlg->second).first--;
		if((itlg->second).first == 0){
			lg.erase(itlg);
			tamlg--;
		}
		for(itlg = lg.begin(); (itlg->first) != n2; itlg++){}
		for(itsl = ((itlg->second).second).begin(); *itsl != n1; itsl++){}
		((itlg->second).second).erase(itsl);
		(itlg->second).first--;
		if((itlg->second).first == 0){
			lg.erase(itlg);
			tamlg--;
		}
	}
		
	// Creo las aristas nuevas
	if(b){ p = costo + 5; }else{ p = costo - 5; }
	for(int h = 0; h < a; h++)
	{
		itlg = lg.begin();		// iterador a lg
		
		aux1 = rand() % tamlg;
		advance(itlg,aux1);		// pos random en lg
		n1 = itlg->first;		// nodo 1
		itsl = ((itlg->second).second).begin();	// iterador a la sl
		aux2 = (itlg->second).first;			// cant de elementos de sl
		aux1 = rand() % aux2;
		advance(itsl,aux1);		// pos random en la sl
		n2 = *itsl;				// nodo 2
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
		
		edge = make_pair(n1,n2);
		con_peso = make_pair(edge,p);
		inc.push_back(con_peso);
	}
	
	return;
}

void testear_3_A()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing3A.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	

	int n1 = 10;
	int n2 = n1;
	int a = ((rand() % (n1*n1 - 2*n1 + 1)) + n1 - 1)/2;
	int cant_ref = 0;
	int cant_tub = 0;
	int costo_ref = 50;
	
	list<int> refinerias;
	list<Arista> tuberias;
	
	Incidencia inc1 = generar_grafo(n1,a);
	
	t = 0;
	for(int j = 0; j < 20; j++)
	{		
		start = clock();
		petroleo(inc1,refinerias,tuberias,n1,cant_ref,cant_tub,costo_ref);
		end = clock();
		t = t + difftime(end,start);
		
		cant_ref = 0;
		cant_tub = 0;
		refinerias.clear();
		tuberias.clear();
	}
	fprintf(pTest,"%i, %f \n",n1,t/20);
	
	for(int i = 1; i < 50; i++)
	{	
		t = 0;
		int a = ((rand() % (n2*n2 - 2*n2 + 1)) + n2 - 1)/2;
		Incidencia inc2 = generar_grafo(n2,a);
		unir_grafos(inc1,inc2,n1,n2);
	
		for(int j = 0; j < 20; j++)
		{		
			start = clock();
			petroleo(inc1,refinerias,tuberias,n1,cant_ref,cant_tub,costo_ref);
			end = clock();
			t = t + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
		}
		inc2.clear();
		fprintf(pTest,"%i, %f \n",n1,t/20);
	}

	fclose(pTest);
}

void testear_3_B()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing3B.txt","w");
	clock_t start;
	clock_t end;
	double t1 = 0;
	double t2 = 0;
	double t3 = 0;
	
	int cant_ref = 0;
	int cant_tub = 0;
	
	list<int> refinerias;
	list<Arista> tuberias;
	
	for(int i = 0; i < 50; i++)
	{	
		t1 = 0;
		t2 = 0;
		t3 = 0;
		int n1 = (2 + rand() % 50);
		int n2 = (2 + rand() % 50);
		int n3;
		int costo_ref = (40 + rand() % 60);
		int a1 = ((rand() % (n1*n1 - 2*n1 + 1)) + n1 - 1)/2;
		int a2 = ((rand() % (n2*n2 - 2*n2 + 1)) + n2 - 1)/2;
		Incidencia inc1 = generar_grafo(n1,a1);
		Incidencia inc2 = generar_grafo(n2,a2);
		Incidencia inc3;
		Incidencia inc4;
		
		for(Incidencia::iterator it = inc1.begin(); it != inc1.end(); it++){}
		for(Incidencia::iterator it = inc2.begin(); it != inc2.end(); it++){}
		
		for(int j = 0; j < 20; j++)
		{	
			for(Incidencia::iterator it = inc1.begin(); it != inc1.end(); it++){
				inc3.push_back(*it);
			}
			for(Incidencia::iterator it = inc2.begin(); it != inc2.end(); it++){
				inc4.push_back(*it);
			}
			n3 = n1;
			
			start = clock();
			petroleo(inc1,refinerias,tuberias,n1,cant_ref,cant_tub,costo_ref);
			end = clock();
			t1 = t1 + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
			
			start = clock();
			petroleo(inc2,refinerias,tuberias,n2,cant_ref,cant_tub,costo_ref);
			end = clock();
			t2 = t2 + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
						
			unir_grafos(inc3,inc4,n3,n2);
			
			start = clock();
			petroleo(inc3,refinerias,tuberias,n3,cant_ref,cant_tub,costo_ref);
			end = clock();
			t3 = t3 + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
			inc3.clear();
			inc4.clear();
		}
		
		fprintf(pTest,"%i, %f, %i, %f, %i, %f \n",n1,t1/20,n2,t2/20,n3,t3/20);
		inc1.clear();
		inc2.clear();
	}

	fclose(pTest);
}

void testear_3_C()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing3C.txt","w");
	clock_t start;
	clock_t end;
	double t1 = 0;	
	double t2 = 0;	
	double t3 = 0;	
	
	int n = 10;
	int a = ((rand() % (n*n - 2*n + 1)) + n - 1)/2;
	int m = n*n - n - a;
	int cant_ref = 0;
	int cant_tub = 0;
	int costo_ref = 50;
	
	Incidencia inc = generar_grafo(n,a);
	Incidencia inc1;
	Incidencia inc2;
	for(Incidencia::iterator it = inc.begin(); it != inc.end(); it++){
		inc1.push_back(*it);
		inc2.push_back(*it);
	}
	
	list<int> refinerias;
	list<Arista> tuberias;
	
	for(int j = 0; j < 20; j++)
	{
		start = clock();
		petroleo(inc,refinerias,tuberias,n,cant_ref,cant_tub,costo_ref);
		end = clock();
		t1 = t1 + difftime(end,start);
		
		cant_ref = 0;
		cant_tub = 0;
		refinerias.clear();
		tuberias.clear();
	}
	fprintf(pTest,"%i, %f \n",inc.size(),t1/20);
	
	for(int i = 0; i < m; i = i + 5)
	{	
		t1 = 0;
		t2 = 0;
		t3 = 0;
		agrandar_grafo(inc1,n,i,false,costo_ref);	// tub buenas
		agrandar_grafo(inc2,n,i,true,costo_ref);	// tub malas
		
		for(int j = 0; j < 20; j++)
		{		
			start = clock();
			petroleo(inc1,refinerias,tuberias,n,cant_ref,cant_tub,costo_ref);
			end = clock();
			t2 = t2 + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
			
			start = clock();
			petroleo(inc2,refinerias,tuberias,n,cant_ref,cant_tub,costo_ref);
			end = clock();
			t3 = t3 + difftime(end,start);
			
			cant_ref = 0;
			cant_tub = 0;
			refinerias.clear();
			tuberias.clear();
		}
		
		fprintf(pTest,"%i, %f, %f \n",inc1.size(),t2/20,t3/20);
	}

	fclose(pTest);
}

#endif // TESTING3_H_INCLUDED

