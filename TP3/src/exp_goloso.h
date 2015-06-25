#ifndef EXP_GOLOSO_H_INCLUDED
#define EXP_GOLOSO_INCLUDED

#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_goloso_solitarios(int cant_min,int cant_max);
void exp_goloso_completos(int cant_min,int cant_max);
void exp_goloso_aleatorio(int cant_min,int cant_max,int cant_it);
void exp_goloso_aleatorio_comp(int cant_min,int cant_max,int cant_it);
void exp_goloso_estrellas(int min,int max,int cant_it);
void exp_goloso_circuito_ord(int min, int max);
void exp_goloso_circuito_rnd(int min, int max);
void exp_goloso_galaxias(int min,int med,int max,int cant_it);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_goloso_solitarios(int cant_min,int cant_max)
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/solitarios.txt","w");
	clock_t start;
	clock_t end;
	double t;	
	int res;
	list<int> cidm_sol;
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
		t = 0;
		Vecinos vec = generar_solitarios(n);
		Vecinos vec_aux(n);
		
		for(int i = 0; i < 20; i++)
		{
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; j < n; j++)
			{
				(vec_aux[j].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[j].first).push_back(*it); }
			}
			
			// Mido el tiempo
			start = clock();
			res = goloso(cidm_sol,vec_aux,n,0,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",n,t/20,res);
	}

	fclose(pExp);
}


void exp_goloso_completos(int cant_min,int cant_max)
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/completos.txt","w"); // Resultados de tiempo
	clock_t start;
	clock_t end;
	double t;
	int res;
	list<int> cidm_sol;
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
		t = 0;
		Vecinos vec = generar_completo(n);
		Vecinos vec_aux(n);
		
		for(int i = 0; i < 20; i++)
		{
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; j < n; j++)
			{
				(vec_aux[j].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[j].first).push_back(*it); }
			}
			
			// Mido el tiempo
			start = clock();
			res = goloso(cidm_sol,vec_aux,n,0,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %f, %i \n",n,t/20,res);
	}

	fclose(pExp);
}


void exp_goloso_aleatorio(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/aleatorio.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int a;
	int n;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
		t = 0;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		Vecinos vec_aux(n);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,a);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		for(int i = 0; i < 20; i++)
		{
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; j < n; j++)
			{
				(vec_aux[j].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[j].first).push_back(*it); }
			}
			
			// Mido el tiempo
			start = clock();
			res = goloso(cidm_sol,vec_aux,n,0,0);
			end = clock();
			t = t + difftime(end,start);
		}
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %i, %f, %i \n",n,a,t/20,res);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_aleatorio_comp(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/aleatorio_comp.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/aleatorio_comp.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int a;
	int n;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
		t = 0;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,a);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		// Acomodo las variables
		cota = n;
		res = 0;
		vector<int> estado(n,0);
		
		backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0,0);

		fprintf(pExp,"%i, %i, %i, ",n,a,cota);

		cidm_sol.clear();
		
		res = goloso(cidm_sol,vec,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i \n",res);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_estrellas(int min,int max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/estrellas.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/estrellas.in","w");	// Instancias de entrada

	int n;
	int res;
	int sol;
	list<int> cidm_sol;
	
	for(int k = 0; k < cant_it; k++)
	{	
		cout << "iteracion " << k << endl;
		Vecinos vec = generar_estrella(n,min,max,sol);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i \n",n);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		// Resuelvo
		cidm_sol.clear();
		res = goloso(cidm_sol,vec,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %i, %i \n",n,res,sol);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_circuito_ord(int min, int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/circuito_ord.txt","w");

	int res;
	list<int> cidm_sol;
	
	for(int n = min; n < max+1; n++)
	{
		cout << n << " nodos" << endl;
		Vecinos vec = generar_circuito_ord(n);
		
		// Resuelvo
		cidm_sol.clear();
		res = goloso(cidm_sol,vec,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %i \n",n,res);
	}

	fclose(pExp);
}


void exp_goloso_circuito_rnd(int min, int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/circuito_rnd.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/circuito_rnd.in","w");	// Instancias de entrada

	int res;
	list<int> cidm_sol;
	
	for(int n = min; n < max+1; n++)
	{	
		cout << n << " nodos" << endl;
		Vecinos vec = generar_circuito_rnd(n);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i \n",n);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		// Resuelvo
		cidm_sol.clear();
		res = goloso(cidm_sol,vec,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %i \n",n,res);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_galaxias(int min,int med,int max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/galaxias.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/galaxias.in","w");	// Instancias de entrada

	int n;
	int res;
	int sol;
	list<int> cidm_sol;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion" << k << endl;
		Vecinos vec = generar_galaxia(n,min,med,max,sol);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i \n",n);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		// Resuelvo
		cidm_sol.clear();
		res = goloso(cidm_sol,vec,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i, %i, %i \n",n,res,sol);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}

#endif // EXP_GOLOSO_H_INCLUDED
