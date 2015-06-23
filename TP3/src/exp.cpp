#include <cstdio>
#include "exp_exacto.h"
#include "exp_goloso.h"


int main()
{
	srand(time(0));
	
	// CORRER UNA VEZ CON CADA PODA
	exp_exacto_solitarios();
	exp_exacto_completos();	
	exp_exacto_k2_ord();	
	exp_exacto_k2_rnd();	
	exp_exacto_aleatorio();	
	
	exp_goloso_solitarios();
	exp_goloso_completos();
	exp_goloso_aleatorio();
	exp_goloso_estrellas();
}
