#ifndef EXP_GOLOSO_H_INCLUDED
#define EXP_GOLOSO_INCLUDED

#include "generadores.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_goloso_solitarios();
void exp_goloso_completos();
void exp_goloso_aleatorio();
void exp_goloso_estrellas();

void exp_goloso_galaxias();


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_goloso_solitarios()
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/solitarios.txt","w");
	clock_t start;
	clock_t end;
	double t;	
	int res;
	list<int> cidm_sol;
	
	for(int n = 3; n < 21; n++)
	{
		t = 0;
		Vecinos vec = generar_solitarios(n);
		Vecinos vec_aux(n);
		
		for(int i = 0; i < 20; i++)
		{
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; i < n; i++)
			{
				(vec_aux[i].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[i].first).push_back(*it); }
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


void exp_goloso_completos()
{	
	FILE * pExp = fopen("../Resultados_experimentos/goloso/completos.txt","w"); // Resultados de tiempo
	clock_t start;
	clock_t end;
	double t;
	int m;	
	int res;
	list<int> cidm_sol;
	
	for(int n = 5; n < 101; n++)
	{
		t = 0;
		m = n*(n-1)/2;
		Vecinos vec = generar_completo(n);
		Vecinos vec_aux(n);
		
		for(int i = 0; i < 20; i++)
		{
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; i < n; i++)
			{
				(vec_aux[i].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[i].first).push_back(*it); }
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


void exp_goloso_aleatorio()
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/aleatorio.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int a;
	int n;
	int m;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < 1000; k++)
	{
		t = 0;
		n = (rand() % 12) + 4;			// random entre 4 y 15
		a = rand() % ((n*(n-1)/2)+1);	// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		Vecinos vec_aux(n);
		
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
			// Acomodo las variables
			cidm_sol.clear();
			
			for(int j = 0; i < n; i++)
			{
				(vec_aux[i].first).clear();
				for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
				{ (vec_aux[i].first).push_back(*it); }
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

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_goloso_estrellas()
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/estrellas.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/estrellas.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < 1000; k++)
	{
		// FALTA PONER UN VALOR PARA N
		
		Vecinos vec = generar_estrella(n);
		
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


void exp_goloso_circuito_ord()
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/circuito_ord.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/circuito_ord.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < 1000; k++)
	{
		// FALTA PONER UN VALOR PARA N
		
		Vecinos vec = generar_circuito_ord(n);
		
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


void exp_goloso_circuito_rnd()
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/circuito_rnd.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/circuito_rnd.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < 1000; k++)
	{
		// FALTA PONER UN VALOR PARA N
		
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


void exp_goloso_galaxias()
{
	FILE * pExp = fopen("../Resultados_experimentos/goloso/galaxias.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/goloso/galaxias.in","w");	// Instancias de entrada

	int n;
	int res;
	list<int> cidm_sol;
	
	for(int k = 0; k < 1000; k++)
	{
		// FALTA PONER UN VALOR PARA N
		
		Vecinos vec = generar_galaxia(n);
		
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

#endif // EXP_GOLOSO_H_INCLUDED
