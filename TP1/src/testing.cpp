#include "cstdlib"
#include "ctime"
#include "testing.h"

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

int zombie_test(int n, int p)
{
    int salvacion_total;
    
    list<ciudad> cities = generar_pais(n);
	
	// Calculo y completo soldier_req y costfsafety para cada ciudad
    calcular_costo_de_salvacion(cities);
    
    // Ordeno por costo de salvación
    cities.sort(compare_cost);
    
    // Busco la solución "greedy"
    salvacion_total = zombie_goloso(cities,p);
    
    // Ordeno por nombre (orden en el que vinieron en la entrada)
    cities.sort(compare_name);

	cities.clear();
}

void testear_1()
{
	for(int n = 10; n <= 10000; n=n+10)
	{
		zombie_test(n,0);
		zombie_test(n,n*100000);
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

int freq_test(int n)
{
	int i = 0;
	int costo_total;
    frecuencia freq;
    list<frecuencia>::iterator it;
    list<frecuencia> res;    
    frecuencia total_freq[n];	// Arreglo donde voy a ir metiendo las frecuencias
       
    list<frecuencia> freq_l1 = generar_freq_piramide(n);
    //~ list<frecuencia> freq_l1 = generar_freq_tren(n);
    //~ list<frecuencia> freq_l1 = generar_freq_cadena(n);
       
    // Ordeno por tiempo de inicio
    freq_l.sort(compare_time);
    
    // Paso la lista a un arreglo
    for (it = freq_l.begin(); it != freq_l.end(); it++)
    {
		total_freq[i] = *it;
		i++;
	}
    freq_l.clear();
    
    // Hago el divide and conquer
    res = frequency_dc(total_freq,0,n-1);
    
    // Calculo el costo total
    costo_total = costo_transmision(res);
    
	res.clear();
}

void testear_2()
{
	for(int n = 10; n <= 10000; n=n+10)
	{
		freq_test(n);
	}
}

/**********************************************************************/
/*******      TESTS CABALLOS       ************************************/
/**********************************************************************/


