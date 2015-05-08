#ifndef TESTING1_H_INCLUDED
#define TESTING1_H_INCLUDED
//~ #include <iostream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include "dakkar.h"

using namespace std;


/********************** DECLARACIÓN DE FUNCIONES **********************/

int* generar_etapas(int n);
int* generar_etapas_especial(int n);
void testear_1_A();
void testear_1_B();
void testear_1_C();


/******************** IMPLEMENTACIÓN DE FUNCIONES ********************/

int* generar_etapas(int n)
{
	int etapas[n];
	
	for(int i = 0; i < n; i++){
		etapas[i] = (2 + rand() % 50);
	}
	
	return etapas;
}

int* generar_etapas_especial(int n)
{
	int etapas[n];
	
	for(int i = 0; i < n; i++){
		etapas[i] = 1;
	}
	
	return etapas;
}

void testear_1_A()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing1A.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	int km = 100;
	int kb = 100;
	
	int* total_bici = generar_etapas(200);
	int* total_moto = generar_etapas(200);
	int* total_buggy = generar_etapas(200);
	
	for(int n = 50; n <= 200; n = n + 10)
	{	
		t = 0;
		int bici[n];
		int moto[n];
		int buggy[n];
		
		for(int j = 0; j < n; j++)
		{
			bici[j] = total_bici[j];
			moto[j] = total_moto[j];
			buggy[j] = total_buggy[j];
		}	
		//~ cout << "copie todo \n";
		for(int i = 0; i < 20; i++)
		{
			list<int> salida;
			
			start = clock();
			Carrera etapas = dakkar(n,km,kb,bici,moto,buggy);
			armo_salida(etapas,km,kb,n,salida);
			end = clock();
			t = t + difftime(end,start);
			
			salida.clear();
		}
		
		fprintf(pTest,"%i, %f \n",n,t/20);
	}

	fclose(pTest);
}

void testear_1_B()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing1B.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	int n = 100;
	
	int* bici = generar_etapas(n);
	int* moto = generar_etapas(n);
	int* buggy = generar_etapas(n);

	for(int km = 20; km <= 140; km = km + 10)
	{
		for(int kb = 20; kb <= 140; km = km + 10)
		{
			t = 0;
			for(int i = 0; i < 20; i++)
			{
				list<int> salida;
				
				start = clock();
				Carrera etapas = dakkar(n,km,kb,bici,moto,buggy);
				armo_salida(etapas,km,kb,n,salida);
				end = clock();
				t = t + difftime(end,start);
				
				salida.clear();
			}
			
			fprintf(pTest,"%i, %i, %f \n",km,kb,t/20);
		}
	}

	fclose(pTest);
}

void testear_1_C()
{
	FILE * pTest = fopen("../Resultados_tests_nuestros/testing1C.txt","w");
	clock_t start;
	clock_t end;
	double t = 0;	
	
	int n = 100;
	int km = 30;
	int kb = 40;
	
	for(int j = 0; j < n; j++)
	{
		int* bici = generar_etapas(n);
		int* moto = generar_etapas(n);
		int* buggy = generar_etapas(n);
		
		t = 0;
		for(int i = 0; i < 20; i++)
		{
			list<int> salida;
			
			start = clock();
			Carrera etapas = dakkar(n,km,kb,bici,moto,buggy);
			armo_salida(etapas,km,kb,n,salida);
			end = clock();
			t = t + difftime(end,start);
			
			salida.clear();
		}
		fprintf(pTest,"%f \n",t/20);
	}

	int* bici = generar_etapas(n);
	int* moto = generar_etapas(n);
	int* buggy = generar_etapas(n);
	int* bici_especial = generar_etapas_especial(n);
	int* moto_especial = generar_etapas_especial(n);
	int* buggy_especial = generar_etapas_especial(n);
	
	t = 0;	
	for(int i = 0; i < 20; i++)
	{
		list<int> salida;
		
		start = clock();
		Carrera etapas = dakkar(n,km,kb,bici_especial,moto,buggy);
		armo_salida(etapas,km,kb,n,salida);
		end = clock();
		t = t + difftime(end,start);
		
		salida.clear();
	}
	fprintf(pTest,"%f \n",t/20);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		list<int> salida;
		
		start = clock();
		Carrera etapas = dakkar(n,100,kb,bici,moto_especial,buggy);
		armo_salida(etapas,100,kb,n,salida);
		end = clock();
		t = t + difftime(end,start);
		
		salida.clear();
	}
	fprintf(pTest,"%f \n",t/20);
	
	t = 0;
	for(int i = 0; i < 20; i++)
	{
		list<int> salida;
		
		start = clock();
		Carrera etapas = dakkar(n,km,100,bici,moto,buggy_especial);
		armo_salida(etapas,km,100,n,salida);
		end = clock();
		t = t + difftime(end,start);
		
		salida.clear();
	}
	fprintf(pTest,"%f \n",t/20);

	fclose(pTest);
}


#endif // TESTING1_H_INCLUDED

