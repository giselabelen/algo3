#!/bin/bash

RES=../Resultados_experimentos
RES1=exacto
RES2=goloso
RES3=busqlocal
RES4=grasp

echo "Borrando carpeta "$RES

rm -r $RES
mkdir $RES
mkdir $RES/$RES1
mkdir $RES/$RES2
mkdir $RES/$RES3

echo "Compilando"

g++ exp.cpp -g -o exp

echo "Corriendo Tests"

./exp
