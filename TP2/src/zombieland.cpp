#include <cstdio>
#include "zombieland.h"

int main()
{
	int i;
	int j;
	int n;
	int m;
	int h;
	int v;
	int soldados;
	int zombies;
	pos inicio;
	pos bunker;
	pair <pos,int> primero;
	list<pair <pos,int> > cola;
	list<pos> salida;
	
	scanf("%i",&n);	// Cant calles horizontales
	scanf("%i",&m);	// Cant calles verticales
	scanf("%i",&soldados);	// Cant soldados iniciales
	
	// Creo el mapa
	Mapa ciudad(n, Vec(m));
	
	// señalo las calles inválidas (bordes)
	for(i = 0; i < n; i++)
	{
		ciudad[i][0].izquierda = -1;
		ciudad[i][m-1].derecha = -1;
	}
	for(j = 0; j < m; j++)
	{
		ciudad[0][j].arriba = -1;
		ciudad[n-1][j].abajo = -1;
	}
	
	// valor por defecto para .parcial (para cada nodo)
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			ciudad[i][j].parcial = 0;
		}
	}
	
	// Posición de inicio
	scanf("%i",&h);
	scanf("%i",&v);
	inicio.horizontal = h - 1;	
	inicio.vertical = v - 1;
	
	// valor de .parcial de la posición inicial
	ciudad[h-1][v-1].parcial = soldados;
	
	// Posición de bunker
	scanf("%i",&h);
	scanf("%i",&v);
	bunker.horizontal = h - 1;	
	bunker.vertical = v - 1;
	
	// Cant de zombies x calle
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m-1; j++)	// calles horizontales
		{
			scanf("%i",&zombies);
			
			// si la cant de zombies es muy grande, invalido la calle
			if(zombies < 2*soldados){
				ciudad[i][j].derecha = zombies;
				ciudad[i][j+1].izquierda = zombies;
			}else{
				ciudad[i][j].derecha = -1;
				ciudad[i][j+1].izquierda = -1;
			}
		}
		
		if(i != (n - 1))		// calles verticales
		{
			for(j = 0; j < m; j++)
			{
				scanf("%i",&zombies);
				
				// si la cant de zombies es muy grande, invalido la calle
				if(zombies < 2*soldados){
					ciudad[i][j].abajo = zombies;
					ciudad[i+1][j].arriba = zombies;
				}else{
					ciudad[i][j].abajo = -1;
					ciudad[i+1][j].arriba = -1;
				}
			}
		}
	}
	
	// Busco el recorrido
	primero = make_pair(inicio,soldados);
	cola.push_back(primero);
	zombieland(ciudad,cola,soldados,bunker);
	
	// Armo la lista con la solución
	armo_resultado(ciudad,salida,inicio,bunker);
	
	// Salida
	printf("%i \n",soldados);	// Cant soldados vivos
	
	// Recorrido
	for (list<pos>::iterator it = salida.begin(); it != salida.end(); it++){
		printf("%i %i \n",it->horizontal+1,it->vertical+1);
	}
	
	cola.clear();
	salida.clear();
}
