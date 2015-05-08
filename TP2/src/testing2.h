#ifndef TESTING2_H_INCLUDED
#define TESTING2_H_INCLUDED

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "zombieland.h"

using namespace std;


/********************** DECLARACIÓN DE FUNCIONES **********************/

Mapa generar_ciudad(int n, int m, int s);
Mapa generar_ciudad_facil(int n, int m, int s);
Mapa generar_ciudad_zigzag(int n, int m, int s);
void completar_derecha(Mapa& ciudad, int i, int n, int m, int& zombies);
void completar_izquierda(Mapa& ciudad, int i, int m, int& zombies);
void inhabilitar_esquina(Mapa& ciudad, int i, int j);
void restablecer(Mapa& ciudad, int n, int m, int s);
void testear_2_A();
void testear_2_B();
void testear_2_C(Mapa ciudad, pos inicio, pos bunker, int n, int m, int s, double tiempo);
void testear_2_D(Mapa ciudad, pos inicio, pos bunker, int n, int m, int s, double tiempo);


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

Mapa generar_ciudad(int n, int m, int s)
{
	int i;
	int j;
	int zombies;
	int tope;
	int cont = 0;
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
	for(i = 0; i < n; i++)
	{
		tope = 2*s + 1;
		cont = 0;
		
		for(j = 0; j < m-1; j++)	// calles horizontales
		{
			if(cont == m/8){ tope = s; }
			
			zombies = rand() % tope;
			
			// si la cant de zombies es muy grande, invalido la calle
			if(zombies < 2*s){
				ciudad[i][j].derecha = zombies;
				ciudad[i][j+1].izquierda = zombies;
				if(zombies > s){ cont++; }
			}else{
				ciudad[i][j].derecha = -1;
				ciudad[i][j+1].izquierda = -1;
				tope--;
			}
		}
		
		if(i != (n - 1))		// calles verticales
		{
			for(j = 0; j < m; j++)
			{
				if(cont == m/8){ tope = s; }
			
				zombies = rand() % tope;
				
				// si la cant de zombies es muy grande, invalido la calle
				if(zombies < 2*s){
					ciudad[i][j].abajo = zombies;
					ciudad[i+1][j].arriba = zombies;
					if(zombies > s){ cont++; }
				}else{
					ciudad[i][j].abajo = -1;
					ciudad[i+1][j].arriba = -1;
					tope--;
				}
			}
		}
	}
	
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
	int zombies = s + 1;
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
	for(i = 0; i < n; i++)
	{
		if(i % 2 == 0){
			completar_derecha(ciudad,i,n,m,zombies);
		}
		else{
			completar_izquierda(ciudad,i,m,zombies);
		}
	}
	
	return ciudad;
}

void completar_derecha(Mapa& ciudad, int i, int n, int m, int& zombies)
{
	for(int j = 0; j < m-1; j++)	// calles horizontales
	{
		ciudad[i][j].derecha = zombies;
		ciudad[i][j+1].izquierda = zombies;
		zombies--;
	}
	
	if(i != (n - 1))		// calles verticales
	{	
		for(int j = 0; j < m-1; j++)
		{
			ciudad[i][j].abajo = -1;
			ciudad[i+1][j].arriba = -1;
		}
		
		ciudad[i][m-1].abajo = zombies;
		ciudad[i+1][m-1].arriba = zombies;
		zombies--;
	}
	
	return;
}

void completar_izquierda(Mapa& ciudad, int i, int m, int& zombies)
{
	for(int j = m-1; j > 0; j--)
	{
		ciudad[i][j].izquierda = zombies;
		ciudad[i][j].abajo = -1;
		ciudad[i][j-1].derecha = zombies;
		ciudad[i+1][j].arriba = -1;
		zombies--;
	}
	
	ciudad[i][0].abajo = zombies;
	ciudad[i+1][0].arriba = zombies;
	zombies--;
	
	return;
}

void inhabilitar_esquina(Mapa& ciudad, int i, int j)
{
	ciudad[i][j].arriba = -1;
	ciudad[i-1][j].abajo = -1;
	ciudad[i][j].abajo = -1;
	ciudad[i+1][j].arriba = -1;
	ciudad[i][j].izquierda = -1;
	ciudad[i][j-1].derecha = -1;
	ciudad[i][j].derecha = -1;
	ciudad[i][j+1].izquierda = -1;
	
	return;
}

