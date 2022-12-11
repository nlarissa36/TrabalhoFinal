/*Aluno: Mikaelle Costa dos Santos
Matricula: 20221045050311
Aluno: Ana Flávia Torres do Carmo
Matricula: 20221045050427
Aluno: Isabelly Pinheiro da Costa
Matricula: 20221045050460
Aluno: Larissa do Nascimento Vieira
Matricula: 20202045050412
Avaliação 04: Trabalho Final
04.505.23 - 2022.2 - Prof. Daniel Ferreira
Compilador: gcc Versão: version 6.3.0 (MinGW.org GCC-6.3.0-1)
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

int menu();
void readPGMImage(struct pgm *, char *, char *);
void quantize(struct pgm *, int);
void SCM(struct pgm *, struct pgm *, char *, int);