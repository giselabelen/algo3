#ifndef TESTING2_H_INCLUDED
#define TESTING2_H_INCLUDED
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "zombieland.h"

using namespace std;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Mapa generar_ciudad(int n, int m, int s);
Mapa generar_ciudad_facil(int n, int m, int s);
Mapa generar_ciudad_zigzag(int n, int m, int s);
void completar_derecha(Mapa& ciudad, int i, int n, int m, int& zombies,int s);
void completar_izquierda(Mapa& ciudad, int i, int n, int m, int& zombies,int s);
void restablecer(Mapa& ciudad, int n, int m, int s);
list<int> zombies_aleatorios(int total, int s);
void anular(Mapa& ciudad, int n, int m, int s);
void testear_2_A();
void testear_2_B();
void testear_2_C();


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

list<int> zombies_aleatorios(int total, int s)
{
	int z;
	int tope = 2*s + 1;
	int diez = total*10/100;
	int veinte = total*20/100;
	int resto = total - (diez + veinte);
	list<int> z_random;
	
	for(int i = 0; i < total; i++)
	{
		z = rand() % tope;
		z_random.push_back(z);
		
		if(s < z && z <= (s + s/2))
		{
			veinte--;
			if(veinte == 0)
			{
				if(diez == 0){
					tope = s + 1;
				}else{
					veinte = diez;
					diez = 0;
					tope = s + s/2 + 1;
				}
			}
		}
		
		if(s > (s + s/2))
		{
			diez--;
			if(diez == 0){
				tope = s + s/2 + 1;
			}
		}
	}
	
	return z_random;
}


Mapa generar_ciudad(int n, int m, int s)
{
	//~ 
	//~ /** OJO ACA **/
	//~ FILE * pCiudad = fopen("../Resultados_tests_nuestros/ciudad.txt","w");
	
	
	int r;
	int contador = n*(m-1) + m*(n-1);
	list<int> z_random = zombies_aleatorios(contador,s);
	list<int>::iterator it;
	Mapa ciudad(n, Vect(m));
	
	// señalo las calles inválidas (bordes)
	for(int i = 0; i < n; i++){
		ciudad[i][0].izquierda = -1;
		ciudad[i][m-1].derecha = -1;
	}
	for(int j = 0; j < m; j++){
		ciudad[0][j].arriba = -1;
		ciudad[n-1][j].abajo = -1;
	}
	
	// valor por defecto para .parcial (para cada nodo)
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			ciudad[i][j].parcial = 0;
		}
	}
	
	// Cant de zombies x calle
	for(int i = 0; i < n; i++)
	{
		
			//~ /** OJO ACA **/
			//~ fprintf(pCiudad,"\n");
			//~ 
		
		for(int j = 0; j < m-1; j++)	// calles horizontales
		{
			it = z_random.begin();
			r = rand() % contador;
			advance(it,r);
			
			//~ 
		//~ 
			//~ /** OJO ACA **/
			//~ fprintf(pCiudad,"%i        ",*it);
//~ 

			
			// si la cant de zombies es muy grande, invalido la calle
			if(*it < 2*s){
				ciudad[i][j].derecha = *it;
				ciudad[i][j+1].izquierda = *it;
			}else{
				ciudad[i][j].derecha = -1;
				ciudad[i][j+1].izquierda = -1;
			}
			
			z_random.erase(it);
			contador--;
		}
		
		if(i != (n - 1))		// calles verticales
		{
			
			//~ 
			//~ /** OJO ACA **/
			//~ fprintf(pCiudad,"\n");
				//~ 
				
				
			for(int j = 0; j < m; j++)
			{
				it = z_random.begin();
				r = rand() % contador;
				advance(it,r);
				
				//~ 
				//~ /** OJO ACA **/
				//~ fprintf(pCiudad,"%i        ",*it);
				//~ 
				
			
				// si la cant de zombies es muy grande, invalido la calle
				if(*it < 2*s){
					ciudad[i][j].abajo = *it;
					ciudad[i+1][j].arriba = *it;
				}else{
					ciudad[i][j].abajo = -1;
					ciudad[i+1][j].arriba = -1;
				}
				
				z_random.erase(it);
				contador--;
			}
		}
	}
	
	//~ /** OJO ACA */
	//~ fclose(pCiudad);
	
	
	return ciudad;
}

