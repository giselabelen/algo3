#!/bin/bash

DIR=../tests_catedra
DIR1=$DIR/tests.tp1.ej1
DIR2=$DIR/tests.tp1.ej2
DIR3=$DIR/tests.tp1.ej3

RES=../Resultados_tests_catedra
RES1=$RES/Ej1
RES2=$RES/Ej2
RES3=$RES/Ej3

echo "Borrando carpeta "$RES

rm -r $RES
mkdir $RES
mkdir $RES1
mkdir $RES2
mkdir $RES3

echo "Compilando"

./compilar.sh

echo "Corriendo Tests Zombieland"

for file in $DIR1/*.in
do
	base=$(basename "$file" .in)
	./zombieland < $file > $RES1/$base.out
done

echo "Corriendo Tests AltaFrecuencia"

for file in $DIR2/*.in
do
	base=$(basename "$file" .in)
	./altafrecuencia < $file > $RES2/$base.out
done

echo "Corriendo Tests Caballos"

for file in $DIR3/*.in
do
	base=$(basename "$file" .in)
	./caballos < $file > $RES3/$base.out
done
