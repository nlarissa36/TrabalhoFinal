<p align="center">
  <a href="#main">Main</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#lerpgm">LerPGM</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#quantização">Quantização</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#scm">SCM</a>&nbsp;&nbsp;&nbsp;
  </p>

# Trabalho Final Laboratório de Programação 👩‍💻
Processamento de imagens com o objetivo de gerar uma matriz SCM para descrever as características de uma imagem de entrada.

### Colaboradoras:
- Mikaelle Costa
- Ana Torres
- Isabelly Pinheiro
- Larissa Vieira

# 💻 Projeto
Explicação de como cada etapa principal do código foi desenvolvida:

### Main
Arquivo.c principal do nosso programa no qual concentra todas as etapas do projeto.

```c 
#define QTDIMG 1312
#define FOLDER "./oncotex_pgm"
 
int main(){
  
 int k;
 clock_t begin, end;
 double time_per_img, time_total=0;
 
 DIR *d;
 struct dirent *dir;
 d = opendir(FOLDER);
```
Nessa parte se localiza a declaração das variáveis e das constantes que utilizaremos nesse arquivo. Contendo a quantidade de imagens a serem processadas, a localização da pasta que as mesmas se encontram, variáveis para calcular o tempo, e por fim, a abertura do diretório que iremos trabalhar.

```c
if (d){

  int level = menu();
  printf("Nivel: %d\n\n", level);
  
  while (((dir = readdir(d)) != NULL)){
  
  if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name,"..")){
        continue;
      }
```
Com o diretório aberto, utilizamos a função MENU para solicitar o nível que iremos quantizar. A partir disso, poderemos percorrer todas as imagens. 
> problema de exibição do "." e do ".." resolvido!

```c
begin = clock();

struct pgm img1, img2;

readPGMImage(&img1,FOLDER,dir->d_name);
quantize(&img1,level);
      
dir = readdir(d); // Próximo arquivo
      
readPGMImage(&img2,FOLDER,dir->d_name);
quantize(&img2,level);

SCM(&img1, &img2, dir->d_name, level);
      
end = clock();
```
- 1 - Iniciar a medição do tempo para cada par a ser processado (1 img original e 1 img filtrada).
- 2 - Ler os pixels da imagem passando como parâmetro a variável do tipo struct, a pasta e o respectivo nome.
- 3 - Quantizar a imagem de acordo com o nível inserido pelo menu.
- 4 - Computar a matriz SCM com base nas 2 imagens quantizadas.
- 5 - Interromper a medição do tempo ao finalizar as etapas.

```c
time_per_img = (double)(end - begin) / CLOCKS_PER_SEC;
time_total += time_per_img;
}
closedir(d);
   
printf("\nTempo médio: %lf\n",time_total/QTDIMG);
printf("Tempo Total: %lf\n",time_total);
  }
```
Para calcular o tempo total e o tempo médio, o programa incrementa o tempo obtido por cada par e salva em "time_total". Após todas as imagens serem processadas, o tempo médio por imagem é exibido e o tempo total também.

### LerPGM
Arquivo.c que realiza a leitura da imagem, transformando em dados cada pixel da mesma.

```c
#define TAM 200

void readPGMImage(struct pgm *pio, char *foldername, char *filename){

	FILE *fp;
	char ch;
  char fileAddress[TAM];

  sprintf(fileAddress, "%s/%s", foldername, filename);

  printf("%s\n", filename);
  
  if (!(fp = fopen(fileAddress,"r"))){
		perror("Erro.");
		exit(1);
	}
```
Define variáveis e constantes a serem utilizadas, contendo o tamanho do nome para o caminho do arquivo e as variáveis a serem usadas, bem como abre o arquivo.

