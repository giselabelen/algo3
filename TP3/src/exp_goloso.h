#ifndef EXP_GOLOSO_H_INCLUDED
#define EXP_GOLOSO_INCLUDED

#include "auxiliares.h"
#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_goloso_solitarios(int cant_min,int cant_max);
void exp_goloso_completos(int cant_min,int cant_max);
void exp_goloso_aleatorio(int cant_min,int cant_max,int cant_it);
void exp_goloso_aleatorio_comp(int cant_min,int cant_max,int cant_it);
//~ void exp_goloso_estrellas(int min,int max,int cant_it);
void exp_goloso_estrellas(int min,int max);
void exp_goloso_circuito_ord(int min, int max);
void exp_goloso_circuito_rnd(int min, int max);
//~ void exp_goloso_galaxias(int min,int med,int max,int cant_it);
void exp_goloso_galaxias(int min,int max);

void correr(Vecinos vec, int n, int a, FILE* pExp);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_goloso_solitarios(int cant_min,int cant_max)
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/solitarios.txt","w");
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
		
		Vecinos vec = generar_solitarios(n);
		
		correr(vec, n, 0, pExp);
	}

	fclose(pExp);
}


void exp_goloso_completos(int cant_min,int cant_max)
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/completos.txt","w"); // Resultados de tiempo
	
	for(int n = cant_min; n < cant_max+1; n++)
	{
		cout << n << " nodos" << endl;
	
		Vecinos vec = generar_completo(n);
	
		correr(vec, n, -1, pExp);
	}

	fclose(pExp);
}


void exp_goloso_aleatorio(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/aleatorio.in","w");	// Instancias de entrada
	
	int a;
	int n;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
	
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		imp_instancia(pIn, n, a, vec);
		
		correr(vec, n, a, pExp);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_aleatorio_comp(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/aleatorio_comp.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/aleatorio_comp.in","w");	// Instancias de entrada
	
	int a;
	int n;
	int res;
	int cota;
	list<int> cidm;	
	list<int> cidm_sol;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
	
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		imp_instancia(pIn, n, a, vec);
		
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

//~ 
//~ void exp_goloso_estrellas(int min,int max,int cant_it)
//~ {
	//~ FILE * pExp = fopen("../Resultados_experimentos/goloso/estrellas.txt","w");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/goloso/estrellas.in","w");	// Instancias de entrada
//~ 
	//~ int n;
	//~ int res;
	//~ int sol;
	//~ int grado_int;
	//~ list<int> cidm_sol;
	//~ 
	//~ for(int k = 0; k < cant_it; k++)
	//~ {	
		//~ cout << "iteracion " << k << endl;
		//~ Vecinos vec = generar_estrella(n,min,max,sol);
		//~ 
		//~ imp_instancia(pIn, n, -1, vec);
		//~ 
		//~ // Resuelvo
		//~ cidm_sol.clear();
		//~ res = goloso(cidm_sol,vec,n,0,0);
		//~ 
		//~ // Imprimo los resultados
		//~ fprintf(pExp,"%i, %i, %i \n",n,res,sol);
	//~ }
//~ 
	//~ // Cierro los archivos
	//~ fclose(pExp);
	//~ fclose(pIn);
//~ }

void exp_goloso_estrellas(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/estrellas.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/estrellas.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int grado_int = min; grado_int < max; grado_int += 10)
	{	
		for(int i = 0; i < 50; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_estrella(grado_int,n);
			
			imp_instancia(pIn, n, -1, vec);
			
			// Resuelvo
			cidm_sol.clear();
			res = goloso(cidm_sol,vec,n,0,0);
			
			// Imprimo los resultados
			fprintf(pExp,"%i, %i, %i \n",n,res,grado_int);
		}
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
		
		imp_instancia(pIn, n, n, vec);
		
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


//~ void exp_goloso_galaxias(int min,int med,int max,int cant_it)
//~ {
	//~ FILE * pExp = fopen("../Resultados_experimentos/goloso/galaxias.txt","w");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/goloso/galaxias.in","w");	// Instancias de entrada
//~ 
	//~ int n;
	//~ int res;
	//~ int sol;
	//~ int grado_int;
	//~ list<int> cidm_sol;
	//~ 
	//~ for(int k = 0; k < cant_it; k++)
	//~ {
		//~ cout << "iteracion" << k << endl;
		//~ Vecinos vec = generar_galaxia(n,min,med,max,sol);
		//~ 
		//~ imp_instancia(pIn, n, -1, vec);
		//~ 
		//~ // Resuelvo
		//~ cidm_sol.clear();
		//~ res = goloso(cidm_sol,vec,n,0,0);
		//~ 
		//~ // Imprimo los resultados
		//~ fprintf(pExp,"%i, %i, %i \n",n,res,sol);
	//~ }
//~ 
	//~ // Cierro los archivos
	//~ fclose(pExp);
	//~ fclose(pIn);
//~ }
void exp_goloso_galaxias(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/galaxias.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/galaxias.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int grado_int = min; grado_int < max; grado_int += 10)
	{
		for(int i = 0; i < 50; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_galaxia(grado_int, n);
			
			imp_instancia(pIn, n, -1, vec);
			
			// Resuelvo
			cidm_sol.clear();
			res = goloso(cidm_sol,vec,n,0,0);
			
			// Imprimo los resultados
			fprintf(pExp,"%i, %i, %i \n",n,res,grado_int);
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void correr(Vecinos vec, int n, int a, FILE* pExp)
{
	clock_t start;
	clock_t end;
	double t;
	int res;
	list<int> cidm_sol;
	list<double> tiempos;
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
			vec_aux[j].second = vec[j].second;
		}
		
		// Mido el tiempo
		start = clock();
		res = goloso(cidm_sol,vec_aux,n,0,0);
		end = clock();
		t = difftime(end,start);
		tiempos.push_back(t);
	}
	
	// Imprimo los resultados
	sacar_outliers(tiempos);
	t = promediar(tiempos);
	fprintf(pExp,"%i, %i, %f, %i \n",n,a,t,res);
}


#endif // EXP_GOLOSO_H_INCLUDED
