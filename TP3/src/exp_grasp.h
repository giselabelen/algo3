#ifndef EXP_BUSQLOCAL_H_INCLUDED
#define EXP_BUSQLOCAL_INCLUDED

#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"
#include "CIDM_grasp.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_grasp_aleatorio(int cant_min,int cant_max,int cant_it);
void exp_grasp_aleatorio_comp(int cant_min,int cant_max,int cant_it);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_grasp_aleatorio(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio.in","w");	// Instancias de entrada
	clock_t start;
	clock_t end;
	double t1;
	double t2;
	int a;
	int n;
	int res1;
	int res2;
	list<int> cidm_sol1;
	list<int> cidm_sol2;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		fprintf(pExp,"%i, %i, ",n,a);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,a);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		for(int c = 1; c < 3; c++)
		{
			t1 = 0;
			t2 = 0;

			for(int i = 0; i < 20; i++)
			{
				// Acomodo las variables
				cidm_sol1.clear();
				cidm_sol2.clear();
				
				// Mido el tiempo
				start = clock();
				res1 = grasp(cidm_sol1,vec,n,0.1,0,20,c);
				end = clock();
				t1 = t1 + difftime(end,start);
				
				start = clock();
				res2 = grasp(cidm_sol2,vec,n,0,10,20,c);
				end = clock();
				t2 = t2 + difftime(end,start);
			}
			
			// Imprimo los resultados
			fprintf(pExp,"%f, %i, %f, %i, ",t1/20,res1,t2/20,res2);
		}
		fprintf(pExp,"\n");
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}

void exp_grasp_aleatorio_comp(int cant_min,int cant_max,int cant_it)
{
	FILE * pExp = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.txt","w");	// Resultados
	FILE * pIn = fopen("../Resultados_experimentos/busqlocal/aleatorio_comp.in","w");	// Instancias de entrada
	int a;
	int n;
	int res1;
	list<int> cidm_sol1;
	int res2;
	list<int> cidm_sol2;
	int cota;
	
	for(int k = 0; k < cant_it; k++)
	{
		cout << "iteracion " << k << endl;
		n = (rand() % (cant_max-cant_min+1)) + cant_min;
		a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
		Vecinos vec = generar_aleatorio(n,a);
		
		fprintf(pExp,"%i, %i, ",n,a);
		
		// Imprimo la instancia actual
		fprintf(pIn,"%i %i \n",n,a);
	
		for(int i = 0; i < n; i++)
		{
			for (list<int>::iterator it = (vec[i].first).begin(); it != (vec[i].first).end(); it++){
				fprintf(pIn,"%i %i \n",i+1,*it + 1);
			}
		}
		
		fprintf(pIn,"\n");
		
		cota = n;
		res1 = 0;
		vector<int> estado(n,0);
		
		backtracking(cidm_sol2,cidm_sol1,estado,vec,0,n,cota,res1,0,1);

		fprintf(pExp,"%i, ",cota);
		
		for(int c = 1; c < 3; c++)
		{
			// Acomodo las variables
			cidm_sol1.clear();
			cidm_sol2.clear();
			
			res1 = grasp(cidm_sol1,vec,n,0.1,0,20,c);
			res2 = grasp(cidm_sol2,vec,n,0,10,20,c);
						
			// Imprimo los resultados
			fprintf(pExp,"%i, %i, ",res1,res2);
		}
		fprintf(pExp,"\n");
	}

	// Cierro los archivos
	fclose(pExp);
	fclose(pIn);
}

#endif // EXP_BUSQLOCAL_H_INCLUDED