```c
if ( (ch = getc(fp))!='P'){
	puts("A imagem fornecida não está no formato pgm");
	exit(2);
}
  
pio->tipo = getc(fp)-48;
	
fseek(fp,1, SEEK_CUR);

while((ch=getc(fp))=='#'){
	while( (ch=getc(fp))!='\n');
}
  
fseek(fp,-1, SEEK_CUR);

fscanf(fp, "%d %d",&pio->c,&pio->r);
if (ferror(fp)){ 
	perror(NULL);
	exit(3);
}	
fscanf(fp, "%d",&pio->mv);

printf("TIPO: %d\nDIMENSÃO: %d %d\nMV: %d\n",pio->tipo,pio->c,pio->r, pio->mv);
  
fseek(fp,1, SEEK_CUR)
```
Essa parte checa o formato se está em PGM, em P5 ou P2, e ignora os eventuais comentários entre o tipo e a dimensão. Ele reserva na estrutura o tipo, a dimensão e o valor máximo e imprime esses valores para o usuário. No final o ponteiro segue em 1 para poder fazer a leitura da parte certa.

```c
pio->pData = (unsigned char*) malloc(pio->r * pio->c * sizeof(unsigned char));


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
  ```
A alocação dinâmica do ponteiro dos dados é feita de acordo com a dimensão da imagem. Para que o programa leia a imagem, ele realiza uma verificação de tipo e caso seja do tipo P2 (dados em texto), percorre-se a imagem inteira e armazena pixel por pixel no ponteiro na estrutura; caso seja do tipo P5 (dados em binário), a leitura é feita em forma de blocos, logo, os pixels serão armazenados todos de uma vez.

### Quantização
Arquivo.c responsável por quantizar cada imagem.

```c
void quantize(struct pgm *img, int level){
  
  int quant = (img->mv+1) / level; 
  int start, end, count=0; // começa em 0 e termina em level-1
  int inter = quant;
 
```
A função recebe um ponteiro do tipo da estrutura e o nível de quantização. A variável 'quant' se refere a quantidade de valores por intervalo que compõe cada nível, 'start' e 'end' são para sinalizar o começo e o fim de cada intervalo, e count para avançar o n° do intervalo até chegar em count=level-1. 'inter' começará igual a 'quant' para definir o 1° nível.

```c
while (inter <= img->mv+1){
  start = inter - quant;
  end = inter-1; 
  
  for (int k=0; k < (img->r * img->c); k++){
    if ((*(img->pData+k) >= start) && (*(img->pData+k) <= end)){
    *(img->pData+k) = count;
	 }
 } 
   count++;
   inter += quant;
  }
```
A quantização será feita enquanto os valores do intervalo forem menor ou igual ao ValorMaximo. 'start' na primeira execução será igual a 0 e mudará de acordo com o incremento do 'inter'. O loop for irá percorrer a dimensão da imagem comparando os dados para cada intervalo, e caso se encaixem, transformando-os no respectivo no n° do intervalo. No final avançamos para o próximo intervalo e incrementamos 'inter' com 'quant' para que assim gere um novo 'start' e 'end' com base na divisão feita no 'quant'.

### SCM
Arquivo.c que cria a matriz de ocorrências comparando as duas imagens processadas por par (filtrada e a original).
```c
void generateMatrix(int *matrix, struct pgm *img1, struct pgm *img2, int level){
  int elem=0,c=0,r=0;

  do{
    for(int i=0; i<(img1->c*img1->r); i++){
      if(*(img1->pData+i)==c && *(img2->pData+i)==r){
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
```
Essa função recebe como paramêtros o ponteiro que será salva a matriz SCM, as duas imagens e o nível de quantização das mesmas. Percorre a imagem por meio de um loop baseado na sua dimensão, compara os dados das duas imagens e caso sejam iguais, soma +1 na posição respectiva da matriz para sinalizar sua ocorrência. Ao finalizar a comparação, verifica-se o número da coluna e caso seja a última, incrementa-se o número da linha; caso não, incrementa-se o número da coluna e permanece na mesma linha. Esse processo será realizado enquanto o elemento da matriz SCM for menor que dimensão.

```c
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
```
Essa função recebe como paramêtros as duas imagens, o nome delas e o nível da quantização realizada. A alocação do ponteiro da matriz SCM é feita pelo calloc para que todos os elementos comecem em 0 e sejam preenchidos pela função de gerar matriz. Um arquivo .txt é criado com a identificação de qual nível as imagens foram quantizadas e a partir disso, insere as ocorrências armazenadas pela matriz em forma de vetor. No final de cada vetor, a identificação baseada em características de cada imagem é adicionada (sendo 0 ou 1).
