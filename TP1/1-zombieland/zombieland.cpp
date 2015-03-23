#include "zombieland.h"

//funcion que recorre archivo y lo mete en una lista los hace del tipo ciudad,...
//mete todo donde corresponde... en principio la lista viene ordenada como
//se tomo del archivo y eso es lo que se pone en los punteros. tambien modifica pn y los pone del archivo

lista_t informacion_en_lista (archivo a,int n, int p){



}


//funcion que calcula los costos para salvar cada ciudad, y los pone en su tipo
// los costos por salvar cada ciudad, viene por zombies-(soldados x 10)= r
// luego r/10 aproximada siempre para arriba(o sea, 10.2=11) y luego eso x c
//el resultado debe ir en costfsafety

void calcular_costo_de_salvacion (lista *l, int n){

    ciudad_t *c= (l->primero);
    int s;
    for (i=0, i<n, i++){

        s= (c->zombies) - 10*(c->soldados)
        s= (s/10) * (c->costfsoldier)               //hay que hacer que s/10 devuelve el numero redondeado siempre hacia arriba
        (c->costfsafety) = s
        c = (c->sig)

    }

}

//funcion que ordena de menor a mayor segun su costfsafety  (heapsort, o mergesort... por ahi
//merge es mas tranqui... por ahiiii)

void    funcionqueordena(lista_t *l,int n){




}


//funcion que aglomera todo lo arriba escrito y luego va tomando los primeros g
//elementos de manera tal que la suma de costfsafety de esos g elementos son
// menores que el Presupuesto pero si tomo el proximo elemento, y le sumo su
//costfsafety ya es mayor, siendo esta mi respuesta.
//Esta funcion debe devolver mi formato de salida.

void heroe_tactico_del_pais(archivo a){

    int n= 0;
    int p= 0;
    lista_t *l=informacion_en_lista(a,n,p);
    calcular_costo_de_salvacion(l,n);
    funcionqueordena(l,n);

}
