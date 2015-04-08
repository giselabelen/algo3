#include "testing.h"

list<ciudad> generar_casos(int n)
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
		zombie_test(n,0);
		zombie_test(n,n*100000);
	}
}
