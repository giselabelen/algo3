#ifndef PETROLEO_H_INCLUDED
#define PETROLEO_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef pair<int,int> Arista;	/* par de nodos unidos por una arista */
typedef list< pair<Arista,int> > Incidencia;	/* lista con pares de arista-peso */


/********************** DECLARACIÓN DE FUNCIONES **********************/

int plan(Incidencia& inc, int n, list<Arista>& tuberias, int& costo_total,vector<int>& padres);
bool comparar_peso(const pair<Arista,int>& par1, const pair<Arista,int>& par2);
int petroleo(Incidencia inc,list<int>& refinerias,list<Arista>& tuberias,int n,int& cant_ref,int& cant_tub);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int plan(Incidencia& inc, int n, list<Arista>& tuberias, int& costo_total,vector<int>& padres)
{
/* Función que arma el arbol generador mínimo con las tuberías y
 * determina las componentes conexas a la vez.  Devuelve la cantidad de
 * tuberías colocadas.
 */
	int costo;
	int p1;
	int p2;
	int res = 0;
	Arista edge;
	vector< pair<int,list<int> > > hijos(n);
	
	for(int i = 0; i < n; i++){	// todos los nodos empiezan con 0 hijos
		hijos[i].first = 0;
	}
	
	for(list< pair<Arista,int> >::iterator it1 = inc.begin(); it1 != inc.end(); it1++)
	{
		edge = it1->first;
		costo = it1->second;
		p1 = padres[edge.first];
		p2 = padres[edge.second];
		if((p1 != p2) || (p1 == -1))
		{
			if(p1 != p2)	// padres distintos
			{
				if((p1 != -1) && (p2 != -1))	// si ninguno es -1
				{
					if(hijos[p1].first < hijos[p2].first){
						swap(p1,p2);	// p1 se queda con el que tiene más hijos
					}
					
					for(list<int>::iterator it2 = (hijos[p2].second).begin(); it2 != (hijos[p2].second).end(); it2++)
					{	// paso los hijos de p2 como hijos de p1
						padres[*it2] = p1;
						(hijos[p1].second).push_back(*it2);
						hijos[p1].first++;
					}
					// pongo a p2 como hijo de p1
					padres[p2] = p1;
					(hijos[p1].second).push_back(p2);
					hijos[p1].first++;
					
				}else if(p1 == -1){	// si p1 es -1
					// pongo a p1 como hijo de p2
					padres[edge.first] = p2;
					(hijos[p2].second).push_back(edge.first);
					hijos[p2].first++;
				}else{	// si p2 es -1
					// pongo a p2 como hijo de p1
					padres[edge.second] = p1;
					(hijos[p1].second).push_back(edge.second);
					hijos[p1].first++;
				}
			}else if (p1 == -1){	// si ambos son -1
				// pongo como padre de ambos a p1
				padres[edge.first] = edge.first;
				padres[edge.second] = edge.first;
				(hijos[edge.first].second).push_back(edge.second);
				hijos[edge.first].first++;
			}
			
			// actualizo variables
			costo_total = costo_total + costo;
			tuberias.push_back(edge);
			res++;
		}
	}
	
	return res;
}

bool comparar_peso(const pair<Arista,int>& par1, const pair<Arista,int>& par2)
{
	return (par1.second <= par2.second);
}

int petroleo(Incidencia inc,list<int>& refinerias,list<Arista>& tuberias,int n,int& cant_ref,int& cant_tub, int costo_ref)
{
/* Función que elabora el plan, determina las refinerías a colocar y 
 * calcula el costo total.  Devuelve el costo total.
 */
	int p;
	int res = 0;
	vector<int> padres(n,-1);
	vector<bool> aux(n,false);
	
	// elaboro el plan de tuberías
	cant_tub = plan(inc,n,tuberias,res,padres);
	
	// determino refinerías
	for(int i = 0; i < n; i++)
	{
		if(padres[i] == -1)	// nodo solitario
		{	// coloco refinería
			refinerias.push_back(i);
			cant_ref++;
		}else{
			p = padres[i];
			if(!aux[p])	// nueva componente conexa
			{	// coloco refinería
				aux[p] = true;
				refinerias.push_back(i);
				cant_ref++;
			}
		}
	}
	
	// actualizo costo total
	res = res + costo_ref*cant_ref;
	return res;
}

#endif // PETROLEO_H_INCLUDED
