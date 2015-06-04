#ifndef CABALLOS_H_INCLUDED
#define CABALLOS_H_INCLUDED

#include <vector>

using namespace std;

typedef vector<char> Vec;
typedef vector<Vec> Tablero;

void setear_amenaza(Tablero& tab, int fila, int columna, int n, int& dec);
void backtranki(Tablero& tab, int fila, int columna, int n, int& cota, int lo_que_falta,int extras);
void copiar_tablero(Tablero& tab, Tablero& copia, int n);

#endif // CABALLOS_H_INCLUDED
