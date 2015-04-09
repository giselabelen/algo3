#!/bin/bash

DIR=../tests_caballos

RES=../Resultados_tests_nuestros

echo "Borrando carpeta "$RES

rm -r $RES
mkdir $RES
touch $RES/testing3.txt	# esto va a servir por como está hecho el test3

echo "Compilando"

./compilar.sh
g++ testing.cpp -g -o testing

echo "Corriendo Tests Zombieland/Alta Frecuencia"
# para correr test1 o test2, comentar o descomentar correspondientemente
# en main de testing.cpp y elegir una de las siguientes líneas, comentando
# la otra.

./testing > $RES/testing1.txt
#./testing > $RES/testing2.txt

echo "Corriendo Tests Caballos"

for file in $DIR/*.in
do
	base=$(basename "$file" .in)
	./caballos < $file > $RES/$base.out
done
