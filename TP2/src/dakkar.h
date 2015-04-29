#ifndef DAKKAR_H_INCLUDED
#define DAKKAR_H_INCLUDED

#include <list>
#include <utility>
#include <vector>

using namespace std;


/**************************** ESTRUCTURAS ****************************/

typedef pair< int,int > Optimo;	/* (tiempo,vehículo) */
typedef vector<Optimo> Vec;
typedef vector<Vec> Etapa;	/* Una matriz por etapa */
typedef vector<Etapa> Carrera;

/********************** DECLARACIÓN DE FUNCIONES **********************/

Optimo eleccion(int bici, int moto, int buggy);
Carrera dakkar(int n, int km, int kb, int* bici, int* moto, int* buggy);
int armo_salida(Carrera etapas, int km, int kb, int n, list<int>& salida);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

Optimo eleccion(int bici, int moto, int buggy)
{
/* Dados los tiempos de 3 vehículos, elige el mejor y lo devuelve 
 * indicando de qué vehículo se trata: 1 para bici, 2 para moto y 
 * 3 para buggy. Si alguno de los valores es -1 no tengo que mirarlo 
 * y sólo debo comparar los otros dos. El valor de bici nunca será -1.
 */
	Optimo res;
	
	if(moto == -1)	// bici contra buggy
	{
		if(bici <= buggy){
			res = make_pair(bici,1);	// gana bici
		}else{
			res = make_pair(buggy,3);	// gana buggy
		}
		
	}else if(buggy == -1)	// bici contra moto
	{
		if(bici <= moto){
			res = make_pair(bici,1);	// gana bici
		}else{
			res = make_pair(moto,2);	// gana moto
		}
	}else{	// todos contra todos
		if((bici <= moto) && (bici <= buggy)){
			res = make_pair(bici,1);	// gana bici
		}else if(moto <= buggy){
			res = make_pair(moto,2);	// gana moto
		}else{
			res = make_pair(buggy,3);	// gana buggy
		}
	}
	return res;
}

Carrera dakkar(int n, int km, int kb, int* bici, int* moto, int* buggy)
{
	int h;
	int i;
	int j;
	Optimo aux;
	Carrera etapas(n, Etapa(kb+1, Vec(km+1)));
	
	// Lleno los datos de la primera etapa (etapas[0])
	
	// posición (0,0)
	etapas[0][0][0] = make_pair(bici[0],1);
	
	// posiciones (0,1) a (0,km)
	aux = eleccion(bici[0],moto[0],-1);
	for(j = 1; j <= km; j++){
		etapas[0][0][j] = aux;
	}
	
	// posiciones (1,0) a (kb,0)
	aux = eleccion(bici[0],-1,buggy[0]);
	for(i = 1; i <= kb; i++){
		etapas[0][i][0] = aux;
	}
	
	// demás posiciones
	aux = eleccion(bici[0],moto[0],buggy[0]);
	for(i = 1; i <= kb; i++){
		for(j = 1; j <= km; j++){
			etapas[0][i][j] = aux;
		}
	}
	
	// Armo las demás etapas (etapas[1] a etapas[n-1])
	for(h = 1; h < n; h++)
	{
		// posición (0,0)
		etapas[h][0][0] = make_pair(etapas[h-1][0][0].first + bici[h],1);
		
		// posiciones (0,1) a (0,km)
		for(j = 1; j <= km; j++){
			aux = eleccion(etapas[h-1][0][j].first + bici[h],etapas[h-1][0][j-1].first + moto[h],-1);
			etapas[h][0][j] = aux;
		}
		
		// posiciones (1,0) a (kb,0)
		for(i = 1; i <= kb; i++){
			aux = eleccion(etapas[h-1][i][0].first + bici[h],-1,etapas[h-1][i-1][0].first + buggy[h]);
			etapas[h][i][0] = aux;
		}
		
		// demás posiciones
		for(i = 1; i <= kb; i++)
		{
			for(j = 1; j <= km; j++)
			{
				aux = eleccion(etapas[h-1][i][j].first + bici[h],etapas[h-1][i][j-1].first + moto[h],etapas[h-1][i-1][j].first + buggy[h]);
				etapas[h][i][j] = aux;
			}
		}
	}
	
	return etapas;
}

int armo_salida(Carrera etapas, int km, int kb, int n, list<int>& salida)
{
/* Función que recorre las matrices de etapas y determina el tiempo
 * total incurrido y el vehículo utilizado en cada etapa.  Empieza
 * en la última etapa y termina con la primera.
 */
	int aux;
	int i = kb;
	int j = km;
	int res = etapas[n-1][i][j].first;	// tiempo total incurrido
	
	for(int h = n-1; h >= 0; h--)
	{
		// apilo vehículo
		salida.push_front(etapas[h][i][j].second);
		
		// acomodo índices
		if(etapas[h][i][j].second == 2){
			j--;
		}else if(etapas[h][i][j].second == 3){
			i--;
		}
	}
	
	return res;
}


#endif // DAKKAR_H_INCLUDED
