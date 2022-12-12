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

#include "library.h"

void generateMatrix(int *matrix, struct pgm *img1, struct pgm *img2, int level);


void SCM(struct pgm *img1, struct pgm *img2, char *filename, int level){
  int *matrix=NULL;
  
  if(!(matrix = calloc(level*level,sizeof(int)))){
    puts("Memória Insuficiente");
    exit(3);
  }

  generateMatrix(matrix, img1, img2, level);

  FILE *fp;

  char archiveName[20];
  sprintf(archiveName, "SCM_%d.txt", level);

  fp = fopen(archiveName,"a+");

  if(fp==NULL){
    puts("Erro ao abrir o arquivo");
    exit(1);
  }

  for(int i=0; i<level*level; i++){
    fprintf(fp, "%d, ", *(matrix+i));
  }
  
  fprintf(fp,"%c", *filename);
  fputc('\n', fp);

  fclose(fp);
  
}

void generateMatrix(int *matrix, struct pgm *img1, struct pgm *img2, int level){
  int elem=0,c=0,r=0;

  do{
    for(int i=0; i<(img1->c*img1->r); i++){
      if(*(img1->pData+i)==r && *(img2->pData+i)==c){
        *(matrix+elem)+=1;
      }
    }
    if(c==(level-1)){
      c=0;
      r++;
    } else c++;
    elem++;
  } while(elem<level*level);

  puts("Matriz computada!\n");
}
