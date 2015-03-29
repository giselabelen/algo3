#ifndef ALTAFRECUENCIA_H_INCLUDED
#define ALTAFRECUENCIA_H_INCLUDED

typedef struct frecuencia_t
{
	int nombre; // numero que identifica la frecuencia segun el orden en el que viene dada
	int costfminute;  // costo de uso por minuto
    int inicio;	// minuto inicio de transmisión
    int fin;	// minuto fin de transmisión
    
    //~ int cant_zombies;
    //~ int cant_soldados;
    //~ int soldier_req;  // numero de soldados que faltan para salvar la ciudad
    //~ int costfsafety;  // costo de salvar esa ciudad
    //~ bool salvar;	// 1 para salvarla, 0 para no salvarla
} frecuencia;

typedef struct transmision_t
{
	frecuencia freq; // frecuencia que estoy transmitiendo
	int inicio;	// inicio de transmisión
    int fin;	// fin de transmisión
} transmision;

#endif // ALTAFRECUENCIA_H_INCLUDED
