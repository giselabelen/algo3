#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

#include <list>
#include <utility>

using namespace std;

typedef vector<esquina> Vec;
typedef vector<Vec> Mapa;

typedef struct esquina_t
{
	// Cant de zombies en cada dirección
	int arriba;
    int abajo;
    int izquierda;
    int derecha;
    
    // Posiciones de las que vengo
    list<pos> origen;
    
} esquina = {-1, -1, -1, -1};	// Por los casos borde

typedef struct pos_t
{
	int horizontal;
	int vertical;
} pos;

bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, int& cont, int tope);

bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, int& cont, int tope)
{	
	bool res;
	pos pos_aux;
	pair <pos,int> bp;
	
	int i = posicion.horizontal;
	int j = posicion.vertical;
	
	if(posicion == bunker)	// si ya llegué al bunker me voy
	{
		return true;
	}
	
	if(ciudad[i][j].arriba != -1)	// si es calle válida
	{
		if((ciudad[i][j].arriba <= soldados) || (2*soldados - ciudad[i][j].arriba >= tope))
		{
			if(2*soldados - ciudad[i][j].arriba >= tope)
			{
				soldados = 2*soldados - ciudad[i][j].arriba;
				tope = tope - soldados;
			}
			
			// aviso que ya pasé por esta cuadra
			ciudad[i][j].arriba = -1;
			ciudad[i-1][j].abajo = -1;
			
			// esquina a la que llego
			pos_aux.horizontal = i-1;
			pos_aux.vertical = j;
			
			// guardo de dónde vine
			(ciudad[i-1][j].origen).push_back(posicion);
			
			// recursion
			res = recorridos(ciudad, cola, soldados, pos_aux, bunker,cont,tope);
			if(res){ return res; }
		}
	}
	
	if((ciudad[i][j].abajo != -1) && (ciudad[i][j].abajo <= soldados))
	{
		if(ciudad[i][j].abajo == soldados && tol == 1)
		{
			tol = 0;
			soldados--;
		}
		
		// aviso que ya pasé por esta cuadra
		ciudad[i][j].abajo = -1;
		ciudad[i+1][j].arriba = -1;
		
		// esquina a la que llego
		pos_aux.horizontal = i+1;
		pos_aux.vertical = j;
		
		// guardo de dónde vine
		(ciudad[i+1][j].origen).push_back(posicion);
		
		// recursion
		res = recorridos(ciudad, cola, soldados, pos_aux, bunker,cont,tol);
		if(res){ return res; }
	}
	
	if((ciudad[i][j].izquierda != -1) && (ciudad[i][j].izquierda <= soldados))
	{
		if(ciudad[i][j].iquierda == soldados && tol == 1)
		{
			tol = 0;
			soldados--;
		}
		
		// aviso que ya pasé por esta cuadra
		ciudad[i][j].izquierda = -1;
		ciudad[i][j-1].derecha = -1;
		
		// esquina a la que llego
		pos_aux.horizontal = i;
		pos_aux.vertical = j-1;
		
		// guardo de dónde vine
		(ciudad[i][j-1].origen).push_back(posicion);
		
		// recursion
		res = recorridos(ciudad, cola, soldados, pos_aux, bunker,cont,tol);
		if(res){ return res; }
	}
	
	if((ciudad[i][j].derecha != -1) && (ciudad[i][j].derecha <= soldados))
	{
		if(ciudad[i][j].arriba == soldados && tol == 1)
		{
			tol = 0;
			soldados--;
		}
		
		// aviso que ya pasé por esta cuadra
		ciudad[i][j].derecha = -1;
		ciudad[i][j+1].izquierda = -1;
		
		// esquina a la que llego
		pos_aux.horizontal = i;
		pos_aux.vertical = j+1;
		
		// guardo de dónde vine
		(ciudad[i][j+1].origen).push_back(posicion);
		
		// recursion
		res = recorridos(ciudad, cola, soldados, pos_aux, bunker,cont,tol);
		if(res){ return res; }
	}
	
	if(ciudad[i][j].arriba > soldados || ciudad[i][j].abajo > soldados ||
		ciudad[i][j].izquierda > soldados || ciudad[i][j].derecha > soldados)
	{
		bp = make_pair(posicion,soldados);
		cola.push_back(bp);
		cont++;
	}
	
	return false;
}


bool zombieland(Mapa& ciudad, list<pair <pos,int> >& cola, int& soldados, pos bunker)
{
	int contador;
	int cont_aux = 1;
	int sold_aux;
	int tope = soldados;
	bool res = false;
	pos posicion;
	
	while(tope > 0 && !res)
	{
		contador = cont_aux;
		
		while(contador > 0 && !res)
		{
			posicion = (cola.pop_front()).first;
			sold_aux = (cola.pop_front()).second;
			res = res || recorridos(ciudad, cola, sold_aux, posicion, bunker, cont_aux, tope);
		}
		
		tope--;
	}
	
	if(!res){ 
		soldados = 0; // se mueren todos
	}
	else{
		soldados = tope + 1; // soldados que llegan vivos
	}

	return res;
}

#endif // ZOMBIELAND_H_INCLUDED
