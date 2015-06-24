#ifndef EXP_EXACTO_H_INCLUDED
#define EXP_EXACTO_H_INCLUDED

#include "generadores.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_exacto_solitarios(int cant_min, int cant_max);
void exp_exacto_completos(int cant_min, int cant_max);
void exp_exacto_k2_ord(int cant);
void exp_exacto_k2_rnd(int cant);
void exp_exacto_aleatorio(int cant_min,int cant_max,int cant_it);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_exacto_solitarios(int cant_min, int cant_max)
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
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		t = 0;
		Vecinos vec = generar_solitarios(n);
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


void exp_exacto_completos(int cant_min, int cant_max)
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
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		t = 0;
		Vecinos vec = generar_completo(n);
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


void exp_exacto_k2_ord(int cant)
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
	
	for(int k = 1; k < cant+1; k++)
	{
		t = 0;
		Vecinos vec = generar_k2_ord(k);
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


void exp_exacto_k2_rnd(int cant)
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
	
	for(int k = 1; k < cant+1; k++)
	{
		t = 0;
		Vecinos vec = generar_k2_rnd(k);
		vector<int> estado(2*k);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",2*k,k);
	
		for(int i = 0; i < 2*k; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
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


void exp_exacto_aleatorio(int cant_min,int cant_max,int cant_it)
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
	
	for(int k = 0; k < cant_it; k++)
	{
		t = 0;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;	
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		vector<int> estado(n);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,m);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
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
