<p align="center">
  <a href="#main">Main</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#lerpgm">LerPGM</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#quantização">Quantização</a>&nbsp;&nbsp;&nbsp;|&nbsp;&nbsp;&nbsp;
  <a href="#scm">SCM</a>&nbsp;&nbsp;&nbsp;
  </p>

# Trabalho Final Laboratório de Programação 👩‍💻
Processamento de imagens com o intuito de gerar uma matriz SCM para descrever as características de uma imagem de entrada.

### Colaboradoras:
- Mikaelle Costa
- Ana Flavia
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
Nessa parte se localiza a declaração das variaveis e das constantes que utilizaremos nesse arquivo. Contendo a quantidade de imagens a serem processadas, a localização da pasta que as mesmas se encontram, variaveis para calcular o tempo, e por fim, a abertura do diretório que iremos trabalhar.

```c
if (d){

  int level = menu();
  printf("Nivel: %d\n\n", level);
  
  while (((dir = readdir(d)) != NULL)){
  
  if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name,"..")){
        continue;
      }
```
Com o diretório aberto, utilizamos nossa função MENU para solicitar o nível que iremos quantizar. A partir disso, poderemos percorrer todas as imagens. 
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
- 2 - Ler os pixels da imagem passando como parametro a variavel do tipo struct, a pasta e o respectivo nome.
- 3 - Quantizar a imagem de acordo com o nivel inserido pelo menu.
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
Para calcular o tempo total e o tempo médio, o programa incrementa o tempo obtido por cada par e salva em "time_total". Após todas as imagens serem processadas, o tempo médio por par é exibido e o tempo total também.


### LerPGM

### Quantização

### SCM


