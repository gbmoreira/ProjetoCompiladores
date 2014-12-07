#!/bin/bash

flex -t lexico.l > lexico.c
bison -g -d -v sintatico.y -o sintatico.c
gcc hashTable.c listaEncadeada.c sintatico.c -o simples


