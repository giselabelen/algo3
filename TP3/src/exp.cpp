#include <cstdio>
#include "exp_exacto.h"
#include "exp_goloso.h"
#include "exp_busqlocal.h"
#include "exp_grasp.h"


int main()
{
	srand(time(0));
	
	//~ cout << "solitarios" << endl;
	//~ exp_exacto_solitarios(3,20);
	//~ cout << "completos" << endl;
	//~ exp_exacto_completos(3,20);	
	//~ cout << "k2 ordenados" << endl;
	//~ exp_exacto_k2_ord(9);
	//~ cout << "k2 random" << endl;
	//~ exp_exacto_k2_rnd(9);
	//~ cout << "aleatorio" << endl;
	//~ exp_exacto_aleatorio(5,18);	
	//~ 
	//~ cout << "solitarios" << endl;
	//~ exp_goloso_solitarios(10,1000);
	//~ cout << "completos" << endl;
	//~ exp_goloso_completos(10,400);
	//~ cout << "aleatorio" << endl;
	//~ exp_goloso_aleatorio(4,200);
	//~ cout << "aleatorio_comp" << endl;
	//~ exp_goloso_aleatorio_comp(4,15);
	//~ cout << "estrellas" << endl;
	//~ exp_goloso_estrellas(10,100);
	//~ cout << "circuito_ord" << endl;
	//~ exp_goloso_circuito_ord(5,100);
	//~ cout << "circuito_rnd" << endl;
	//~ exp_goloso_circuito_rnd(5,100);
	//~ cout << "galaxias" << endl;
	//~ exp_goloso_galaxias(10,100);
	//~ 
	//~ cout << "aleatorio" << endl;
	//~ exp_busqlocal_aleatorio(4,50);
	//~ cout << "aleatorio_comp" << endl;
	//~ exp_busqlocal_aleatorio_comp(4,15);
	//~ cout << "estrellas" << endl;
	//~ exp_busqlocal_estrellas(5,10);
	//~ cout << "circuitos" << endl;
	//~ exp_busqlocal_circuito_rnd(5,50);
	cout << "galaxias" << endl;
	exp_busqlocal_galaxias(8,9);
	
	//~ cout << "aleatorio" << endl;
	//~ exp_grasp_aleatorio(4,20,50);
	//~ cout << "aleatorio_comp" << endl;
	//~ exp_grasp_aleatorio_comp(4,15,100);
	
	//~ list<double> lista;
	//~ for(double i = 0; i < 10; i++)
	//~ {
		//~ lista.push_back(i);
	//~ }
	//~ sacar_outliers(lista);
	//~ for(list<double>::iterator it = lista.begin(); it != lista.end(); it++)
	//~ {
		//~ printf("%f ",*it);
	//~ }
	//~ double cosa = 9870.867976;
	//~ cout << cosa << endl;
	
}
