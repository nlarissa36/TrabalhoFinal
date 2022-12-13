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

//Realiza a quantização da imagem

#include "library.h"

void quantize(struct pgm *img, int level){
  
  int quant = (img->mv+1) / level; 
  int start, end, count=0; // começa em 0 e termina em level-1
  int inter = quant;
  
   puts("Quantizando Imagem PGM");
   while (inter <= img->mv+1){
     start = inter - quant;
     end = inter-1;
     
  // Compara os dados e transforma os que entram no intervalo dos níveis
    for (int k=0; k < (img->r * img->c); k++){
      if ((*(img->pData+k) >= start) && (*(img->pData+k) <= end)){
        *(img->pData+k) = count;
	    }
    } 
    count++;
    inter += quant;
  }

}
