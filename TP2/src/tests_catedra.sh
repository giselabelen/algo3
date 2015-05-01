#!/bin/bash

DIR=../tests_catedra
DIR1=$DIR/tests.tp2.ej1.v1.1
#DIR2=$DIR/	FALTAN LOS TESTS PARA EL EJ2
DIR3=$DIR/tests.tp2.ej3

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

#~ echo "Corriendo Tests Dakkar"
#~ 
#~ for file in $DIR1/*.in
#~ do
	#~ base=$(basename "$file" .in)
	#~ ./dakkar < $file > $RES1/$base.out1
#~ done

#echo "Corriendo Tests Zombieland II"

#for file in $DIR2/*.in
#do
#	 base=$(basename "$file" .in)
#	 ./zombieland < $file > $RES2/$base.out1
#done

echo "Corriendo Tests Petróleo"

for file in $DIR3/*.in
do
	base=$(basename "$file" .in)
	./petroleo < $file > $RES3/$base.out1
done
