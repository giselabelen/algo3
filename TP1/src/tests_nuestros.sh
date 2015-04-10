#!/bin/bash

DIR=../tests_caballos

RES=../Resultados_tests_nuestros

echo "Borrando carpeta "$RES

rm -r $RES
mkdir $RES

echo "Compilando"

./compilar.sh
g++ testing.cpp -g -o testing

echo "Corriendo Tests Zombieland/Alta Frecuencia"

./testing

echo "Corriendo Tests Caballos"

for file in $DIR/*.in
do
	for i in {1..50}
	do
		base=$(basename "$file" .in)
		./caballos < $file > $RES/$base.out
	done
done
