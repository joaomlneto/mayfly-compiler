#!/bin/bash

# Source file (.mf extension)
file="test.mf"

file_asm=${file//mf/asm}
file_o=${file//mf/o}
file_exec=${file//.mf/}

rm -f $file_asm
echo "---------- MAKE MAYFLY ----------"
#make clean -s
make
echo " "
echo "----------- TEST FILE -----------"
cat $file
echo " "
echo "----------- COMPILING -----------"
./mayfly -g $file
echo " "
echo "----------- ASSEMBLER -----------"
yasm -felf32 $file_asm
echo " "
echo "------------ LINKING ------------"
ld -o $file_exec $file_o -lrts
echo " "
echo "------------ POSTFIX ------------"
sed '/\t/d' $file_asm
#sed '/\t/d' $file_asm | sed '/:/d'
echo " "
echo "---------- EXEC OUTPUT ----------"
./$file_exec
echo " "
rm -f $file_o $file_exec