Mapa generar_ciudad_facil(int n, int m, int s)
{
	Mapa ciudad = generar_ciudad(n,m,s);
	
	for(int j = 0; j < m-1; j++)	// calles horizontales
	{
		ciudad[0][j].izquierda = 0;
		ciudad[0][j+1].derecha = 0;
	}
	
	for(int i = 0; i < n-1; i++)	// calles verticales
	{
		ciudad[i][m-1].abajo = 0;
		ciudad[i+1][m-1].arriba = 0;
	}
	
	return ciudad;
}

Mapa generar_ciudad_zigzag(int n, int m, int s)
{
	int i;
	int j;
	int zombies;
	
	//Modifique esto!!(ALE)
	//if(s < n*m){ zombies = n*m; }
	//else{ zombies = s + 1; }
	zombies =s*2 -1;
	Mapa ciudad(n, Vect(m));
	
	// señalo las calles inválidas (bordes)
	for(i = 0; i < n; i++)
	{
		ciudad[i][0].izquierda = -1;
		ciudad[i][m-1].derecha = -1;
	}
	for(j = 0; j < m; j++)
	{
		ciudad[0][j].arriba = -1;
		ciudad[n-1][j].abajo = -1;
	}
	
	// valor por defecto para .parcial (para cada nodo)
	for(i = 0; i < n; i++){
		for(j = 0; j < m; j++){
			ciudad[i][j].parcial = 0;
		}
	}
	
	// Cant de zombies x calle
	//cout << zombies << endl;   //SACALO DESPUES
	for(i = 0; i < n; i++){
		if(i % 2 == 0){
			completar_derecha(ciudad,i,n,m,zombies,s);
		}
		else{
			completar_izquierda(ciudad,i,n,m,zombies,s);
		}
	}
	
	if(n % 2 == 1){
		ciudad[n-1][m-1].izquierda = zombies;	//para volver al anterior, cambiar 
		ciudad[n-1][m-2].derecha = zombies;		//zombies por 2*zombies - 1 (ALE)
	}else{
		ciudad[n-1][0].derecha = zombies;
		ciudad[n-1][1].izquierda = zombies;
	}
	//zombies no debeŕia existir, lo pongo para qe se parezca mas al anterior codigo(ALE)
	//cout << 2*zombies - 1 << endl;    //SACALO DEPUES
	if(s < n*m){ anular(ciudad,n,m,s); }
	
	return ciudad;
}

void completar_derecha(Mapa& ciudad, int i, int n, int m, int& zombies, int s)
{
	for(int j = 0; j < m-1; j++)	// calles horizontales
	{
		ciudad[i][j].derecha = 0;		//para volver al anterior, descomentar zombies--, y 
		ciudad[i][j+1].izquierda = 0;	//donde dice 0 poner zombies (ALE)
		//zombies--;
	//	cout << zombies << endl;   //SACALO DESPUES
	}
	
	if(i != (n - 1))		// calles verticales
	{	
		for(int j = 0; j < m-1; j++)
		{
			ciudad[i][j].abajo = 2*s - 1;
			ciudad[i+1][j].arriba = 2*s - 1;
		}
		
		ciudad[i][m-1].abajo = 0;		//aca tambien(ALE)
		ciudad[i+1][m-1].arriba = 0;
		//zombies--;
	//	cout << zombies << endl;   //SACALO DESPUES
	}

	return;
}

void completar_izquierda(Mapa& ciudad, int i, int n, int m, int& zombies, int s)
{
	for(int j = m-1; j > 0; j--)
	{
		ciudad[i][j].izquierda = 0;		//para volver al ant, lo mismo que derecha(ALE)
		ciudad[i][j-1].derecha = 0;
		//zombies--;
		cout << zombies << endl;   //SACALO DESPUES
	}
	
	if(i != (n - 1))
	{
		for(int j = 0; j < m; j++)
		{
			ciudad[i][j].abajo = 2*s - 1;
			ciudad[i+1][j].arriba = 2*s - 1;
		}
		
		ciudad[i][0].abajo = 0;
		ciudad[i+1][0].arriba = 0;
		//zombies--;
		cout << zombies << endl;   //SACALO DESPUES
	}
	return;
}

