#ifndef CIDM_BUSQLOCAL_H_INCLUDED
#define CIDM_BUSQLOCAL_H_INCLUDED

#include <list>
#include <vector>

using namespace std;

/**************************** ESTRUCTURAS ****************************/

typedef vector< pair< list<int>, int> > Vecinos;


/********************** DECLARACIÓN DE FUNCIONES **********************/

int otro_inicio(list<int>& cidm_sol, Vecinos vecinos, int n);
pair<int,int> vecindad1(list<int> salientes,Vecinos vecinos, vector<int>& cercanos, int cont_ceros,int n);
int vecindad2(list<int> intercambios, Vecinos vecinos, vector<int>& cercanos);
bool mejorador1(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res, int n);
bool mejorador2(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res, int n);
void busqueda(list<int>& cidm_sol, Vecinos vecinos, int n, int& res, int mej);
list<int> fusion_vecinos(list<int> nodos, Vecinos vecinos, int n);
bool son_vecinos(int n1, int n2, Vecinos vecinos);


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


list<int> fusion_vecinos(list<int> nodos, Vecinos vecinos, int n)
{
	list<int> res;
	list<int>::iterator it1;
	list<int>::iterator it2;
	vector<bool> cand_bool(n,false);
	
	for(it1 = nodos.begin(); it1 != nodos.end(); it1++)
	{
		for(it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
		{
			if(!cand_bool[*it2])
			{
				cand_bool[*it2] = true;
				res.push_back(*it2);
			}
		}
	}
	
	return res;
}


bool son_vecinos(int n1, int n2, Vecinos vecinos)
{
	list<int>::iterator it;
	
	for(it = (vecinos[n1].first).begin(); it != (vecinos[n1].first).end(); it++)
	{
		if(*it == n2){ return true; }
	}
	
	return false;
}


pair<int,int> vecindad1(list<int> salientes, Vecinos vecinos, vector<int>& cercanos, int cont_ceros, int n)
{
	int cont_aux;
	pair<int,int> res;
	list<int> nodos;
	list<int> aux_vecinos;
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int>::iterator it3;
	
	// Armo una lista de candidatos
	list<int> candidatos = fusion_vecinos(salientes,vecinos,n);
	
	// Recorro esta lista de nodos
	for(it1 = candidatos.begin(); it1 != candidatos.end(); it1++)
	{
		it2 = it1;
		it2++;
		
		while(it2 != candidatos.end())
		{
			cont_aux = 0;
			
			// Si ambos nodos me sirven
			if(cercanos[*it1] == 0 && cercanos[*it2] == 0 && !son_vecinos(*it1,*it2,vecinos))
			{
				aux_vecinos.clear();
				nodos.clear();
				
				nodos.push_back(*it1);
				nodos.push_back(*it2);
				
				aux_vecinos = fusion_vecinos(nodos,vecinos,n);
				
				// Cuento cuántos huecos cubren
				for(it3 = aux_vecinos.begin(); it3 != aux_vecinos.end(); it3++)
				{
					if(cercanos[*it3] == 0){ cont_aux++; }
				}
				
				// Si se cubren todos los huecos, actualizo 'cercanos' y devuelvo
				if(cont_ceros-2 == cont_aux)
				{
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
					
					res = make_pair(*it1,*it2);
					return res;
				}
				
			}
			
			it2++;
		}
	}
	
	res = make_pair(-1,-1);
	return res;
}


int vecindad2(list<int> intercambios, Vecinos vecinos, vector<int>& cercanos)
{
	list<int>::iterator it1;
	list<int>::iterator it2;
	
	for(it1 = intercambios.begin(); it1 != intercambios.end(); it1++)
	{
		for(it2 = (vecinos[*it1].first).begin(); it2 != (vecinos[*it1].first).end(); it2++)
		{
			if(cercanos[*it2] > 1)
			{
				cercanos[*it2]--;
			}
			else if(cercanos[*it2] == 1)
			{
				return 1;
			}
		}
	}
	
	return 0;
}


bool mejorador1(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res, int n)
{
	int cont_ceros;				// Cantidad de nodos que quedan 'libres'
	pair<int,int> cambio;		// Nodos que vamos a insertar
	list<int> salientes;		// Nodos que vamos a sacar
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int>::iterator it3;
	list<int>::iterator it4;
	
	for(it1 = cidm_sol.begin(); it1 != cidm_sol.end(); it1++)
	{
		it2 = it1;
		it2++;
		while(it2 != cidm_sol.end())
		{
			it4 = it2;
			it4++;
			while(it4 != cidm_sol.end())
			{
				salientes.clear();
				
				// Tomo 3 nodos de la solución
				cercanos[*it1] = 0;
				cercanos[*it2] = 0;
				cercanos[*it4] = 0;
				cont_ceros = 3;
				
				// Actualizo 'cercanos' y 'cont_ceros' para los vecinos de los 3 nodos elegidos
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
				
				for(it3 = (vecinos[*it4].first).begin(); it3 != (vecinos[*it4].first).end(); it3++)
				{
					cercanos[*it3]--;
					if(cercanos[*it3] == 0){ cont_ceros++; }
				}
				
				salientes.push_back(*it1);
				salientes.push_back(*it2);
				salientes.push_back(*it4);
				
				// Veo si puedo cambiar estos 3 con otros 2 nodos fuera del conjunto
				cambio = vecindad1(salientes,vecinos,cercanos,cont_ceros,n);
				
				// Si tuve un cambio, actualizo 'cidm_sol' y 'res'
				if(cambio.first != -1)
				{
					it1 = cidm_sol.erase(it1);
					it2 = cidm_sol.erase(it2);
					it4 = cidm_sol.erase(it4);
					cidm_sol.push_back(cambio.first);
					cidm_sol.push_back(cambio.second);
					res--;
					return true;
				}
				
				// Si no tuve un cambio, vuelvo al 'cercanos' original
				cercanos[*it1] = -1;
				cercanos[*it2] = -1;
				cercanos[*it4] = -1;
				
				for(it3 = (vecinos[*it1].first).begin(); it3 != (vecinos[*it1].first).end(); it3++){
					cercanos[*it3]++;
				}
				
				for(it3 = (vecinos[*it2].first).begin(); it3 != (vecinos[*it2].first).end(); it3++){
					cercanos[*it3]++;
				}
				
				for(it3 = (vecinos[*it4].first).begin(); it3 != (vecinos[*it4].first).end(); it3++){
					cercanos[*it3]++;
				}
				
				it4++;
			}
			
			it2++;
		}
	}
	
	return false;
}


bool mejorador2(list<int>& cidm_sol, Vecinos vecinos, vector<int>& cercanos, int& res, int n)
{
	int cont_ceros;				// Cantidad de nodos que quedan 'libres'
	int cambio;	
	vector<int> cercanos_aux;
	list<int> intercambios;		// Nodos que vamos a sacar
	list<int>::iterator it1;
	list<int>::iterator it2;
	list<int>::iterator it3;
	
	for(int i = 0; i < n; i++)
	{
		if(cercanos[i] > 1)
		{
			intercambios.clear();
			cercanos_aux = cercanos;
			cercanos_aux[i] = -1;
			
			// Actualizo 'cercanos' para los vecinos del nodo elegido
			for(it1 = (vecinos[i].first).begin(); it1 != (vecinos[i].first).end(); it1++)
			{
				if(cercanos_aux[*it1] == -1)
				{ 
					cercanos_aux[*it1] = 1; 
					intercambios.push_back(*it1);
				}else{
					cercanos_aux[*it1]++;
				}
			}
			
			cambio = vecindad2(intercambios, vecinos, cercanos_aux);
			
			// Si tuve un cambio, actualizo 'cercanos', 'cidm_sol' y 'res'
			if(cambio == 0)
			{
				cercanos = cercanos_aux;
				
				for(it1 = intercambios.begin(); it1 != intercambios.end(); it1++)
				{
					it2 = cidm_sol.begin();
					
					while(*it2 != *it1){ it2++; }
					
					it2 = cidm_sol.erase(it2);
					res--;
				}
				
				cidm_sol.push_back(i);
				res++;
				return true;
			}
			
			// Si no tuve un cambio, me voy
		}
	}
	
	return false;
}


void busqueda(list<int>& cidm_sol, Vecinos vecinos, int n, int& res, int mej)
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
		printf("%i ",res);
		for (list<int>::iterator it = cidm_sol.begin(); it != cidm_sol.end(); it++){
			printf("%i ",*it + 1);
		}
		printf("\n");
		
		if(mej == 1){
			if( res>2 ){
				hay_cambios = mejorador1(cidm_sol,vecinos,cercanos,res,n);
			}
			else{hay_cambios = false;}
		}else{
			hay_cambios = mejorador2(cidm_sol,vecinos,cercanos,res,n);
		}
	}
	
	return;
}

#endif // CIDM_BUSQLOCAL_H_INCLUDED
