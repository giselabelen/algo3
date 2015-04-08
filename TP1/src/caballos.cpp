#include <cmath>
#include <cstdio>
#include "caballos.h"

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

void backtranki(Tablero& tab,Tablero& tab_final, int fila, int columna, int n, int& cota, int lo_que_falta, int extras)
{
/* Función que realiza el backtraking */
	
	int f;
	int c;
	
	if(extras > cota)
	{	// Si me pasé de la cota o se me terminó el tablero, me voy, IMPORTANTE QUE VAYA PRIMEROA	
		return;
	}

	if(lo_que_falta == 0)	// Si ya llené el tablero, me guardo esa solución y me voy
	{
		copiar_tablero(tab,tab_final,n);
		cota = extras;
		return;
	}
	if(fila == n){		//es importante que este este despues
		return;
	}
	
	// Establezco la fila y columna para la siguiente llamada recursiva
	f = fila;
	c = columna + 1;
	if(c == n){
		f = fila +1;
		c = 0;
	}
	
	if(tab[fila][columna] != 'p')	// Si no había un caballo preubicado
	{
		Tablero copia_tab(n, Vec(n, 'v'));
		copiar_tablero(tab,copia_tab,n);	// Hago una copia del tablero

		int r = lo_que_falta;				//lo pongo en variable aparte, para que no rompa a
		int e = extras;						//lo_que_falta y a extras que estan fuera del if
		
		if(copia_tab[fila][columna] == 'v'){

			r--;
		}

		copia_tab[fila][columna] = 'e';	// pongo un caballo extra
		e++;

		
		
		// actualizo el tablero y lo que falta
		setear_amenaza(copia_tab,fila-2,columna-1,n,r);	
		setear_amenaza(copia_tab,fila-2,columna+1,n,r);
		setear_amenaza(copia_tab,fila-1,columna-2,n,r);	
		setear_amenaza(copia_tab,fila-1,columna+2,n,r);
		setear_amenaza(copia_tab,fila+1,columna-2,n,r);
		setear_amenaza(copia_tab,fila+1,columna+2,n,r);
		setear_amenaza(copia_tab,fila+2,columna-1,n,r);
		setear_amenaza(copia_tab,fila+2,columna+1,n,r);
		
		// llamada recursiva con el tablero actualizado
		backtranki(copia_tab,tab_final,f,c,n,cota,r,e);
	}

	// Llamada recursiva con el mismo tablero
	backtranki(tab,tab_final,f,c,n,cota,lo_que_falta,extras);
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
	int aux=0;

	scanf("%i",&n);	// Levanto la cantidad de filas-columnas
	scanf("%i",&knights);	// Levanto la cantidad de caballos preubicados
	
	Tablero tab(n, Vec(n, 'v'));	// Creo un tablero de nxn y seteo todo con 'v' (vacío)
	Tablero tab_final(n, Vec(n, 'v'));	//aca va a estar mi solucion
	
	for(i = 0; i < knights; i++)	// Para cada caballo preubicado
	{
		scanf("%i",&fila);	// Levanto la fila
		scanf("%i",&columna);	// Levanto la columna
		fila--;					//por que mi entrada va de 1 a n, y los vec empiezan de 0
		columna--;
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
	if(n<5){
		cota = 4;
	}else if(n == 6){

		cota = 8;
	}else{
		float c = n;
		cota = c * ceil(c/5);
	}
	// Llamo al backtraking
	backtranki(tab,tab_final,0,0,n,cota,falta_cubrir,extras);
	
	// Armo la salida
	printf("%i \n",cota);	// Cantidad de caballos extra
	
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
		{
			if(tab_final[i][j] == 'e'){
				printf("%i %i \n",i+1,j+1);	// Posición de cada caballo extra
			}
		}
	}
}