void restablecer(Mapa& ciudad, int n, int m, int s)
{
	// Adentro
	for(int i = 1; i < n - 1; i++)
	{
		for(int j = 1; j < m - 1; j++)
		{
			if(ciudad[i][j].arriba == -1){ ciudad[i][j].arriba = s; }
			if(ciudad[i][j].abajo == -1){ ciudad[i][j].abajo = s; }
			if(ciudad[i][j].izquierda == -1){ ciudad[i][j].izquierda = s; }
			if(ciudad[i][j].derecha == -1){ ciudad[i][j].derecha = s; }
		}
	}

	// Bordes arriba y abajo
	for(int j = 1; j < m - 1; j++)
	{
		if(ciudad[0][j].izquierda == -1){ ciudad[0][j].izquierda = s; }
		if(ciudad[0][j].derecha == -1){ ciudad[0][j].derecha = s; }
		if(ciudad[n-1][j].izquierda == -1){ ciudad[n-1][j].izquierda = s; }
		if(ciudad[n-1][j].derecha == -1){ ciudad[n-1][j].derecha = s; }
	}
	
	// Bordes izquierda y derecha
	for(int i = 1; i < n - 1; i++)
	{
		if(ciudad[i][0].izquierda == -1){ ciudad[i][0].izquierda = s; }
		if(ciudad[i][0].derecha == -1){ ciudad[i][0].derecha = s; }
		if(ciudad[i][m-1].izquierda == -1){ ciudad[i][m-1].izquierda = s; }
		if(ciudad[i][m-1].derecha == -1){ ciudad[i][m-1].derecha = s; }
	}
	
	// Esquinas
	if(ciudad[0][0].abajo == -1){ ciudad[0][0].abajo = s; }
	if(ciudad[0][0].derecha == -1){ ciudad[0][0].derecha = s; }
	if(ciudad[0][m-1].abajo == -1){ ciudad[0][m-1].abajo = s; }
	if(ciudad[0][m-1].izquierda == -1){ ciudad[0][m-1].izquierda = s; }
	if(ciudad[n-1][0].arriba == -1){ ciudad[n-1][0].arriba = s; }
	if(ciudad[n-1][0].derecha == -1){ ciudad[n-1][0].derecha = s; }
	if(ciudad[n-1][m-1].arriba == -1){ ciudad[n-1][m-1].arriba = s; }
	if(ciudad[n-1][m-1].izquierda == -1){ ciudad[n-1][m-1].izquierda = s; }

}

void anular(Mapa& ciudad, int n, int m, int s)
{
	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(ciudad[i][j].arriba > s + 1){ ciudad[i][j].arriba = 0; }
			if(ciudad[i][j].abajo > s + 1){ ciudad[i][j].abajo = 0; }
			if(ciudad[i][j].izquierda > s + 1){ ciudad[i][j].izquierda = 0; }
			if(ciudad[i][j].derecha > s + 1){ ciudad[i][j].derecha = 0; }
		}
	}
}

void testear_2_A()	// EXTIENDO N
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2A.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	double tmax = 0;	
	
	bool marca = false;
	int n = 60;
	int m = 10;
	int s = 610;
	
	pos inicio = (pos){
			.horizontal = 0,
			.vertical = 0,
		};
		
	pos bunker;
		
	Mapa ciudad;
	
	for(int tam = n; tam >= 10 ; tam--)
	{
		tmax = 0;
		
		bunker = (pos){
			.horizontal = tam - 1,
			.vertical = 9,
		};
		
		for(int a = 0; a < 10; a++)
		{
			t = 0;
			ciudad = generar_ciudad(tam,m,s);
			ciudad[0][0].parcial = s;
			
			for(int h = 0; h < 20; h++)
			{	cout << tam << " " << a << " " << h << endl;
				int soldados = s;
				Mapa ciudad_aux (tam, Vect(m));
				for(int i = 0; i < tam; i++)
				{
					for(int j = 0; j < m; j++){
						ciudad_aux[i][j] = ciudad[i][j];
					}
				}
				// señalo las calles inválidas (bordes)
				//~ for(int j = 0; j < m; j++){
					//~ ciudad[tam-1][j].abajo = -1;
				//~ }
				pair<pos,int> primero = make_pair(inicio,soldados);
				list<pair <pos,int> > cola;
				list<pos> salida;
				cola.push_back(primero);
				
				start = clock();
				zombieland(ciudad_aux,cola,soldados,bunker);
				armo_resultado(ciudad_aux,salida,inicio,bunker);
				end = clock();
				t = t + difftime(end,start);
				
				cola.clear();
				salida.clear();
			}
			
			t = t/20;
			if(t > tmax){ tmax = t; }
		}
		
		t = 0;
		ciudad = generar_ciudad_zigzag(tam,m,s);
		ciudad[0][0].parcial = s;
		
		for(int h = 0; h < 20; h++)
		{	cout << tam << " zigzag " << h << endl;
			int soldados = s;
			Mapa ciudad_aux (tam, Vect(m));
			for(int i = 0; i < tam; i++)
			{
				for(int j = 0; j < m; j++){
					ciudad_aux[i][j] = ciudad[i][j];
				}
			}
			//~ // señalo las calles inválidas (bordes)
			//~ for(int j = 0; j < m; j++){
				//~ ciudad[tam-1][j].abajo = -1;
			//~ }
			pair<pos,int> primero = make_pair(inicio,soldados);
			list<pair <pos,int> > cola;
			list<pos> salida;
			cola.push_back(primero);
			
			start = clock();
			zombieland(ciudad_aux,cola,soldados,bunker);
			armo_resultado(ciudad_aux,salida,inicio,bunker);
			end = clock();
			t = t + difftime(end,start);
			
			cola.clear();
			salida.clear();
		}
			
		fprintf(pTest,"%i, %f, %f \n",tam,t/20,tmax);
	}
	
	fclose(pTest);
}
 
