#ifndef EXP_EXACTO_H_INCLUDED
#define EXP_EXACTO_H_INCLUDED

#include <iostream>
#include "generadores.h"

using namespace std;

/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_exacto_solitarios(int cant_min, int cant_max);
void exp_exacto_completos(int cant_min, int cant_max);
void exp_exacto_k2_ord(int cant);
void exp_exacto_k2_rnd(int cant);
void exp_exacto_aleatorio(int cant_min,int cant_max,int cant_it);
void sacar_outliers(list<double>& lista);
double promediar(list<double> lista);
void correr(Vecinos vec, vector<int> estado, int n, FILE* pExp);
void imp_instancia(FILE* pIn, int n, int a, Vecinos vec);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_exacto_solitarios(int cant_min, int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/solitarios.txt","w");
		
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
		
		fprintf(pExp,"%i, ",n);
		
		Vecinos vec = generar_solitarios(n);
		vector<int> estado(n);
		
		correr(vec, estado, n, pExp);
	}
	
	fclose(pExp);
}


void exp_exacto_completos(int cant_min, int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/completos.txt","w");
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
		
		fprintf(pExp,"%i, ",n);
		
		Vecinos vec = generar_completo(n);
		vector<int> estado(n);
		
		correr(vec, estado, n, pExp);
	}
	
	fclose(pExp);
}


void exp_exacto_k2_ord(int cant)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/k2_ord.txt","w");
	
	for(int k = 1; k < cant+1; k++)
	{
		cout << k << " componentes" << endl;
		
		fprintf(pExp,"%i, ",2*k);
		
		Vecinos vec = generar_k2_ord(k);
		vector<int> estado(2*k);
		
		correr(vec, estado, 2*k, pExp);
	}
	
	fclose(pExp);
}


void exp_exacto_k2_rnd(int cant)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/k2_rnd.txt","w");// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/k2_rnd.in","w");	// Instancias de entrada
		
	for(int k = 1; k < cant+1; k++)
	{
		cout << k << " componentes" << endl;
		
		fprintf(pExp,"%i, ",2*k);
		
		Vecinos vec = generar_k2_rnd(k);
		vector<int> estado(2*k);
		
		imp_instancia(pIn, 2*k, k, vec);
		
		correr(vec, estado, 2*k, pExp);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_exacto_aleatorio(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/aleatorio.in","w");	// Instancias de entrada
	int a;
	int n;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
		
		n = (rand() % (cant_max-cant_min+1)) + cant_min;	
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		vector<int> estado(n);
		
		fprintf(pExp,"%i, %i, ",n,a);
		
		imp_instancia(pIn, n, a, vec);
		
		correr(vec, estado, n, pExp);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void imp_instancia(FILE* pIn, int n, int a, Vecinos vec)
{
	fprintf(pIn,"%i %i \n",n,a);

	for(int i = 0; i < n; i++)
	{
		for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
			fprintf(pIn,"%i %i \n",i+1,*it + 1);
		}
	}
	
	fprintf(pIn,"\n");
}


void correr(Vecinos vec, vector<int> estado, int n, FILE* pExp)
{
	clock_t start;
	clock_t end;
	double t;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	list<double> tiempos;
	
	for(int p = 0; p < 5; p++)
	{			
		for(int i = 0; i < 20; i++)
		{				
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; j < n; j++){ estado[j] = 0; }
			cota = n;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0,p);
			end = clock();
			t = difftime(end,start);
			tiempos.push_back(t);
		}
		
		// Imprimo los resultados
		sacar_outliers(tiempos);
		t = promediar(tiempos);
		fprintf(pExp,"%f, ",t);
	}
	fprintf(pExp,"%i \n",cota);
}


void sacar_outliers(list<double>& lista)
{
	list<double>::iterator it;
	list<double>::iterator min;
	list<double>::iterator max;
	
	for(int i = 0; i < 2; i++)
	{
		it = lista.begin();
		min = it;
		max = it;
		it++;
		
		while(it != lista.end())
		{
			if(*it < *min){ min = it; }
			if(*it > *max){ max = it; }
			it++;
		}
		
		min = lista.erase(min);
		max = lista.erase(max);
	}
}


double promediar(list<double> lista)
{
	double suma = 0;
	double valor = 0;
	
	for(list<double>::iterator it = lista.begin(); it != lista.end(); it++)
	{ 
		suma += *it;
		valor++;
	}
	
	return (suma/valor);
}

#endif // EXP_EXACTO_H_INCLUDED
