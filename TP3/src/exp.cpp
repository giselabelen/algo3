#include <cstdio>
#include "exp_exacto.h"
#include "exp_goloso.h"
#include "exp_busqlocal.h"
#include "exp_grasp.h"
#include "exp_final.h"


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
	//~ cout << "galaxias" << endl;
	//~ exp_busqlocal_galaxias(8,9);
	
	//~ cout << "aleatorio" << endl;
	//~ exp_grasp_aleatorio(10,30);
	//~ cout << "aleatorio_comp" << endl;
	//~ exp_grasp_aleatorio_comp(4,15);
	//~ cout << "estrellas" << endl;
	//~ exp_grasp_estrellas(5,7);
	//~ cout << "circuitos" << endl;
	//~ exp_grasp_circuito_rnd(10,30);
	//~ cout << "galaxias" << endl;
	//~ exp_grasp_galaxias(5,5);
	
	//~ cout << "aleatorio" << endl;
	//~ exp_final_aleatorio(31,40);
	//~ cout << "aleatorio_comp" << endl;
	//~ exp_final_aleatorio_comp(4,15);
	//~ cout << "estrellas" << endl;
	//~ exp_final_estrellas(5,10);
	cout << "circuitos" << endl;
	exp_final_circuito_rnd(41,50);
	//~ cout << "galaxias" << endl;
	//~ exp_final_galaxias(5,7);
	
}