void testear_2_B()	// EXTIENDO M
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2B.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	double tmax = 0;	
	
	int n = 10;
	int m = 60;
	int s = 610;
	
	pos inicio = (pos){
			.horizontal = 0,
			.vertical = 0,
		};
		
	pos bunker;
		
	Mapa ciudad;
	
	for(int tam = m; tam >= 10 ; tam--)
	{
		tmax = 0;
		
		bunker = (pos){
			.horizontal = 9,
			.vertical = tam - 1,
		};
		
		for(int a = 0; a < 10; a++)
		{
			t = 0;
			ciudad = generar_ciudad(n,tam,s);
			ciudad[0][0].parcial = s;

			for(int h = 0; h < 20; h++)
			{	cout << tam << " " << a << " " << h << endl;
				int soldados = s;
				Mapa ciudad_aux (n, Vect(tam));
				for(int i = 0; i < n; i++)
				{
					for(int j = 0; j < tam; j++){
						ciudad_aux[i][j] = ciudad[i][j];
					}
				}
				// señalo las calles inválidas (bordes)
				//~ for(int i = 0; i < n; i++){
					//~ ciudad[i][tam-1].derecha = -1;
				//~ }
				pair<pos,int> primero = make_pair(inicio,soldados);
				list<pair <pos,int> > cola;
				list<pos> salida;
				cola.push_back(primero);
				
				start = clock();
				zombieland(ciudad_aux,cola,soldados,bunker);
				armo_resultado(ciudad_aux,salida,inicio,bunker);
				end = clock();
				t = t + difftime(end,start);
				
				cola.clear();
				salida.clear();
			}
			
			t = t/20;
			if(t > tmax){ tmax = t; }
		}
		
		t = 0;
		ciudad = generar_ciudad_zigzag(n,tam,s);
		ciudad[0][0].parcial = s;
		
		for(int h = 0; h < 20; h++)
		{	cout << tam << " zigzag " << h << endl;
			int soldados = s;
			Mapa ciudad_aux (n, Vect(tam));
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < tam; j++){
					ciudad_aux[i][j] = ciudad[i][j];
				}
			}
			// señalo las calles inválidas (bordes)
			//~ for(int j = 0; j < m; j++){
				//~ ciudad[tam-1][j].abajo = -1;
			//~ }
			pair<pos,int> primero = make_pair(inicio,soldados);
			list<pair <pos,int> > cola;
			list<pos> salida;
			cola.push_back(primero);
			
			start = clock();
			zombieland(ciudad_aux,cola,soldados,bunker);
			armo_resultado(ciudad_aux,salida,inicio,bunker);
			end = clock();
			t = t + difftime(end,start);
			
			cola.clear();
			salida.clear();
		}
		
		fprintf(pTest,"%i, %f, %f \n",tam,t/20,tmax);
	}
	
	fclose(pTest);
}

