#ifndef ZOMBIELAND_H_INCLUDED
#define ZOMBIELAND_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef struct pos_t
{
/* Estructura para representar una posición */
	
	int horizontal;
	int vertical;
	bool operator==(const pos_t p)const{
		return ((horizontal==p.horizontal)&&(vertical==p.vertical));}
} pos;

typedef struct esquina_t
{
/* Estructura para representar un nodo (esquina) */

	// Cant de zombies en cada dirección
	int arriba;
    int abajo;
    int izquierda;
    int derecha;
    
    // Posición de la que vengo
    pos origen;
    
    // Cantidad de soldados con los que llego
    int parcial;
    
} esquina; 

typedef vector<esquina> Vec;
typedef vector<Vec> Mapa;	/* el mapa es una matriz de "esquinas" */


/********************** DECLARACIÓN DE FUNCIONES **********************/

bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, /*int& cont,*/ int tope);
void zombieland(Mapa& ciudad, list<pair <pos,int> >& cola, int& soldados, pos bunker);
void armo_resultado(Mapa& ciudad, list<pos>& salida, pos inicio, pos bunker);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

bool recorridos(Mapa& ciudad, list<pair <pos,int> >& cola, int soldados, pos posicion, pos bunker, /*int& cont,*/ int tope)
{
/* Función que recorre el mapa buscando llegar al bunker */
	
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
	
	if(posicion == bunker)	// si ya estoy en el bunker, me voy
	{
		return true;
	}
	
	if(ciudad[i][j].derecha != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].derecha <= soldados) || (2*soldados - ciudad[i][j].derecha >= tope))
		{
			if(2*soldados - ciudad[i][j].derecha >= tope){
				// si se me mueren soldados
				soldD = 2*soldados - ciudad[i][j].derecha;
				topeD = tope - soldD;
			}else{
				// si no
				soldD = soldados;
				topeD = tope;
			}
				
			// aviso que ya pasé por esta cuadra
			ciudad[i][j].derecha = -1;
			ciudad[i][j+1].izquierda = -1;
			
			// esquina a la que llego
			pos_aux.horizontal = i;
			pos_aux.vertical = j+1;
			
			if(soldD > ciudad[i][j+1].parcial)	// si vale la pena
			{
				// guardo de dónde vine
				ciudad[i][j+1].origen = posicion;
				
				// cantidad de soldados vivos hasta acá
				ciudad[i][j+1].parcial = soldD;
			}
			
			// recursion
			res = recorridos(ciudad, cola, soldD, pos_aux, bunker,/*cont,*/topeD);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].abajo != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].abajo <= soldados) || (2*soldados - ciudad[i][j].abajo >= tope))
		{
			if(2*soldados - ciudad[i][j].abajo >= tope){
				// si se me mueren soldados
				soldAb = 2*soldados - ciudad[i][j].abajo;
				topeAb = tope - soldAb;
			}else{
				// si no
				soldAb = soldados;
				topeAb = tope;
			}
				
			// aviso que ya pasé por esta cuadra
			ciudad[i][j].abajo = -1;
			ciudad[i+1][j].arriba = -1;
			
			// esquina a la que llego
			pos_aux.horizontal = i+1;
			pos_aux.vertical = j;
			
			if(soldAb > ciudad[i+1][j].parcial)	// si vale la pena
			{
				// guardo de dónde vine
				ciudad[i+1][j].origen = posicion;
				
				// cantidad de soldados vivos hasta acá
				ciudad[i+1][j].parcial = soldAb;
			}
			
			// recursion
			res = recorridos(ciudad, cola, soldAb, pos_aux, bunker,/*cont,*/topeAb);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].arriba != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].arriba <= soldados) || (2*soldados - ciudad[i][j].arriba >= tope))
		{
			if(2*soldados - ciudad[i][j].arriba >= tope){
				// si se me mueren soldados
				soldAr = 2*soldados - ciudad[i][j].arriba;
				topeAr = tope - soldAr;
			}else{
				// si no
				soldAr = soldados;
				topeAr = tope;
			}
			
			// aviso que ya pasé por esta cuadra
			ciudad[i][j].arriba = -1;
			ciudad[i-1][j].abajo = -1;
			
			// esquina a la que llego
			pos_aux.horizontal = i-1;
			pos_aux.vertical = j;
			
			if(soldAr > ciudad[i-1][j].parcial)	// si vale la pena
			{
				// guardo de dónde vine
				ciudad[i-1][j].origen = posicion;
				
				// cantidad de soldados vivos hasta acá
				ciudad[i-1][j].parcial = soldAr;
			}
			
			// recursion
			res = recorridos(ciudad, cola, soldAr, pos_aux, bunker,/*cont,*/topeAr);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].izquierda != -1)	// si es calle válida
	{
		// si puedo pasar por esa calle
		if((ciudad[i][j].izquierda <= soldados) || (2*soldados - ciudad[i][j].izquierda >= tope))
		{
			if(2*soldados - ciudad[i][j].izquierda >= tope){
				// si se me mueren soldados
				soldI = 2*soldados - ciudad[i][j].izquierda;
				topeI = tope - soldI;
			}else{
				// si no
				soldI = soldados;
				topeI = tope;
			}
		
			// aviso que ya pasé por esta cuadra
			ciudad[i][j].izquierda = -1;
			ciudad[i][j-1].derecha = -1;
			
			// esquina a la que llego
			pos_aux.horizontal = i;
			pos_aux.vertical = j-1;
			
			if(soldI > ciudad[i][j-1].parcial)	// si vale la pena
			{
				// guardo de dónde vine
				ciudad[i][j-1].origen = posicion;
				
				// cantidad de soldados vivos hasta acá
				ciudad[i][j-1].parcial = soldI;
			}
						
			// recursion
			res = recorridos(ciudad, cola, soldI, pos_aux, bunker,/*cont,*/topeI);
			if(res){ return res; }
		}
	}
	
	if(ciudad[i][j].arriba > soldados || ciudad[i][j].abajo > soldados ||
		ciudad[i][j].izquierda > soldados || ciudad[i][j].derecha > soldados) 
	{
		bp = make_pair(posicion,soldados);
		cola.push_back(bp);
		//~ cont++;
	}
	
	return false;
}


