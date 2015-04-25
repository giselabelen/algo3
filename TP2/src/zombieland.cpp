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
	
	Mapa ciudad(n, Vec(m));
	
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
	
	scanf("%i",&h);
	scanf("%i",&v);
	
	// Posición de inicio
	inicio.horizontal = h - 1;	
	inicio.vertical = v - 1;
	
	scanf("%i",&h);
	scanf("%i",&v);
	
	// Posición de bunker
	bunker.horizontal = h - 1;	
	bunker.vertical = v - 1;
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < m; j++)	// Cant zombies en calles horizontales
		{
			scanf("%i",&zombies);
			ciudad[i][j].derecha = zombies;
			ciudad[i][j+1].izquierda = zombies;
		}
		
		if(i != (n - 1))		// Cant zombies en calles verticales
		{
			for(j = 0; j < m; j++)
			{
				scanf("%i",&zombies);
				ciudad[i][j].abajo = zombies;
				ciudad[i+1][j].arriba = zombies;
			}
		}
	}
	
	// HAGO MAGIA
	primero = make_pair(inicio,soldados);
	cola.push_back(primero);
	zombieland(ciudad,cola,soldados,bunker);
	
	// Armo la lista con la solución
	armo_resultado(ciudad,salida);
	
	// Salida
	printf("%i \n",soldados);	// Cant soldados vivos
	
	// Recorrido
	for (list<pos>::iterator it = salida.begin(); it != salida.end(); it++)
    {
		printf("%i %i \n",it->horizontal,it->vertical);
	}
	
	cola.clear();
	salida.clear();
}