void testear_2_C()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2C.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	double tmax = 0;	
	
	int n = 5;
	int m = 5;
	int s = 100;
	
	pos inicio = (pos){
			.horizontal = 0,
			.vertical = 0,
		};
		
	pos bunker = (pos){
			.horizontal = 4,
			.vertical = 4,
		};
		
	Mapa ciudad;
	
	for(int soldados = s; soldados > 99; soldados--)
	{
		tmax = 0;	
		
		for(int a = 0; a < 1; a++)
		{
			t = 0;
			ciudad = generar_ciudad(n,m,s);
			ciudad[0][0].parcial = s;


			//borrar esto despues, esto imprime por pantalla la ciudad
			for(int i = 0; i < n; i++){
				for(int h = 0; h < m; h++){
					cout << ciudad[i][h].derecha << "  " ;

					}	
				cout << endl;
				for(int j = 0; j < m; j++){
					
					cout << ciudad[i][j].abajo << "  " ;
				}
				cout << endl;
			}



			for(int h = 0; h < 20; h++)
			{	
				cout << soldados << " " << a << " " << h << endl;
				int soldados = s;
				Mapa ciudad_aux (n, Vect(m));
				for(int i = 0; i < n; i++)
				{
					for(int j = 0; j < m; j++){
						ciudad_aux[i][j] = ciudad[i][j];
					}
				}
				
				pair<pos,int> primero = make_pair(inicio,soldados);
				list<pair <pos,int> > cola;
				list<pos> salida;
				cola.push_back(primero);
				
				start = clock();
				zombieland(ciudad_aux,cola,soldados,bunker);
				armo_resultado(ciudad_aux,salida,inicio,bunker);
				end = clock();
				t = t + difftime(end,start);
				
				cola.clear();
				salida.clear();
			}
			
			t = t/20;
			if(t > tmax){ tmax = t; }
		}
		
		t = 0;
		ciudad = generar_ciudad_zigzag(n,m,s);
		ciudad[0][0].parcial = s;

		//borrar esto despues, esto imprime por pantalla la ciudad
			for(int i = 0; i < n; i++){
				for(int h = 0; h < m; h++){
					cout << ciudad[i][h].derecha << "  " ;

					}	
				cout << endl;
				for(int j = 0; j < m; j++){
					
					cout << ciudad[i][j].abajo << "  " ;
				}
				cout << endl;
			}

		
		for(int h = 0; h < 20; h++)
		{	cout << soldados << " zigzag " << h << endl;
			int soldados = s;
			Mapa ciudad_aux (n, Vect(m));
			for(int i = 0; i < n; i++)
			{
				for(int j = 0; j < m; j++){
					ciudad_aux[i][j] = ciudad[i][j];
				}
			}
			
			pair<pos,int> primero = make_pair(inicio,soldados);
			list<pair <pos,int> > cola;
			list<pos> salida;
			cola.push_back(primero);
			
			start = clock();
			zombieland(ciudad_aux,cola,soldados,bunker);
			armo_resultado(ciudad_aux,salida,inicio,bunker);
			end = clock();
			t = t + difftime(end,start);
			
			cola.clear();
			salida.clear();
		}
		
		fprintf(pTest,"%i, %f, %f \n",soldados,t/20,tmax);	
	}
	
	fclose(pTest);
}

/************************* TESTS QUE FALLARON *************************/

//~ void testear_2_A()	// EXTIENDO N
//~ {
	//~ FILE * pTest = fopen("../Resultados_tests_nuestros/testing2A.txt","w");
	//~ clock_t start;
	//~ clock_t end;
	//~ double t = 0;	
	//~ 
	//~ bool marca = false;
	//~ int n = 300;
	//~ int m = 30;
	//~ int s = 50;
	//~ 
	//~ pos inicio = (pos){
			//~ .horizontal = 0,
			//~ .vertical = 0,
		//~ };
		//~ 
	//~ pos bunker = (pos){
			//~ .horizontal = 29,
			//~ .vertical = 29,
		//~ };
		//~ 
	//~ Mapa ciudad = generar_ciudad(n,m,s);
	//~ 
	//~ for(int tam = n; tam >= 30 ; tam = tam - 5)
	//~ {
		//~ t = 0;
//~ 
		//~ for(int h = 0; h < 20; h++)
		//~ {
			//~ int soldados = s;
			//~ Mapa ciudad_aux (tam, Vect(m));
			//~ for(int i = 0; i < tam; i++)
			//~ {
				//~ for(int j = 0; j < m; j++){
					//~ ciudad_aux[i][j] = ciudad[i][j];
				//~ }
			//~ }
			//~ // señalo las calles inválidas (bordes)
			//~ for(int j = 0; j < m; j++){
				//~ ciudad[tam-1][j].abajo = -1;
			//~ }
			//~ pair<pos,int> primero = make_pair(inicio,soldados);
			//~ list<pair <pos,int> > cola;
			//~ list<pos> salida;
			//~ cola.push_back(primero);
			//~ 
			//~ start = clock();
			//~ zombieland(ciudad_aux,cola,soldados,bunker);
			//~ armo_resultado(ciudad_aux,salida,inicio,bunker);
			//~ end = clock();
			//~ t = t + difftime(end,start);
			//~ 
			//~ cola.clear();
			//~ salida.clear();
		//~ }
		//~ fprintf(pTest,"%i, %f \n",tam,t/20);
	//~ }
	//~ 
	//~ fclose(pTest);
