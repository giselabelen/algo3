#ifndef CIDM_GOLOSO_H_INCLUDED
#define CIDM_GOLOSO_H_INCLUDED

#include <list>
#include <vector>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< pair< list<int>, int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

int goloso(list<int>& cidm_sol,	Vecinos vecinos, int n);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int goloso(list<int>& cidm_sol,	Vecinos vecinos, int n)
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
