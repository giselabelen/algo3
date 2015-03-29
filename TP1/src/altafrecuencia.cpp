#include <cmath>
#include <cstdio>
#include <iostream>
#include "merge.h"
#include "altafrecuencia.h"

using namespace std;

//~ list<transmision> mezclar_freq(list<transmision> trans1, list<transmision> it_trans2)
//~ {
	// Variables declaration. 
	//~ frecuencia_t * b = new frecuencia[high+1-low];
	//~ int h,i,j,k;
	//~ h = low;
	//~ i = 0;
	//~ j = mid+1;
	//~ // Merges the two array's into b until the first one is finish
	//~ while((h <= mid) && (j <= high))
	//~ {
		//~ if(a[h].inicio <= a[j].inicio){
			//~ b[i] = a[h];
			//~ h++;
		//~ }else{
			//~ b[i] = a[j];
			//~ j++;
		//~ }
		//~ i++;
	//~ }
	// Completes the array filling in it the missing values
	//~ if(h > mid)
	//~ {
		//~ for(k = j;k <= high;k++)
		//~ {
			//~ b[i] = a[k];
			//~ i++;
		//~ }
	//~ }
	//~ else
	//~ {
		//~ for(k = h;k <= mid;k++)
		//~ {
			//~ b[i] = a[k];
			//~ i++;
		//~ }
	//~ }
	//~ // Prints into the original array
	//~ for(k = 0;k <= high-low;k++) 
	//~ {
		//~ a[k+low] = b[k];
	//~ }
	//~ delete[] b;
//~ }


//~ list<transmision> frequency_dc(frecuencia* freq, int low, int high, int costo)
//~ {
	//~ int mid;
	//~ list<transmision> trans1;
	//~ list<transmision> trans2;
	//~ list<transmision> trans_final;
    //~ if (low < high)
    //~ {
        //~ mid = (low+high)/2;
        //~ trans1 = frequency_dc(freq,low,mid);
        //~ trans2 = frequency_dc(freq,mid+1,high);
		//~ trans_final = mezclar_freq(trans1,trans2);
    //~ }else{
			//~ /** ARMAR UNA LISTA DE 1 ELEMENTO **/
	//~ }
    //~ return trans_final;
//~ }

/**********************************************************************/
/**********************************************************************/

int main()
{
/* Lee los datos, separa la información, y llama a las funciones 
 * correspondientes para:
 * 		- ordenar las frecuencias por tiempo de inicio
 * 		- hacer el divide and conquer
 * Finalmente, arma la salida.
 */
	int i;
    int n;
    int p;
    int costo_por_minuto;
    int start;
    int end;
	//~ int costo_total;
    frecuencia freq;
    //~ list<transmision> res;
    
    scanf("%i",&n);	// Levanto la cantidad de frecuencias
    
    frecuencia total_freq[n];	// Arreglo donde voy a ir metiendo las frecuencias
       
    for (i = 0; i < n; i++)			// Para cada frecuencia
    {
		scanf("%i",&costo_por_minuto);	// Levanto los datos
		scanf("%i",&start);
		scanf("%i",&end);
		freq = (frecuencia){			// Lleno el struct
			.nombre = i,
			.costfminute = costo_por_minuto,
			.inicio = start,
			.fin = end,
		};
		total_freq[i] = freq;			// Guardo la frecuencia en el arreglo
	}
	
    // Ordeno por tiempo de inicio
    mergesort_ej2(total_freq,0,n-1);
    
    // Hago el divide and conquer
     //~ res = frequency_dc(total_freq,low,high,costo_total);
    
    // Armo la salida
	
}
