#include <cmath>
#include <cstdio>
#include "caballos.h"

Tablero tab_final;

void setear_amenaza(Tablero& tab, int fila, int columna, int n, int& dec)
{
/* Función que dada una posición del tablero, determina si la misma es 
 * válida, y en ese caso, si estaba 'v' (vacía) coloca 'a' (amenazada)
 */
	if((0 <= fila) && (fila < n) && (0 <= columna) && (columna < n))
	{
		if(tab[fila][columna] == 'v')
		{
			tab[fila][columna] = 'a';
			dec--;
		}
	}
}

void copiar_tablero(Tablero& tab, Tablero& copia, int n)
{	
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			copia[i][j] = tab[i][j];
		}
	}
}

void backtranki(Tablero& tab, int fila, int columna, int n, int& cota, int lo_que_falta, int extras)
{
/* Función que realiza el backtraking */
	
	Tablero copia_tab(n, Vec(n, 'v'));
	int f;
	int c;
	
	if(lo_que_falta == 0)	// Si ya llené el tablero, me guardo esa solución y me voy
	{
		copiar_tablero(tab,tab_final,n);
		cota = extras;
		return;
	}
	
	if(extras > cota || fila == n)
	{	// Si me pasé de la cota o se me terminó el tablero, me voy	
		return;
	}
	
	// Establezco la fila y columna para la siguiente llamada recursiva
	if(columna == n){
		f = fila++;
		c = 0;
	}else{
		f = fila;
		c = columna++;
	}
	
	if(copia_tab[fila][columna] != 'p')	// Si no había un caballo preubicado
	{
		copiar_tablero(tab,copia_tab,n);	// Hago una copia del tablero
		
		copia_tab[fila][columna] = 'e';	// pongo un caballo extra
		extras++;
		lo_que_falta--;
		
		// actualizo el tablero y lo que falta
		setear_amenaza(copia_tab,fila-2,columna-1,n,lo_que_falta);	
		setear_amenaza(copia_tab,fila-2,columna+1,n,lo_que_falta);
		setear_amenaza(copia_tab,fila-1,columna-2,n,lo_que_falta);	
		setear_amenaza(copia_tab,fila-1,columna+2,n,lo_que_falta);
		setear_amenaza(copia_tab,fila+1,columna-2,n,lo_que_falta);
		setear_amenaza(copia_tab,fila+1,columna+2,n,lo_que_falta);
		setear_amenaza(copia_tab,fila+2,columna-1,n,lo_que_falta);
		setear_amenaza(copia_tab,fila+2,columna+1,n,lo_que_falta);
		
		// llamada recursiva con el tablero actualizado
		//if(columna == n){
		//	f = fila++;
		//	c = 0;
		//}else{
		//	f = fila;
		//	c = columna++;
		//}
		backtranki(copia_tab,f,c,n,cota,lo_que_falta,extras);
		//backtranki(tab,f,c,n,cota,lo_que_falta,extras);
}
	}//else{
	// Llamada recursiva con el mismo tablero
		//if(columna == n){
		//	f = fila++;
		//	c = 0;
		//}else{
		//	f = fila;
		//	c = columna++;
		//}
		backtranki(tab,f,c,n,cota,lo_que_falta,extras);
	//}
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
	int falta_cubrir = 0;
	int extras = 0;
	int aux;
	
	scanf("%i",&n);	// Levanto la cantidad de filas-columnas
	scanf("%i",&knights);	// Levanto la cantidad de caballos preubicados
	
	Tablero tab(n, Vec(n, 'v'));	// Creo un tablero de nxn y seteo todo con 'v' (vacío)
	
	for(i = 0; i < knights; i++)	// Para cada caballo preubicado
	{
		scanf("%i",&fila);	// Levanto la fila
		scanf("%i",&columna);	// Levanto la columna
		
		tab[fila][columna] = 'p';	// Seteo la posición en 'p' (preubicado)
		
		// Marco las casillas que quedan amenazadas por el caballo preubicado
		setear_amenaza(tab,fila-2,columna-1,n,aux);	
		setear_amenaza(tab,fila-2,columna+1,n,aux);
		setear_amenaza(tab,fila-1,columna-2,n,aux);	
		setear_amenaza(tab,fila-1,columna+2,n,aux);
		setear_amenaza(tab,fila+1,columna-2,n,aux);
		setear_amenaza(tab,fila+1,columna+2,n,aux);
		setear_amenaza(tab,fila+2,columna-1,n,aux);
		setear_amenaza(tab,fila+2,columna+1,n,aux);
	}
	
	// Guardo cuántas casillas faltan cubrir, para ir sabiendo si ya terminé
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(tab[i][j] == 'v'){
				falta_cubrir++;
			}
		}
	}
	
	cota = n * ceil(n/5);
	
	// Llamo al backtraking
	backtranki(tab,0,0,n,cota,falta_cubrir,extras);
	
	// Armo la salida
	printf("%i \n",cota);	// Cantidad de caballos extra
	
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

