#include <cstdio>
#include "dakkar.h"

int main()
{
	int n;
	int km;
	int kb;
	int bi;
	int mo;
	int bu;
	int total;
	list<int> salida;
	
	scanf("%i",&n);	// cantidad de etapas
	scanf("%i",&km);	// cantidad de motos
	scanf("%i",&kb);	// cantidad de buggies
	
	// arreglos para los tiempos
	int bici[n];
	int moto[n];
	int buggy[n];
	
	// tiempos de cada uno
	for(int i = 0; i < n; i++)
	{
		scanf("%i",&bi);
		scanf("%i",&mo);
		scanf("%i",&bu);
		
		bici[i] = bi;
		moto[i] = mo;
		buggy[i] = bu;
	}
	
	// Armo las matrices con las decisiones de cada etapa
	Etapa* etapas = dakkar(n,km,kb,bici,moto,buggy);
	
	// Obtengo el tiempo total y los vehículos utilizados
	total = armo_salida(etapas,km,kb,n,salida);
	
	// Salida
	printf("%i ",total);	// tiempo total incurrido
	
	// vehículos utilizados
	for (list<int>::iterator it = salida.begin(); it != salida.end(); it++){
		printf("%i ",*it);
	}
	
	salida.clear();
}
