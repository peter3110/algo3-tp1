#!/bin/bash

#Tomo como parametros el .in del test,  hasta que K quiero estudiar para dicho test
#para dicho test (ej.: testRed.in) y el intervalo de k's deseado

N="$1"
INTERVALO="$2"
TAM="$3"
H="$4"

#Para cada uno de los valores de n que quiero estudiar dejando intervalos..

for i in $(seq 1 $INTERVALO $N); do

	#Ejecuto comandos

	TXT="./experimentar ./exp_aleatorios/exp1.txt $i $TAM $H"
	$TXT
	TXT="./prob2 ./exp_aleatorios/exp1.txt"
	$TXT
	
done