//~ }
	//~ 
//~ void testear_2_B()	// EXTIENDO M
//~ {
	//~ FILE * pTest = fopen("../Resultados_tests_nuestros/testing2B.txt","w");
	//~ clock_t start;
	//~ clock_t end;
	//~ double t = 0;	
	//~ 
	//~ int n = 30;
	//~ int m = 300;
	//~ int s = 50;
	//~ 
	//~ pos inicio = (pos){
			//~ .horizontal = 0,
			//~ .vertical = 0,
		//~ };
		//~ 
	//~ pos bunker = (pos){
			//~ .horizontal = 29,
			//~ .vertical = 29,
		//~ };
		//~ 
	//~ Mapa ciudad = generar_ciudad(n,m,s);
	//~ 
	//~ for(int tam = m; tam >= 30 ; tam = tam - 5)
	//~ {
		//~ t = 0;
//~ 
		//~ for(int h = 0; h < 20; h++)
		//~ {
			//~ int soldados = s;
			//~ Mapa ciudad_aux (n, Vect(tam));
			//~ for(int i = 0; i < n; i++)
			//~ {
				//~ for(int j = 0; j < tam; j++){
					//~ ciudad_aux[i][j] = ciudad[i][j];
				//~ }
			//~ }
			//~ // señalo las calles inválidas (bordes)
			//~ for(int i = 0; i < n; i++){
				//~ ciudad[i][tam-1].derecha = -1;
			//~ }
			//~ pair<pos,int> primero = make_pair(inicio,soldados);
			//~ list<pair <pos,int> > cola;
			//~ list<pos> salida;
			//~ cola.push_back(primero);
			//~ 
			//~ start = clock();
			//~ zombieland(ciudad_aux,cola,soldados,bunker);
			//~ armo_resultado(ciudad_aux,salida,inicio,bunker);
			//~ end = clock();
			//~ t = t + difftime(end,start);
			//~ 
			//~ cola.clear();
			//~ salida.clear();
		//~ }
		//~ fprintf(pTest,"%i, %f \n",tam,t/20);
	//~ }
	//~ 
	//~ fclose(pTest);
//~ }
//~ 
//~ void testear_2_C()
//~ {
	//~ FILE * pTest = fopen("../Resultados_tests_nuestros/testing2C.txt","w");
	//~ clock_t start;
	//~ clock_t end;
	//~ double t = 0;	
	//~ 
	//~ int n = 30;
	//~ int m = 30;
	//~ int s = 25;
	//~ 
	//~ pos inicio = (pos){
			//~ .horizontal = 0,
			//~ .vertical = 0,
		//~ };
		//~ 
	//~ pos bunker = (pos){
			//~ .horizontal = 29,
			//~ .vertical = 29,
		//~ };
		//~ 
	//~ Mapa ciudad = generar_ciudad(n,m,s);
	//~ 
	//~ restablecer(ciudad,n,m,2*s);
	//~ 
	//~ for(int soldados = 75; soldados > 0; soldados--)
	//~ {
		//~ t = 0;
		//~ 
		//~ if(soldados <= 25){
			//~ anular(ciudad,n,m,2*soldados);
		//~ }
		//~ 
		//~ for(int h = 0; h < 20; h++)
		//~ {
			//~ int sold_aux = soldados;
			//~ Mapa ciudad_aux = ciudad;
			//~ pair<pos,int> primero = make_pair(inicio,s);
			//~ list<pair <pos,int> > cola;
			//~ list<pos> salida;
			//~ cola.push_back(primero);
			//~ 
			//~ start = clock();
			//~ zombieland(ciudad_aux,cola,sold_aux,bunker);
			//~ armo_resultado(ciudad_aux,salida,inicio,bunker);
			//~ end = clock();
			//~ t = t + difftime(end,start);
			//~ 
			//~ cola.clear();
			//~ salida.clear();
		//~ }
		//~ fprintf(pTest,"%i, %f \n",soldados,t/20);
	//~ }
	//~ 
	//~ fclose(pTest);
//~ }
		
#endif // TESTING2_H_INCLUDED

