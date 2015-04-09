#include "cstdlib"
#include "ctime"
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
			.cant_zombies = (rand() % 10000),
			.cant_soldados = (rand() % 1000),
			.soldier_req = 0,
			.costfsoldier = (10 + rand() % 90),
			.costfsafety = 0,
			.salvar = 0,
		};
		instancia.push_back(city);
	}
	return instancia;
}

void testear_1()
{
	for(int n = 10; n <= 10000; n=n+10)
	{
		list<ciudad> cities = generar_pais(n);
		
		zombieland(cities,0);
		zombieland(cities,n*1000000);
	}
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
}

void testear_2()
{
	for(int n = 10; n <= 10000; n=n+10)
	{
		list<frecuencia> res;
		
		list<frecuencia> freq_lp = generar_freq_piramide(n);
		list<frecuencia> freq_lt = generar_freq_tren(n);
		list<frecuencia> freq_lc = generar_freq_cadena(n);
		
		altafrecuencia(freq_lp,res,n);		
		altafrecuencia(freq_lt,res,n);		
		altafrecuencia(freq_lc,res,n);		
	}
}

/**********************************************************************/
/*******      TESTS CABALLOS       ************************************/
/**********************************************************************/


/**********************************************************************/
/*****************      MAIN       ************************************/
/**********************************************************************/
int main()
{
	srand(time(0));
	testear_1();
	testear_2();
}