void restablecer(Mapa& ciudad, int n, int m, int s)
{
	for(int i = 1; i < n - 1; i++)
	{
		for(int j = 0; j < m; j++)
		{
			if(ciudad[i][j].arriba == -1){ ciudad[i][j].arriba = s; }
			if(ciudad[i][j].abajo == -1){ ciudad[i][j].abajo = s; }
			if(ciudad[i][j].izquierda == -1){ ciudad[i][j].izquierda = s; }
			if(ciudad[i][j].derecha == -1){ ciudad[i][j].derecha = s; }
		}
	}

	for(int j = 1; j < m - 1; j++)
	{
		if(ciudad[0][j].izquierda == -1){ ciudad[0][j].izquierda = s; }
		if(ciudad[0][j].derecha == -1){ ciudad[0][j].derecha = s; }
		if(ciudad[n-1][j].izquierda == -1){ ciudad[n-1][j].izquierda = s; }
		if(ciudad[n-1][j].derecha == -1){ ciudad[n-1][j].derecha = s; }
	}
	
	if(ciudad[0][0].abajo == -1){ ciudad[0][0].abajo = s; }
	if(ciudad[0][0].derecha == -1){ ciudad[0][0].derecha = s; }
	if(ciudad[0][m-1].abajo == -1){ ciudad[0][m-1].abajo = s; }
	if(ciudad[0][m-1].izquierda == -1){ ciudad[0][m-1].izquierda = s; }
	if(ciudad[n-1][0].arriba == -1){ ciudad[n-1][0].arriba = s; }
	if(ciudad[n-1][0].derecha == -1){ ciudad[n-1][0].derecha = s; }
	if(ciudad[n-1][m-1].arriba == -1){ ciudad[n-1][m-1].arriba = s; }
	if(ciudad[n-1][m-1].izquierda == -1){ ciudad[n-1][m-1].izquierda = s; }

}


void testear_2_A()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2A.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	bool marca = false;
	int unica = 0;
	int n = 30;
	int m = 30;
	int s = 900;
	
	pos inicio = (pos){
			.horizontal = 0,
			.vertical = 0,
		};
		
	pos bunker = (pos){
			.horizontal = n,
			.vertical = m,
		};
		
	pair<pos,int> primero = make_pair(inicio,s);
	
	for(int i = 0; i < 30; i++)
	{
		t = 0;
		Mapa ciudad = generar_ciudad(n,m,s);
		
		for(int j = 0; j < 20; j++)
		{
			int soldados = s;
			Mapa ciudad_aux = ciudad;
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
			if(soldados != 0){ marca = true; }
			else{ marca = false; }
		}
		fprintf(pTest,"%f \n",t/20);
		
		if(marca)
		{
			testear_2_D(ciudad,inicio,bunker,n,m,s,t/20);
			
			if(unica == 0){
				testear_2_C(ciudad,inicio,bunker,n,m,s,t/20);
				unica++;
			}
		}
	}
	
	Mapa ciudad1 = generar_ciudad_facil(n,m,s);
	Mapa ciudad2 = generar_ciudad_zigzag(n,m,s);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		int soldados = s;
		Mapa ciudad_aux = ciudad1;
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
	fprintf(pTest,"%f \n",t/20);
	testear_2_D(ciudad1,inicio,bunker,n,m,s,t/20);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		int soldados = s;
		Mapa ciudad_aux = ciudad2;
		list<pair <pos,int> > cola;
		cola.push_back(primero);
		list<pos> salida;
		
		start = clock();
		zombieland(ciudad_aux,cola,soldados,bunker);
		armo_resultado(ciudad_aux,salida,inicio,bunker);
		end = clock();
		t = t + difftime(end,start);
		
		cola.clear();
		salida.clear();
	}
	fprintf(pTest,"%f \n",t/20);
	testear_2_D(ciudad2,inicio,bunker,n,m,s,t/20);
	
	fclose(pTest);
}

