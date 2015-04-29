#ifndef PETROLEO_H_INCLUDED
#define PETROLEO_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;

typedef vector<int> Vec;
typedef vector<Vec> Grafo;



int comp_conexas(Grafo g, int n, list<int>& refinerias);
int petroleo(Grafo g, int n, list< pair<int,int> >& tuberias);



int comp_conexas(Grafo g, int n, list<int, list<int> >& refinerias)
{
	int node;
	int res = 0;
	list<int> nodos;
	List<int>::iterator it;
	
	for(int i = 0; i < n; i++){
		nodos.push_back(i);
	}
	
	while(!nodos.empty())
	{
		it = nodos.begin();
		node = *it;
		refinerias.push_back(node);
		nodos.pop_front();
		res++;
		
		for(it = nodos.begin(); it != nodos.end(); it++)
		{
			if(g[node][*it] != -1){
				it = nodos.erase(it);
			}
		}
	}
	
	return res;
}

int petroleo(Grafo g, int n, list< pair<int,int> >& tuberias)
{
	int res = 0;
}


#endif // PETROLEO_H_INCLUDED
