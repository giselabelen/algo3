#ifndef CIDM_GOLOSO_H_INCLUDED
#define CIDM_GOLOSO_H_INCLUDED

#include <list>
#include <vector>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< pair< list<int>, int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

int goloso(list<int>& cidm_sol,	Vecinos vecinos, int n, int alpha, int beta);
int rcl_alpha(int opc, Vecinos vecinos, int n, float alpha);
int rcl_beta(Vecinos vecinos,int n,int beta);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int rcl_alpha(int opc, Vecinos vecinos, int n, float alpha)
{
	int cont = 0;
	int tope = opc;
	opc = ceil(opc*alpha);
	int base = tope - opc;
	list<int> rcl;
	
	for(int i = 0; i < n; i++)
	{
		if(vecinos[i].second >= base && vecinos[i].second <= tope)
		{
			rcl.push_back(i);
			cont++;
		}
	}
	
	int random = rand() % cont;
	list<int>::iterator it1 = rcl.begin();
	advance(it1,random);
	return *it1;
}


int rcl_beta(Vecinos vecinos,int n,int beta)
{
	int i = 0;
	int j = 0;
	list<int> rcl;
	list<int>::iterator it1;
	list<int>::iterator it2;
	
	while(i != n && j != beta)
	{
		if(vecinos[i].second != -1)
		{
			rcl.push_back(i);
			j++;
		}
		i++;
	}
	
	if(i != n)
	{
		it1 = rcl.begin();
		it2 = it1;
		it2++;
		
		while(it2 != rcl.end())
		{
			if(vecinos[*it1].second > vecinos[*it2].second)
			{
				it1 = it2;
			}
		}
		
		for(int h = i; h < n; h++)
		{
			if(vecinos[h].second > vecinos[*it1].second)
			{
				*it1 = h;
			
				it1 = rcl.begin();
				it2 = it1;
				it2++;
				
				while(it2 != rcl.end())
				{
					if(vecinos[*it1].second > vecinos[*it2].second)
					{
						it1 = it2;
					}
				}
			}
		}
	}

	int random = rand() % j;
	it1 = rcl.begin();
	advance(it1,random);
	return *it1;
}	

int goloso(list<int>& cidm_sol,	Vecinos vecinos, int n, int alpha, int beta)
{
	int res = 0;
	int elegido;
	int opc;
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int>::iterator it3;

	while(true)
	{
		opc = -1;
		
		for(int i = 0; i < n; i++)
		{
			if(vecinos[i].second > opc)
			{
				elegido = i;
				opc = vecinos[i].second;
			}
		}
		
		if(opc == -1){ return res; }

		// RCL CON 'ALPHA'
		if(alpha != 0){
			elegido = rcl_alpha(opc,vecinos,n,alpha);
		}	
		
		// RCL CON 'BETA'
		if(beta != 0){	
			elegido = rcl_beta(vecinos,n,beta);
		}
		
		cidm_sol.push_back(elegido);
		res++;
		
		vecinos[elegido].second = -1;
		
		for (it1 = (vecinos[elegido].first).begin(); it1 != (vecinos[elegido].first).end(); it1++)
		{
			vecinos[*it1].second = -1;
			for (it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
			{
				if(*it2 != elegido)
				{
					vecinos[*it2].second--;
					it3 = (vecinos[*it2].first).begin();
					while(*it3 != *it1){ it3++; }
					(vecinos[*it2].first).erase(it3);
				}
			}
		}
	}
}


#endif // CIDM_GOLOSO_H_INCLUDED
