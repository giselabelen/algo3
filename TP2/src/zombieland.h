#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;

typedef struct pos_t
{
	int horizontal;
	int vertical;
	bool operator==(const pos_t p)const{
		return ((horizontal==p.horizontal)&&(vertical==p.vertical));}
} pos;

typedef struct esquina_t
{
	// Cant de zombies en cada dirección
	int arriba;
    int abajo;
    int izquierda;
    int derecha;
    
    // Posiciones de las que vengo
    list<pos> origen;
    
}esquina; //= {-1, -1, -1, -1};	// Por los casos borde

typedef vector<esquina> Vec;
typedef vector<Vec> Mapa;

bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, int& cont, int tope);
bool zombieland(Mapa& ciudad, list<pair <pos,int> >& cola, int& soldados, pos bunker);
void armo_resultado(Mapa& ciudad, list<pos> salida);


bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, int& cont, int tope)
{	
	bool res;
	pos pos_aux;
	pair <pos,int> bp;
	int topeAr;
	int topeAb;
	int topeI;
	int topeD;
	int soldAr;
	int soldAb;
	int soldI;
	int soldD;
	
	int i = posicion.horizontal;
	int j = posicion.vertical;
	
	if(posicion == bunker)	// si ya llegué al bunker me voy
	{
		return true;
	}
	
	if(ciudad[i][j].arriba != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].arriba <= soldados) || (2*soldados - ciudad[i][j].arriba >= tope))
		{
			if(2*soldados - ciudad[i][j].arriba >= tope)	// si se me mueren soldados
			{
				soldAr = 2*soldados - ciudad[i][j].arriba;
				topeAr = tope - soldAr;
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
			res = recorridos(ciudad, cola, soldAr, pos_aux, bunker,cont,topeAr);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].abajo != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].abajo <= soldados) || (2*soldados - ciudad[i][j].abajo >= tope))
		{
			if(2*soldados - ciudad[i][j].abajo >= tope)	// si se me mueren soldados
			{
				soldAb = 2*soldados - ciudad[i][j].abajo;
				topeAb = tope - soldAb;
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
			res = recorridos(ciudad, cola, soldAb, pos_aux, bunker,cont,topeAb);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].izquierda != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].izquierda <= soldados) || (2*soldados - ciudad[i][j].izquierda >= tope))
		{
			if(2*soldados - ciudad[i][j].izquierda >= tope)	// si se me mueren soldados
			{
				soldI = 2*soldados - ciudad[i][j].izquierda;
				topeI = tope - soldI;
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
			res = recorridos(ciudad, cola, soldI, pos_aux, bunker,cont,topeI);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].derecha != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].derecha <= soldados) || (2*soldados - ciudad[i][j].derecha >= tope))
		{
			if(2*soldados - ciudad[i][j].derecha >= tope)	// si se me mueren soldados
			{
				soldD = 2*soldados - ciudad[i][j].derecha;
				topeD = tope - soldD;
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
			res = recorridos(ciudad, cola, soldD, pos_aux, bunker,cont,topeD);
			if(res){ return res; }
		}
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
			posicion = (cola.front()).first;
			sold_aux = (cola.front()).second;
			cola.pop_front();
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


void armo_resultado(Mapa& ciudad, list<pos> salida)
{
	
}

#endif // ZOMBIELAND_H_INCLUDED
