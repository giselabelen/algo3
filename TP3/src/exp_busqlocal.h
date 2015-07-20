#ifndef EXP_BUSQLOCAL_H_INCLUDED
#define EXP_BUSQLOCAL_INCLUDED

#include "auxiliares.h"
#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_busqlocal_aleatorio(int cant_min,int cant_max);
void exp_busqlocal_aleatorio_comp(int cant_min,int cant_max);
void exp_busqlocal_estrellas(int min,int max);
void exp_busqlocal_circuito_ord(int min, int max);
void exp_busqlocal_circuito_rnd(int min, int max);
void exp_busqlocal_galaxias(int min,int max);

void correr_busqlocal(Vecinos vec, int n, int p, FILE* pExp);
void correr_busqlocal_bis(Vecinos vec, int n, FILE* pExp);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_busqlocal_aleatorio(int cant_min,int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio.in","w");	// Instancias de entrada
	
	int a;
	
	for(int n = cant_min; n <= cant_max; n++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << n << " nodos, iteracion " << i << endl;
			
			a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
			Vecinos vec = generar_aleatorio(n,a);
			
			fprintf(pExp,"%i, %i, ",n,a);
			
			imp_instancia(pIn, n, a, vec);
			
			for(int p = 1; p < 3; p++){ correr_busqlocal(vec, n, p, pExp); }
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}

void exp_busqlocal_aleatorio_comp(int cant_min,int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.in","w");	// Instancias de entrada
	
	int a;
	int res1;
	int res2;
	list<int> cidm_sol1;
	list<int> cidm_sol2;
	int cota;
	
	for(int n = cant_min; n <= cant_max; n++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << n << " nodos, iteracion " << i << endl;
			
			a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
			Vecinos vec = generar_aleatorio(n,a);
			Vecinos vec_aux(n);
			
			fprintf(pExp,"%i, %i, ",n,a);
			
			imp_instancia(pIn, n, a, vec);
			
			cota = n;
			res1 = 0;
			vector<int> estado(n,0);
			
			backtracking(cidm_sol2,cidm_sol1,estado,vec,0,n,cota,res1,0,1);

			fprintf(pExp,"%i, ",cota);
			
			for(int p = 1; p < 3; p++)
			{
				// Acomodo las variables
				cidm_sol1.clear();
				cidm_sol2.clear();
				
				Vecinos vec_aux = copiar_vec(vec,n);
				
				res1 = goloso(cidm_sol1,vec_aux,n,0,0);
				res2 = otro_inicio(cidm_sol2,vec,n);
				
				busqueda(cidm_sol1,vec,n,res1,p);
				busqueda(cidm_sol2,vec,n,res2,p);
							
				// Imprimo los resultados
				fprintf(pExp,"%i, %i, ",res1,res2);
			}
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_busqlocal_estrellas(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/estrellas.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/estrellas.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int grado_int = min; grado_int < max; grado_int++)
	{	
		for(int i = 0; i < 20; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_estrella(grado_int,n);
			
			imp_instancia(pIn, n, -1, vec);
			
			fprintf(pExp,"%i, ",n);
		
			for(int p = 1; p < 3; p++){ correr_busqlocal(vec, n, p, pExp); }
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_busqlocal_circuito_ord(int min, int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/circuito_ord.txt","w");

	int res;
	list<int> cidm_sol;
	
	for(int n = min; n < max+1; n++)
	{
		cout << n << " nodos" << endl;
		
		Vecinos vec = generar_circuito_ord(n);
		
		fprintf(pExp,"%i, ",n);
		
		for(int p = 1; p < 3; p++){ correr_busqlocal(vec, n, p, pExp); }
		
		fprintf(pExp,"\n");
	}

	fclose(pExp);
}


void exp_busqlocal_circuito_rnd(int min, int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/circuito_rnd.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/circuito_rnd.in","w");	// Instancias de entrada

	int res;
	list<int> cidm_sol;
	
	for(int n = min; n < max+1; n++)
	{	
		cout << n << " nodos" << endl;
		
		Vecinos vec = generar_circuito_rnd(n);
		
		imp_instancia(pIn, n, n, vec);
		
		fprintf(pExp,"%i, ",n);
		
		for(int p = 1; p < 3; p++){ correr_busqlocal(vec, n, p, pExp); }
		
		fprintf(pExp,"\n");
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_busqlocal_galaxias(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/galaxias.txt","a");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/galaxias.in","a");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int grado_int = min; grado_int < max; grado_int++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_galaxia(grado_int, n);
			
			imp_instancia(pIn, n, -1, vec);
			
			fprintf(pExp,"%i, ",n);
			
			for(int p = 1; p < 3; p++){ correr_busqlocal(vec, n, p, pExp); }
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void correr_busqlocal(Vecinos vec, int n, int p, FILE* pExp)
{
	clock_t start;
	clock_t end;
	double t1;
	double t2;
	int res1;
	int res2;
	list<int> cidm_sol1;
	list<int> cidm_sol2;
	list<double> tiempos1;
	list<double> tiempos2;

	for(int i = 0; i < 20; i++)
	{
		// Acomodo las variables
		t1 = 0;
		t2 = 0;
		
		cidm_sol1.clear();
		cidm_sol2.clear();
		
		Vecinos vec_aux = copiar_vec(vec,n);
		
		// Mido el tiempo
		start = clock();
		res1 = goloso(cidm_sol1,vec_aux,n,0,0);
		end = clock();
		t1 = t1 + difftime(end,start);
		
		start = clock();
		res2 = otro_inicio(cidm_sol2,vec,n);
		end = clock();
		t2 = t2 + difftime(end,start);
		
		if(i == 0){ fprintf(pExp,"%i, %i, ",res1,res2); }
		
		start = clock();
		busqueda(cidm_sol1,vec,n,res1,p);
		end = clock();
		t1 = t1 + difftime(end,start);
		tiempos1.push_back(t1);
		
		start = clock();
		busqueda(cidm_sol2,vec,n,res2,p);
		end = clock();
		t2 = t2 + difftime(end,start);
		tiempos2.push_back(t2);
	}

	// Imprimo los resultados
	sacar_outliers(tiempos1);
	sacar_outliers(tiempos2);
	t1 = promediar(tiempos1);
	t2 = promediar(tiempos2);
	fprintf(pExp,"%f, %i, %f, %i, ",t1,res1,t2,res2);
}


void correr_busqlocal_bis(Vecinos vec, int n, FILE* pExp)
{
	clock_t start;
	clock_t end;
	double t;
	int res;
	list<int> cidm_sol;
	list<double> tiempos;

	for(int i = 0; i < 20; i++)
	{
		// Acomodo las variables
		cidm_sol.clear();
		
		Vecinos vec_aux = copiar_vec(vec,n);
		
		// Mido el tiempo
		start = clock();
		res = goloso(cidm_sol,vec_aux,n,0,0);
		end = clock();
		t = difftime(end,start);
		
		start = clock();
		busqueda(cidm_sol,vec,n,res,2);
		end = clock();
		t += difftime(end,start);
		tiempos.push_back(t);
	}

	// Imprimo los resultados
	sacar_outliers(tiempos);
	t = promediar(tiempos);
	fprintf(pExp,"%f, %i, ",t,res);
}


#endif // EXP_BUSQLOCAL_H_INCLUDED
