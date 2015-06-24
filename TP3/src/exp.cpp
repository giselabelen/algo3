#include <cstdio>
#include "exp_exacto.h"
#include "exp_goloso.h"


int main()
{
	srand(time(0));
	
	// CORRER UNA VEZ CON CADA PODA
	exp_exacto_solitarios(3,20);
	exp_exacto_completos(3,20);	
	exp_exacto_k2_ord(10);	
	exp_exacto_k2_rnd(10);	
	exp_exacto_aleatorio(2,12,100);	
	
	exp_goloso_solitarios(3,20);
	exp_goloso_completos(5,100);
	exp_goloso_aleatorio(4,15,1000);
	exp_goloso_estrellas(5,10,1000);
	exp_goloso_circuito_ord(1000);
	exp_goloso_circuito_rnd(1000);
	exp_goloso_galaxias(6,10,20,1000);
}
