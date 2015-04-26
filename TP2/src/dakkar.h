#ifndef DAKKAR_H_INCLUDED
#define DAKKAR_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;

typedef pair< int,int > Optimo;

typedef vector<Optimo> Vec;
typedef vector<Vec> Etapa;


Optimo eleccion(int bici, int moto, int buggy);
Etapa* dakkar(int n, int km, int kb, int* bici, int* moto, int* buggy);
int armo_salida(Etapa* etapas, int km, int kb, int n, list<int>& salida);


Optimo eleccion(int bici, int moto, int buggy)
{
	Optimo res;
	
	if(moto == -1)	// bici contra buggy
	{
		if(bici <= buggy){
			res = make_pair(bici,1);
		}else{
			res = make_pair(buggy,3);
		}
		
	}else if(buggy == -1)	// bici contra moto
	{
		if(bici <= moto){
			res = make_pair(bici,1);
		}else{
			res = make_pair(moto,2);
		}
	}else{	// todos contra todos
		if((bici <= moto) && (bici <= buggy)){
			res = make_pair(bici,1);
		}else if(moto <= buggy){
			res = make_pair(moto,2);
		}else{
			res = make_pair(buggy,3);
		}
	}
	return res;
}

Etapa* dakkar(int n, int km, int kb, int* bici, int* moto, int* buggy)
{
	int h;
	int i;
	int j;
	Optimo aux;
	Etapa etapas[n];
	
	// Lleno los datos de la primera etapa
	etapas[0][0][0] = make_pair(bici[0],1);
	aux = eleccion(bici[0],moto[0],-1);
	for(j = 1; j <= km; j++)
	{
		etapas[0][0][j] = aux;
	}
	aux = eleccion(bici[0],-1,buggy[0]);
	for(i = 1; i <= kb; i++)
	{
		etapas[0][i][0] = aux;
	}
	aux = eleccion(bici[0],moto[0],buggy[0]);
	for(i = 1; i <= kb; i++)
	{
		for(j = 1; j < km; j++)
		{
			etapas[0][i][j] = aux;
		}
	}
	
	// armo las demás etapas
	for(h = 1; h < n; h++)
	{
		etapas[h][0][0] = make_pair(etapas[h-1][0][0].first + bici[h],1);
		
		for(j = 1; j <= km; j++)
		{
			aux = eleccion(etapas[h-1][0][j].first + bici[h],etapas[h-1][0][j-1].first + moto[h],-1);
			etapas[h][0][j] = aux;
		}
		
		for(i = 1; i <= kb; i++)
		{
			aux = eleccion(etapas[h-1][i][0].first + bici[h],-1,etapas[h-1][i-1][0].first + buggy[h]);
			etapas[h][i][0];
		}
		
		for(i = 1; i <= kb; i++)
		{
			for(j = 1; j <= km; j++)
			{
				aux = eleccion(etapas[h-1][i][j].first + bici[h],
								etapas[h-1][i][j-1].first + moto[h],
								etapas[h-1][i-1][j].first + buggy[h]);
				etapas[h][i][j] = aux;
			}
		}
	}
	return etapas;
}

int armo_salida(Etapa* etapas, int km, int kb, int n, list<int>& salida)
{
	int aux;
	int i = kb;
	int j = km;
	int res = etapas[n-1][kb][km].first;
	
	for(int h = n-1; h >= 0; h--)
	{
		salida.push_front(etapas[h][i][j].second);
		
		if(etapas[h][i][j].second == 2){
			j--;
		}else if(etapas[h][i][j].second == 3){
			i--;
		}
	}
	
	return res;
}


#endif // DAKKAR_H_INCLUDED
