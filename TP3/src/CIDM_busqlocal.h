#ifndef CIDM_BUSQLOCAL_H_INCLUDED
#define CIDM_BUSQLOCAL_H_INCLUDED

#include <list>
#include <vector>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< pair< list<int>, int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

int otro_inicio(list<int>& cidm_sol, Vecinos vecinos, int n);
int vecindades(list<int> vec, Vecinos vecinos, vector<int>& cercanos, int cont_ceros);
bool mejorador(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res);
void busqueda1(list<int>& cidm_sol, Vecinos vecinos, int n, int& res);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int otro_inicio(list<int>& cidm_sol, Vecinos vecinos, int n)
{
	int res;	
	vector<bool> estado(n,false);
	list<int>::iterator it;
	
	for(int i = 0; i < n; i++)
	{
		if(!estado[i])
		{
			cidm_sol.push_back(i);
			estado[i] = true;
			res++;
			
			for (it = (vecinos[i].first).begin(); it != (vecinos[i].first).end(); it++)
			{
				estado[*it] = true;
			}
		}
	}
	
	return res;
}


int vecindades(list<int> vec, Vecinos vecinos, vector<int>& cercanos, int cont_ceros)
{
	int cont_aux = 0;
	list<int>::iterator it1;
	list<int>::iterator it2;
	
	// Recorro esta lista de nodos
	for(it1 = vec.begin(); it1 != vec.end(); it1++)
	{
		// Si el nodo me sirve
		if(cercanos[*it1] == 0)
		{
			// Cuento cuántos huecos cubre
			for(it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
			{
				if(cercanos[*it2] == 0){ cont_aux++; }
			}
			
			// Si el nodo cubre todos los huecos, actualizo 'cercanos' y lo devuelvo
			if(cont_ceros == cont_aux)
			{
				for(it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
				{
					cercanos[*it2]++;
				}

				return *it1;
			}
		}
	}
	
	return -1;
}


bool mejorador(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res)
{
	int cont_ceros;				// Cantidad de nodos que quedan 'libres'
	int cambio;					// Nodo que vamos a insertar
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int>::iterator it3;
	
	for(it1 = cidm_sol.begin(); it1 != cidm_sol.end(); it1++)
	{
		it2 = it1;
		it2++;
		while(it2 != cidm_sol.end())
		{
			// Tomo 2 nodos de la solución
			cercanos[*it1] = 0;
			cercanos[*it2] = 0;
			cont_ceros = 2;
			
			// Actualizo 'cercanos' y 'cont_ceros' para los vecinos de los 2 nodos elegidos
			for(it3 = (vecinos[*it1].first).begin(); it3 != (vecinos[*it1].first).end(); it3++)
			{
				cercanos[*it3]--;
				if(cercanos[*it3] == 0){ cont_ceros++; }
			}
			
			for(it3 = (vecinos[*it2].first).begin(); it3 != (vecinos[*it2].first).end(); it3++)
			{
				cercanos[*it3]--;
				if(cercanos[*it3] == 0){ cont_ceros++; }
			}
			
			// Veo si puedo cambiar estos 2 con un amigo del primero
			cambio = vecindades(vecinos[*it1].first,vecinos,cercanos,cont_ceros);
			
			if(cambio == -1)
			{
				// Si no se pudo, veo de cambiar con un amigo del segundo
				cambio = vecindades(vecinos[*it2].first,vecinos,cercanos,cont_ceros);
			}
			
			// Si tuve un cambio, actualizo 'cidm_sol' y 'res'
			if(cambio != -1)
			{
				it1 = cidm_sol.erase(it1);
				it2 = cidm_sol.erase(it2);
				cidm_sol.push_back(cambio);
				res--;
				return true;
			}
			
			// Si no tuve un cambio, vuelvo al 'cercanos' original
			cercanos[*it1] = -1;
			cercanos[*it2] = -1;
			
			for(it3 = (vecinos[*it1].first).begin(); it3 != (vecinos[*it1].first).end(); it3++)
			{
				cercanos[*it3]++;
			}
			
			for(it3 = (vecinos[*it2].first).begin(); it3 != (vecinos[*it2].first).end(); it3++)
			{
				cercanos[*it3]++;
			}
			
			it2++;
		}
	}
	
	return false;
}


void busqueda1(list<int>& cidm_sol, Vecinos vecinos, int n, int& res)
{
	bool hay_cambios = true;
	vector<int> cercanos(n,0);	// Conexiones con los de la solución
	list<int>::iterator it1;
	list<int>::iterator it2;
	
	// Inicializo 'cercanos'
	for(it1 = cidm_sol.begin(); it1 != cidm_sol.end(); it1++)
	{
		cercanos[*it1] = -1;
		for(it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
		{
			cercanos[*it2]++;
		}
	}

	// Itero hasta que no mejore
	while(hay_cambios && res != 1)
	{
		hay_cambios = mejorador(cidm_sol,vecinos,cercanos,res);
	}
	
	return;
}



#endif // CIDM_BUSQLOCAL_H_INCLUDED