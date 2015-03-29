#include "merge.h"

/**********************************************************************/
/****** FUNCIONES PARA EL MERGESORT CON CIUDADES **********************/
/**********************************************************************/

void merge_ej1(ciudad *a, int low, int high, int mid, bool ver)
{	
/* Función que mergea dos mitades de un arreglo de ciudades */

	// Variables declaration. 
	ciudad_t * b = new ciudad[high+1-low];
	int h,i,j,k;
	h = low;
	i = 0;
	j = mid+1;

	// Merges the two array's into b until the first one is finish
	while((h <= mid) && (j <= high))
	{
		if (ver){
			// ver == 1 -> ordeno por costfsafety
			if(a[h].costfsafety <= a[j].costfsafety){
				b[i] = a[h];
				h++;
			}else{
				b[i] = a[j];
				j++;
			}
			i++;
		}else{
			// ver == 0 -> ordeno por nombre
			if(a[h].nombre <= a[j].nombre){
				b[i] = a[h];
				h++;
			}else{
				b[i] = a[j];
				j++;
			}
			i++;
		}
	}
	// Completes the array filling in it the missing values
	if(h > mid)
	{
		for(k = j;k <= high;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	else
	{
		for(k = h;k <= mid;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	// Prints into the original array
	for(k = 0;k <= high-low;k++) 
	{
		a[k+low] = b[k];
	}
	delete[] b;
}

void mergesort_ej1(ciudad *a, int low, int high, bool b)
{
/* Mergesort para un arreglo de ciudades */

    int mid;
    if (low < high)
    {
        mid = (low+high)/2;
        mergesort_ej1(a,low,mid,b);
        mergesort_ej1(a,mid+1,high,b);
		merge_ej1(a,low,high,mid,b);
    }
    return;
}

/**********************************************************************/
/****** FUNCIONES PARA EL MERGESORT CON FRECUENCIAS *******************/
/**********************************************************************/

void merge_ej2(frecuencia *a, int low, int high, int mid)
{	
/* Función que mergea dos mitades de un arreglo de frecuencias,
 * comparándolas respecto al tiempo de inicio de transmisión.
 */
	// Variables declaration. 
	frecuencia_t * b = new frecuencia[high+1-low];
	int h,i,j,k;
	h = low;
	i = 0;
	j = mid+1;
	
	// Merges the two array's into b until the first one is finish
	while((h <= mid) && (j <= high))
	{
		if(a[h].inicio <= a[j].inicio){
			b[i] = a[h];
			h++;
		}else{
			b[i] = a[j];
			j++;
		}
		i++;
	}
	// Completes the array filling in it the missing values
	if(h > mid)
	{
		for(k = j;k <= high;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	else
	{
		for(k = h;k <= mid;k++)
		{
			b[i] = a[k];
			i++;
		}
	}
	// Prints into the original array
	for(k = 0;k <= high-low;k++) 
	{
		a[k+low] = b[k];
	}
	delete[] b;
}

void mergesort_ej2(frecuencia *a, int low, int high)
{
/* Mergesort para un arreglo de frecuencias */

    int mid;
    if (low < high)
    {
        mid = (low+high)/2;
        mergesort_ej2(a,low,mid,b);
        mergesort_ej2(a,mid+1,high,b);
		merge_ej2(a,low,high,mid,b);
    }
    return;
}

