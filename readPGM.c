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

//Fazer a leitura da imagem e colocar os dados em uma estrutura

#include "library.h"

#define TAM 200

void readPGMImage(struct pgm *pio, char *foldername, char *filename){

	FILE *fp;
	char ch;
  char fileAddress[TAM];

  // Definir o caminho do arquivo
  sprintf(fileAddress, "%s/%s", foldername, filename);

  printf("%s\n", filename); // Exibir o nome do arquivo

  // Abrir e verificar a abertura do arquivo
	if (!(fp = fopen(fileAddress,"r"))){
		perror("Erro.");
		exit(1);
	}

  // Verificar se a imagem é do tipo pgm
	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48; // Inserir na estrutura o tipo da imagem
	
	fseek(fp,1, SEEK_CUR);

  // Ler os comentarios do arquivo
	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}
  
	fseek(fp,-2, SEEK_CUR);

  // Inserir na estrutura a dimensao da imagem
	fscanf(fp, "%d %d",&pio->c,&pio->r);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->mv);

  // Exibir as informações da imagem: tipo, dimensao e valor maximo.
  printf("TIPO: %d\nDIMENSÃO: %d %d\nMV: %d\n",pio->tipo,pio->c,pio->r, pio->mv);
  
	#ifdef __linux__
    fseek(fp,1, SEEK_CUR);
  #elif _WIN32
    fseek(fp,0, SEEK_CUR);
  #endif

  // Alocar o ponteiro que vai receber os pixels da imagem
	pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));

  // Identifica o tipo da imagem e armazena os pixels no ponteiro na estrutura
	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->r * pio->c); k++){
				fscanf(fp, "%hhu", pio->pData+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->pData,sizeof(unsigned char),pio->r * pio->c, fp);
		break;
		default:
			puts("Não está implementado");
	}

	fclose(fp); 

}
