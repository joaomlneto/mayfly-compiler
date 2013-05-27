#!/bin/bash

for file_mf in B*.mf
do

	echo " "
	echo "-------- $file_mf --------"

	file_exp=${file_mf//.mf/.exp}
	file_asm=${file_mf//.mf/.asm}
	file_o=${file_mf//.mf/.o}
	file_exec=${file_mf//.mf/}
	file_out=${file_mf//.mf/.out}

	../project/mayfly $file_mf
	yasm -felf32 $file_asm
	ld -o $file_exec $file_o -lrts
	./$file_exec > $file_out

	diff $file_out $file_exp

	rm -f $file_asm $file_o $file_exec

done
