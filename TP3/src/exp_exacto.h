#ifndef EXP_EXACTO_H_INCLUDED
#define EXP_EXACTO_H_INCLUDED

#include "generadores.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_exacto_solitarios();
void exp_exacto_completos();
void exp_exacto_k2_ord();
void exp_exacto_k2_rnd();
void exp_exacto_aleatorio();


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_exacto_solitarios()
{
	// CORRER UNA VEZ CON CADA PODA
	
	FILE * pExp = fopen("../Resultados_experimentos/exacto/solitarios.txt","w");
	clock_t start;
	clock_t end;
	double t;	
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int n = 3; n < 21; n++)
	{
		t = 0;
		Vec vec(n);
		vector<int> estado(n);
	
		for(int i = 0; i < 20; i++)
		{
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; i < n; i++){ estado[i] = 0; }
			cota = n;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",n,t/20,cota);
	}
	
	fclose(pExp);
}


void exp_exacto_completos()
{
	// CORRER UNA VEZ CON CADA PODA
	
	FILE * pExp = fopen("../Resultados_experimentos/exacto/completos.txt","w");
	clock_t start;
	clock_t end;
	double t;
	int m;	
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int n = 3; n < 21; n++)
	{
		t = 0;
		m = n*(n-1)/2;
		Vec vec = gen_completo(n);
		vector<int> estado(n);
		
		for(int i = 0; i < 20; i++)
		{
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; i < n; i++){ estado[i] = 0; }
			cota = n;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",n,t/20,cota);
	}

	fclose(pExp);
}


void exp_exacto_k2_ord()
{
	// CORRER UNA VEZ CON CADA PODA
	
	FILE * pExp = fopen("../Resultados_experimentos/exacto/k2_ord.txt","w");
	clock_t start;
	clock_t end;
	double t;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int k = 1; k < 11; k++)
	{
		t = 0;
		Vec vec = gen_k2_ord(k);
		vector<int> estado(2*k);
		
		for(int i = 0; i < 20; i++)
		{
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; i < 2*k; i++){ estado[i] = 0; }
			cota = 2*k;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,2*k,cota,res,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",2*k,t/20,cota);
	}
	
	fclose(pExp);
}


void exp_exacto_k2_rnd()
{
	// CORRER UNA VEZ CON CADA PODA
	
	FILE * pExp = fopen("../Resultados_experimentos/exacto/k2_rnd.txt","w");// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/k2_rnd.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int k = 1; k < 11; k++)
	{
		t = 0;
		Vec vec = gen_k2_rnd(k);
		vector<int> estado(2*k);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",2*k,k);
	
		for(int i = 0; i < 2*k; i++)
		{
			for (list<int>::iterator it = vec[i].begin(); it != vec[i].end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		for(int i = 0; i < 20; i++)
		{
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; i < 2*k; i++){ estado[i] = 0; }
			cota = 2*k;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,2*k,cota,res,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",2*k,t/20,cota);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_exacto_aleatorio()
{
	// CORRER UNA VEZ CON CADA PODA
	
	FILE * pExp = fopen("../Resultados_experimentos/exacto/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/exacto/aleatorio.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int a;
	int n;
	int m;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int k = 0; k < 100; k++)
	{
		t = 0;
		n = (rand() % 11) + 2;			// random entre 2 y 12
		a = rand() % ((n*(n-1)/2)+1);	// Cantidad aleatoria de aristas
		Vec vec = gen_aleatorio(n,a);
		vector<int> estado(n);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,m);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = vec[i].begin(); it != vec[i].end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		for(int i = 0; i < 20; i++)
		{
			// Limpio las variables
			cidm.clear();
			cidm_sol.clear();
			for(int j = 0; i < n; i++){ estado[i] = 0; }
			cota = n;			// VER SI ACHICAMOS ESTO CON EL GOLOSO O NO
			res = 0;
			
			// Mido el tiempo
			start = clock();
			backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",n,t/20,cota);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


#endif // EXP_EXACTO_H_INCLUDED
