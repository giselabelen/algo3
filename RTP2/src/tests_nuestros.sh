#!/bin/bash

RES=../Resultados_tests_nuestros

echo "Borrando carpeta "$RES

rm -r $RES
mkdir $RES

echo "Compilando"

./compilar.sh
g++ testing.cpp -g -o testing

echo "Corriendo Tests"

./testing
