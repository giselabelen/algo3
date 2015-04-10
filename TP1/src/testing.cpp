#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "testing.h"

using namespace std;

/**********************************************************************/
/*******      TESTS ZOMBIELAND     ************************************/
/**********************************************************************/

list<ciudad> generar_pais(int n)
{
	list<ciudad> instancia;
	ciudad city;
	
	for(int i = 1; i <= n; i++)
	{
		city = (ciudad){
			.nombre = i,
			.cant_zombies = (100 + rand() % 1000),
			.cant_soldados = (rand() % 10),
			.soldier_req = 0,
			.costfsoldier = (1 + rand() % 10),
			.costfsafety = 0,
			.salvar = 0,
		};
		instancia.push_back(city);

	}
	return instancia;
}

void testear_1()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing1.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;
	
	for(int n = 10; n <= 1000; n=n+10)
	{
		list<ciudad> cities = generar_pais(n);
		
		t = 0;
		for(int j = 0; j < 50; j++)
		{
			start = clock();
			zombieland(cities,0);
			end = clock();
			t = t + difftime(end,start);
		}
		fprintf(pTest,"%i %i %f \n",n,0,t/50);

		t = 0;
		for(int j = 0; j < 50; j++)
		{
		 	start = clock();
		 	zombieland(cities,n*1000);
		 	end = clock();
		 	t = t + difftime(end,start);
		 }
		 fprintf(pTest,"%i %i %f \n",n,n*1000,t/50);
	}
	fclose(pTest);
}

/**********************************************************************/
/*******      TESTS ALTA FRECUENCIA      ******************************/
/**********************************************************************/

list<frecuencia> generar_freq_piramide(int n)
{
	frecuencia freq;
	list<frecuencia> instancia;
	
	for(int i = 0; i < n; i++)
	{
		freq = (frecuencia){
			.nombre = i + 1,
			.costfminute = 2*(n - i),
			.inicio = i,
			.fin = 2*n - i,
		};
		instancia.push_back(freq);
	}
	return instancia;
}

list<frecuencia> generar_freq_tren(int n)
{
	frecuencia freq;
	list<frecuencia> instancia;
	
	for(int i = 0; i < n; i++)
	{
		freq = (frecuencia){
			.nombre = i + 1,
			.costfminute = n,
			.inicio = i,
			.fin = i + 1,
		};
		instancia.push_back(freq);
	}
	return instancia;
}

list<frecuencia> generar_freq_cadena(int n)
{
	frecuencia freq;
	list<frecuencia> instancia;
	
	for(int i = 0; i < n; i++)
	{
		freq = (frecuencia){
			.nombre = i + 1,
			.costfminute = 2*(n - i),
			.inicio = i,
			.fin = i + 2,
		};
		instancia.push_back(freq);
	}
	return instancia;
}

void testear_2()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;
	
	for(int n = 10; n <= 2000; n=n+10)
	{
		list<frecuencia> res;
		
		list<frecuencia> freq_lp = generar_freq_piramide(n);
		list<frecuencia> freq_lt = generar_freq_tren(n);
		list<frecuencia> freq_lc = generar_freq_cadena(n);
		
		for(int i = 0; i < 30; i++)
		{	
			start = clock();
			altafrecuencia(freq_lp,res,n);
			end = clock();
			t = t + difftime(end,start);
		}
		fprintf(pTest,"%i %c %f \n",n,'p',t/30);
		
		t = 0;
		for(int i = 0; i < 30; i++)
		{
			start = clock();
			altafrecuencia(freq_lt,res,n);
			end = clock();
			t = t + difftime(end,start);
		}
		fprintf(pTest,"%i %c %f \n",n,'t',t/30);
		
		t = 0;
		for(int i = 0; i < 30; i++)
		{
			start = clock();
			altafrecuencia(freq_lc,res,n);
			end = clock();
			t = difftime(end,start);
		}
		fprintf(pTest,"%i %c %f \n",n,'c',t/30);
	}
	fclose(pTest);
}

/**********************************************************************/
/*****************      MAIN       ************************************/
/**********************************************************************/
int main()
{
	srand(time(0));
	testear_1();
	//testear_2();
}
