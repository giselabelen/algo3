#ifndef EXP_EXACTO_H_INCLUDED
#define EXP_EXACTO_H_INCLUDED

#include <iostream>
#include "generadores.h"
#include "auxiliares.h"

using namespace std;

/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_exacto_solitarios(int cant_min, int cant_max);
void exp_exacto_completos(int cant_min, int cant_max);
void exp_exacto_k2_ord(int cant);
void exp_exacto_k2_rnd(int cant);
void exp_exacto_aleatorio(int cant_min,int cant_max,int cant_it);

void correr_exacto(Vecinos vec, vector<int> estado, int n, FILE* pExp);
void correr_exacto_bis(Vecinos vec, vector<int> estado, int n, FILE* pExp);


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
		
		correr_exacto(vec, estado, n, pExp);
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
		
		correr_exacto(vec, estado, n, pExp);
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
		
		correr_exacto(vec, estado, 2*k, pExp);
	}
	
	fclose(pExp);
}


void exp_exacto_k2_rnd(int cant)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/k2_rnd.txt","w");// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/k2_rnd.in","w");	// Instancias de entrada
		
	for(int k = 1; k < cant+1; k++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << k << " componentes, iteración " << i << endl;
			
			fprintf(pExp,"%i, ",2*k);
			
			Vecinos vec = generar_k2_rnd(k);
			vector<int> estado(2*k);
			
			imp_instancia(pIn, 2*k, k, vec);
			
			correr_exacto(vec, estado, 2*k, pExp);
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_exacto_aleatorio(int cant_min,int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/exacto/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/aleatorio.in","w");	// Instancias de entrada
	int a;
	
	for(int n = cant_min; n < cant_max; n++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << n << " nodos, iteración " << i << endl;
			
			a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
			Vecinos vec = generar_aleatorio(n,a);
			vector<int> estado(n);
			
			fprintf(pExp,"%i, %i, ",n,a);
			
			imp_instancia(pIn, n, a, vec);
			
			correr_exacto(vec, estado, n, pExp);
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void correr_exacto(Vecinos vec, vector<int> estado, int n, FILE* pExp)
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


void correr_exacto_bis(Vecinos vec, vector<int> estado, int n, FILE* pExp)
{
	clock_t start;
	clock_t end;
	double t;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	list<double> tiempos;

	for(int i = 0; i < 20; i++)
	{				
		// Limpio las variables
		cidm.clear();
		cidm_sol.clear();
		for(int j = 0; j < n; j++){ estado[j] = 0; }
		cota = n;	
		res = 0;
		
		// Mido el tiempo
		start = clock();
		backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0,1);
		end = clock();
		t = difftime(end,start);
		tiempos.push_back(t);
	}
	
	// Imprimo los resultados
	sacar_outliers(tiempos);
	t = promediar(tiempos);
	fprintf(pExp,"%f, %i, ",t,cota);
}


#endif // EXP_EXACTO_H_INCLUDED