void zombieland(Mapa& ciudad, list<pair <pos,int> >& cola, int& soldados, pos bunker)
{
	//~ int contador;
	//~ int cont_aux = 1;
	int sold_aux;
	int tope = soldados;
	bool res = false;
	pos posicion;
	
	while(tope > 0 && !res)	// todavía tengo soldados y no encontré solución
	{
		//~ contador = cont_aux;	// cant de elementos a mirar en la cola
		
		//~ while(contador > 0 && !res)	// todavía tengo elementos para ver y no encontré solución
		//~ {
			posicion = (cola.front()).first;
			sold_aux = (cola.front()).second;
			cola.pop_front();
			res = res || recorridos(ciudad, cola, sold_aux, posicion, bunker, /*cont_aux,*/ tope);
		//~ }
		
		tope--;
	}
	
	if(!res){ 
		soldados = 0; // se mueren todos
	}
	else{
		soldados = tope + 1; // soldados que llegan vivos
	}

	return;
}


void armo_resultado(Mapa& ciudad, list<pos>& salida, pos inicio, pos bunker)
{
	int i;
	int j;
	pos posicion = bunker;
	salida.push_front(bunker);	// apilo la posición del bunker
		
	while(!(posicion == inicio))	// hasta llegar al inicio
	{
		i = posicion.horizontal;
		j = posicion.vertical;
		posicion = ciudad[i][j].origen;
		salida.push_front(posicion);	// apilo el origen de cada nodo
	}
	
	return;
}

#endif // ZOMBIELAND_H_INCLUDED
