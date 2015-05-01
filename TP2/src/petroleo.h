#ifndef PETROLEO_H_INCLUDED
#define PETROLEO_H_INCLUDED

#include <algorithm>
#include <list>
#include <utility>
#include <vector>

using namespace std;

//~ typedef vector<int> Vec;
//~ typedef vector<Vec> Grafo;

typedef vector< list<int> > Adyacencia;	// arreglo con los vecinos
typedef pair<int,int> Arista;	// par de nodos unidos por una arista
typedef list< pair<Arista,int> > Incidencia;	// lista con pares de arista-peso



//~ int comp_conexas(Grafo g, int n, list<int>& refinerias);
//~ int petroleo(Grafo g, int n, list< pair<int,int> >& tuberias);


//~ int comp_conexas(Adyacencia ady, int n, list<int>& refinerias);
//~ void marcar_vecinos(Adyacencia ady, vector<bool>& vistos, int i);
int plan(Incidencia& inc, int n, list<Arista>& tuberias, int& costo_total,vector<int>& padres);
bool comparar_peso(const pair<Arista,int>& par1, const pair<Arista,int>& par2);
int petroleo(Incidencia inc,list<int>& refinerias,list<Arista>& tuberias,int n,int& cant_ref,int& cant_tub);

//~ int comp_conexas(Adyacencia ady, int n, list<int>& refinerias)
//~ {
	//~ int res = 0;
	//~ vector<bool> vistos(n,false);
	//~ 
	//~ for(int i = 0; i < n; i++)
	//~ {
		//~ if(!vistos[i])
		//~ {
			//~ refinerias.push_back(i);
			//~ res++;
			//~ marcar_vecinos(ady,vistos,i);
		//~ }
	//~ }
	//~ 
	//~ return res;
//~ }

//~ void marcar_vecinos(Adyacencia ady, vector<bool>& vistos, int i)
//~ {
	//~ int j;
	//~ 
	//~ for(list<int>::iterator it = ady[i].begin(); it != ady[i].end(); it++){
		//~ j = *it;
		//~ if(!vistos[j]){
			//~ marcar_vecinos(ady,vistos,j);
		//~ }
	//~ }
	//~ vistos[i] = true;
//~ }

int plan(Incidencia& inc, int n, list<Arista>& tuberias, int& costo_total,vector<int>& padres)
{
	int costo;
	int p1;
	int p2;
	int res = 0;
	Arista edge;
	//~ vector<int> padres(n,-1);
	vector< pair<int,list<int> > > hijos(n);
	
	for(int i = 0; i < n; i++)
	{
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
			if(p1 != p2)
			{
				if((p1 != -1) && (p2 != -1))
				{
					if(hijos[p1].first < hijos[p2].first){
						swap(p1,p2);	// p1 se queda con el que tiene más hijos
					}
					
					for(list<int>::iterator it2 = (hijos[p2].second).begin(); it2 != (hijos[p2].second).end(); it2++)
					{
						padres[*it2] = p1;
						(hijos[p1].second).push_back(*it2);
						hijos[p1].first++;
					}
					padres[p2] = p1;
					(hijos[p1].second).push_back(p2);
					hijos[p1].first++;
					
				}else if(p1 == -1){
					padres[edge.first] = p2;
					(hijos[p2].second).push_back(edge.first);
					hijos[p2].first++;
				}else{
					padres[edge.second] = p1;
					(hijos[p1].second).push_back(edge.second);
					hijos[p1].first++;
				}
			}else if (p1 == -1){
				padres[edge.first] = edge.first;
				padres[edge.second] = edge.first;
				(hijos[edge.first].second).push_back(edge.second);
				hijos[edge.first].first++;
			}
			
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
	int p;
	vector<int> padres(n,-1);
	//~ cant_ref = comp_conexas(ady,n,refinerias);
	//~ costo_total = costo_ref*cant_ref;
	//~ cant_ref = 0;
	int res = 0;
	cant_tub = plan(inc,n,tuberias,res,padres);
	vector<bool> aux(n,false);
	for(int i = 0; i < n; i++)
	{
		if(padres[i] == -1)	// nodo solitario
		{
			refinerias.push_back(i);
			cant_ref++;
		}else{
			p = padres[i];
			if(!aux[p])
			{
				aux[p] = true;
				refinerias.push_back(i);
				cant_ref++;
			}
		}
	}
	res = res + costo_ref*cant_ref;
	return res;
}


//~ int comp_conexas(Grafo g, int n, list<int, list<int> >& refinerias)
//~ {
	//~ int node;
	//~ int res = 0;
	//~ list<int> nodos;
	//~ List<int>::iterator it;
	//~ 
	//~ for(int i = 0; i < n; i++){
		//~ nodos.push_back(i);
	//~ }
	//~ 
	//~ while(!nodos.empty())
	//~ {
		//~ it = nodos.begin();
		//~ node = *it;
		//~ refinerias.push_back(node);
		//~ nodos.pop_front();
		//~ res++;
		//~ 
		//~ for(it = nodos.begin(); it != nodos.end(); it++)
		//~ {
			//~ if(g[node][*it] != -1){
				//~ it = nodos.erase(it);
			//~ }
		//~ }
	//~ }
	//~ 
	//~ return res;
//~ }
//~ 
//~ int petroleo(Grafo g, int n, list< pair<int,int> >& tuberias)
//~ {
	//~ int res = 0;
//~ }
//~ 

#endif // PETROLEO_H_INCLUDED
