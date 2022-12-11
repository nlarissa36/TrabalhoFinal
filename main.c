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

#include <dirent.h>
#include "library.h"

#define QTDIMG 1312
#define FOLDER "./oncotex_pgm"
 
int main(){
  
  int k;
	clock_t begin, end;
	double time_per_img, time_total=0;
  
  DIR *d;
  struct dirent *dir;
  d = opendir(FOLDER);

  if (d){

    //Menu quantização
    int level = menu();
    printf("Nivel: %d\n\n", level);
    
    
    while (((dir = readdir(d)) != NULL)){

      // Ignorar arquivo "." e ".."
      if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name,"..")){
        continue;
      }

      // Iniciar medição do tempo.
      begin = clock();

      struct pgm img1, img2;

      // Leitura da Imagem -PGM
      readPGMImage(&img1,FOLDER,dir->d_name);
      
      // Quantização da Imagem -PGM
      quantize(&img1,level);
      
      dir = readdir(d); // Próximo arquivo
      
      // Leitura da Imagem suavizada -PGM
      readPGMImage(&img2,FOLDER,dir->d_name);
      
      // Quantização da Imagem suavizada -PGM
      quantize(&img2,level);

      // Saida - Salvar matriz vetorizada no arquivo de características com o rotulo no final
      SCM(&img1, &img2, dir->d_name, level);
      
      // Finalizar medição do tempo.
      end = clock();

      // Acumular tempo
      time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
		  time_total += time_per_img;
    }
    
    closedir(d);
    
    // Calcular tempo médio por imagem.
    printf("\nTempo médio: %lf\n",time_total/(QTDIMG/2));
    printf("Tempo Total: %lf\n",time_total);
  }

  return(0);
}		
