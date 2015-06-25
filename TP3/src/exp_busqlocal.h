#ifndef EXP_BUSQLOCAL_H_INCLUDED
#define EXP_BUSQLOCAL_INCLUDED

#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_busqlocal_aleatorio(int cant_min,int cant_max,int cant_it);
void exp_busqlocal_aleatorio_comp(int cant_min,int cant_max,int cant_it);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_busqlocal_aleatorio(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t;
	int a;
	int n;
	int res1;
	list<int> cidm_sol1;
	int res2;
	list<int> cidm_sol2;
	
	for(int k = 0; k < cant_it; k++)
	{
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
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
		
		for(int m = 1; m < 3; m++)
		{
			t = 0;

			for(int i = 0; i < 20; i++)
			{
				// Acomodo las variables
				cidm_sol1.clear();
				cidm_sol2.clear();
				
				for(int j = 0; j < n; j++)
				{
					(vec_aux[i].first).clear();
					for(list<int>::iterator it = (vec[j].first).begin(); it != (vec[j].first).end(); it++)
					{ (vec_aux[i].first).push_back(*it); }
				}
				
				// Mido el tiempo
				start = clock();
				res1 = goloso(cidm_sol1,vec_aux,n,0,0);
				busqueda(cidm_sol1,vec,n,res,m)
				end = clock();
				t = t + difftime(end,start);

				res2 = otro_inicio(cidm_sol2,vec,n);
			}
			
			// Imprimo los resultados
			fprintf(pExp,"%i, %i, %f, %i \n",n,a,t/20,res);
		}
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


void exp_busqlocal_aleatorio_comp(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.in","w");	// Instancias de entrada
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
		t = 0;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,m);
	
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
		
		backtracking(cidm,cidm_sol,estado,vec,0,n,cota,res,0,1);

		fprintf(pExp,"%i, %i, %i, ",n,a,res);

		cidm_sol.clear();
		
		res = goloso(cidm_sol,vec_aux,n,0,0);
		
		// Imprimo los resultados
		fprintf(pExp,"%i \n",res);
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}


#endif // EXP_BUSQLOCAL_H_INCLUDED
