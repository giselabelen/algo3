#ifndef CABALLOS_H_INCLUDED
#define CABALLOS_H_INCLUDED

#include <vector>

using namespace std;

typedef vector<char> Vec;
typedef vector<Vec> Tablero;

void setear_amenaza(Tablero& tab, int fila, int columna, int n);

#endif // CABALLOS_H_INCLUDED
