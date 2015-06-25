#include <cstdio>
#include "exp_exacto.h"
#include "exp_goloso.h"


int main()
{
	srand(time(0));
	
	//~ cout << "solitarios" << endl;
	//~ exp_exacto_solitarios(3,20);
	//~ cout << "completos" << endl;
	//~ exp_exacto_completos(3,20);	
	//~ cout << "k2 ordenados" << endl;
	//~ exp_exacto_k2_ord(10);
	//~ cout << "k2 random" << endl;
	//~ exp_exacto_k2_rnd(10);
	//~ cout << "aleatorio" << endl;
	//~ exp_exacto_aleatorio(5,18,500);	
	
	exp_goloso_solitarios(10,1000);
	exp_goloso_completos(5,100);
	exp_goloso_aleatorio(4,1000,10000);
	exp_goloso_aleatorio_comp(4,15,1000);
	exp_goloso_estrellas(5,50,1000);
	exp_goloso_circuito_ord(5,100);
	exp_goloso_circuito_rnd(5,100);
	exp_goloso_galaxias(6,25,50,1000);
}
