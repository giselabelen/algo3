#include <cmath>
#include <cstdio>
#include "caballos.h"

void setear_amenaza(Tablero& tab, int fila, int columna, int n)
{
/* Función que dada una posición del tablero, determina si la misma es 
 * válida, y en ese caso, si estaba 'v' (vacía) coloca 'a' (amenazada)
 */
	if((0 <= fila) && (fila < n) && (0 <= columna) && (columna < n))
	{
		if(tab[fila][columna] == 'v')
		{
			tab[fila][columna] = 'a';
		}

	}
}



/**********************************************************************/
/**********************************************************************/

int main()
{
/* Lee los datos, separa la información, arma el tablero y llama a las 
 * funciones correspondientes para:
 * 		- marcar las posiciones cubiertas por los caballos dados
 * 		- realizar el backtraking
 * 		- 
 * Finalmente, arma la salida.
 */
	int n;
	int knights;
	int fila;
	int columna;
	int i;
	int j;
	int cota;
	int extras = 0;
	
	scanf("%i",&n);	// Levanto la cantidad de filas-columnas
	scanf("%i",&knights);	// Levanto la cantidad de caballos preubicados
	
	Tablero tab(n, Vec(n, 'v'));	// Creo un tablero de nxn y seteo todo con 'v' (vacío)
	
	for(i = 0; i < knights; i++)	// Para cada caballo preubicado
	{
		scanf("%i",&fila);	// Levanto la fila
		scanf("%i",&columna);	// Levanto la columna
		
		tab[fila][columna] = 'p';	// Seteo la posición en 'p' (preubicado)
		
		// Marco las casillas que quedan amenazadas por el caballo preubicado
		setear_amenaza(tab,fila-2,columna-1,n);	
		setear_amenaza(tab,fila-2,columna+1,n);
		setear_amenaza(tab,fila-1,columna-2,n);	
		setear_amenaza(tab,fila-1,columna+2,n);
		setear_amenaza(tab,fila+1,columna-2,n);
		setear_amenaza(tab,fila+1,columna+2,n);
		setear_amenaza(tab,fila+2,columna-1,n);
		setear_amenaza(tab,fila+2,columna+1,n);
	}
	
	cota = n * ceil(n/5);
	
	/** LLAMAR AL BACKTRACKING **/
	
	// Armo la salida
	printf("%i \n",extras);	// Cantidad de caballos extra
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(tab[i][j] == 'e'){
				printf("%i %i \n",i,j);	// Posición de cada caballo extra
			}
		}
	}
}