void testear_2_B()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2B.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	int n = 30;
	int m = 30;
	int s = 900;
	int tam = n;
	int it = 0;
	
	Mapa ciudad = generar_ciudad(n,m,s);
	
	pos inicio = (pos){
			.horizontal = 12,
			.vertical = 12,
		};
		
	pos bunker = (pos){
			.horizontal = 17,
			.vertical = 17,
		};
		
	for(int tam = n; tam >= 6; tam = tam - 2)
	{
		t = 0;
		
		for(int h = 0; h < 20; h++)
		{
			int soldados = s;
			Mapa ciudad_aux (tam, Vect(tam));
			for(int i = 0; i < tam; i++)
			{
				for(int j = 0; j < tam; j++){
					ciudad_aux[i][j] = ciudad[i+it][j+it];
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
		fprintf(pTest,"%i, %i, %f \n",tam,tam,t/20);
		
		inicio.horizontal--;
		inicio.vertical--;
		bunker.horizontal--;
		bunker.vertical--;
		it++;
	}
	
	fclose(pTest);
}

void testear_2_C(Mapa ciudad, pos inicio, pos bunker, int n, int m, int s, double tiempo)
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2C.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	fprintf(pTest,"%i, %f \n",s,tiempo);
	
	restablecer(ciudad,n,m,2*s);
	
	for(int soldados = s + 10; soldados <= 2*s; soldados = soldados + 10)
	{
		t = 0;
		for(int h = 0; h < 20; h++)
		{
			int sold_aux = soldados;
			Mapa ciudad_aux = ciudad;
			pair<pos,int> primero = make_pair(inicio,s);
			list<pair <pos,int> > cola;
			list<pos> salida;
			cola.push_back(primero);
			
			start = clock();
			zombieland(ciudad_aux,cola,sold_aux,bunker);
			armo_resultado(ciudad_aux,salida,inicio,bunker);
			end = clock();
			t = t + difftime(end,start);
			
			cola.clear();
			salida.clear();
		}
		fprintf(pTest,"%i, %f \n",soldados,t/20);
	}
	
	fclose(pTest);
}

void testear_2_D(Mapa ciudad, pos inicio, pos bunker, int n, int m, int s, double tiempo)
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing2D.txt","a");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	int g;
	int h;
	int v;
	
	pair<pos,int> primero = make_pair(inicio,s);
	
	Mapa ciudad_s_bunker = ciudad;
	Mapa ciudad_s_inicio = ciudad;
	Mapa ciudad_s_medio = ciudad;
	
	h = bunker.horizontal;
	v = bunker.vertical;
	inhabilitar_esquina(ciudad_s_bunker,h,v);
	
	h = inicio.horizontal;
	v = inicio.vertical;
	inhabilitar_esquina(ciudad_s_inicio,h,v);
	
	g = n/2;
	
	for(int j = 0; j < m; j++){
		ciudad_s_medio[g][j].arriba = -1;
		ciudad_s_medio[g-1][j].abajo = -1;
		ciudad_s_medio[g][j].abajo = -1;
		ciudad_s_medio[g+1][j].arriba = -1;
	}
	
	fprintf(pTest,"%f ",tiempo);
	
	for(int i = 0; i < 20; i++)
	{
		int soldados = s;
		Mapa ciudad_aux = ciudad_s_bunker;
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
	fprintf(pTest,"%f ",t/20);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		int soldados = s;
		Mapa ciudad_aux = ciudad_s_inicio;
		list<pair <pos,int> > cola;
		cola.push_back(primero);
		list<pos> salida;
		
		start = clock();
		zombieland(ciudad_aux,cola,soldados,bunker);
		armo_resultado(ciudad_aux,salida,inicio,bunker);
		end = clock();
		t = t + difftime(end,start);
		
		cola.clear();
		salida.clear();
	}
	fprintf(pTest,"%f ",t/20);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		int soldados = s;
		Mapa ciudad_aux = ciudad_s_medio;
		list<pair <pos,int> > cola;
		cola.push_back(primero);
		list<pos> salida;
		
		start = clock();
		zombieland(ciudad_aux,cola,soldados,bunker);
		armo_resultado(ciudad_aux,salida,inicio,bunker);
		end = clock();
		t = t + difftime(end,start);
		
		cola.clear();
		salida.clear();
	}
	fprintf(pTest,"%f \n",t/20);
	
	fclose(pTest);
}
		
#endif // TESTING2_H_INCLUDED

