#ifndef EXP_FINAL_H_INCLUDED
#define EXP_FINAL_INCLUDED

#include "auxiliares.h"
#include "generadores.h"
#include "CIDM_exacto.h"
#include "CIDM_goloso.h"
#include "CIDM_busqlocal.h"
#include "CIDM_grasp.h"


/********************** DECLARACIÓN DE FUNCIONES **********************/

void exp_final_aleatorio(int cant_min,int cant_max);
void exp_final_aleatorio_comp(int cant_min,int cant_max);
void exp_final_estrellas(int min,int max);
void exp_final_circuito_rnd(int min, int max);
void exp_final_galaxias(int min,int max);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

void exp_final_aleatorio(int cant_min,int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/final/aleatorio.txt","a");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/final/aleatorio.in","w");	// Instancias de entrada
	
	int a;
	
	for(int n = cant_min; n <= cant_max; n++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << n << " nodos, iteracion " << i << endl;
			
			a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
			Vecinos vec = generar_aleatorio(n,a);
			
			fprintf(pExp,"%i, %i, ",n,a);
			
			//~ imp_instancia(pIn, n, a, vec);
			
			correr_goloso(vec,n,a,pExp);
			correr_busqlocal_bis(vec,n,pExp);
			correr_grasp_bis(vec,n,pExp);
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	//~ fclose(pIn);
}

void exp_final_aleatorio_comp(int cant_min,int cant_max)
{
	FILE * pExp = fopen("../Resultados_experimentos/final/aleatorio_comp.txt","w");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/grasp/aleatorio_comp.in","w");	// Instancias de entrada
	
	int a;
	
	for(int n = cant_min; n <= cant_max; n++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << n << " nodos, iteracion " << i << endl;
			
			a = rand() % ((n*(n-1)/2)+1);			// Cantidad aleatoria de aristas
			Vecinos vec = generar_aleatorio(n,a);
			
			fprintf(pExp,"%i, %i, ",n,a);
			
			//~ imp_instancia(pIn, n, a, vec);
			
			vector<int> estado(n,0);
		
			correr_exacto_bis(vec, estado, n, pExp);
			correr_goloso(vec,n,a,pExp);
			correr_busqlocal_bis(vec,n,pExp);
			correr_grasp_bis(vec,n,pExp);
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	//~ fclose(pIn);
}


void exp_final_estrellas(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/final/estrellas.txt","w");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/final/estrellas.in","w");	// Instancias de entrada

	int n;
	
	for(int grado_int = min; grado_int <= max; grado_int++)
	{	
		for(int i = 0; i < 10; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_estrella(grado_int,n);
			
			//~ imp_instancia(pIn, n, -1, vec);
			
			fprintf(pExp,"%i, ",n);
		
			correr_goloso(vec,n,0,pExp);
			correr_busqlocal_bis(vec,n,pExp);
			correr_grasp_bis(vec,n,pExp);
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	//~ fclose(pIn);
}


void exp_final_circuito_rnd(int min, int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/final/circuito_rnd.txt","a");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/final/circuito_rnd.in","w");	// Instancias de entrada
	
	for(int n = min; n < max+1; n++)
	{	
		cout << n << " nodos" << endl;
		
		Vecinos vec = generar_circuito_rnd(n);
		
		//~ imp_instancia(pIn, n, n, vec);
		
		fprintf(pExp,"%i, ",n);
		
		correr_goloso(vec,n,n,pExp);
		correr_busqlocal_bis(vec,n,pExp);
		correr_grasp_bis(vec,n,pExp);
		
		fprintf(pExp,"\n");
	}

	// Cierro los archivos
	fclose(pExp);
	//~ fclose(pIn);
}


void exp_final_galaxias(int min,int max)
{
	FILE * pExp = fopen("../Resultados_experimentos/final/galaxias.txt","w");	// Resultados
	//~ FILE * pIn = fopen("../Resultados_experimentos/final/galaxias.in","w");	// Instancias de entrada

	int n;
	
	for(int grado_int = min; grado_int <= max; grado_int++)
	{
		for(int i = 0; i < 10; i++)
		{
			cout << "grado " << grado_int << " iteracion " << i << endl;
			
			Vecinos vec = generar_galaxia(grado_int, n);
			
			//~ imp_instancia(pIn, n, -1, vec);
			
			fprintf(pExp,"%i, ",n);
			
			correr_goloso(vec,n,0,pExp);
			correr_busqlocal_bis(vec,n,pExp);
			correr_grasp_bis(vec,n,pExp);
			
			fprintf(pExp,"\n");
		}
	}

	// Cierro los archivos
	fclose(pExp);
	//~ fclose(pIn);
}


#endif // EXP_FINAL_H_INCLUDED
