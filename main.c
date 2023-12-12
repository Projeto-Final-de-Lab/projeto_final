#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "lib/func.h"
#include "lib/pgm.h"


#define DATASETS "./images"
#define OUTPUT "./filtradas/" // Definir o caminho da pasta de saída


int main() {
  // Início da medição do tempo
  clock_t inicio = clock();

  FILE *fptr;
  char *filename = "./program.txt";

  // Abre o arquivo em modo de leitura e escrita, criando-o se ele não existir
  fptr = fopen(filename,"a+");
    if (fptr == NULL) {
      printf("Erro ao abrir o arquivo %s\n", filename);
      exit(1);
  }

  DIR *d;
  struct dirent *dir; 
  d = opendir(DATASETS);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      //"." e ".." são os diretórios "atual" e "anterior" e foram
      // removido para evitar poluição na saída
      if(dir->d_name[0] != '.'){
        char inputFilename[256];
        char outputFilename[256];
        char quantizadaFilename[256];
        
        snprintf(inputFilename, sizeof(inputFilename), "%s/%s", DATASETS, dir->d_name);
        printf("%s\n", inputFilename);
        snprintf(outputFilename, sizeof(outputFilename), "%s%sfiltered.pgm", OUTPUT, dir->d_name); 

        char epstr[16];
        encontrarNome(inputFilename, epstr);

        printf("%s", epstr);

        // Criar uma estrutura pgm para a imagem original
        struct Image img;
        // Ler a imagem do arquivo
        readPGMImage(&img, inputFilename);
        // Criar uma estrutura pgm para a imagem suavizada
        struct Image img_filtrada;
        // Aplicar o filtro da média com janela 3x3 na imagem original
        filtro_media(&img, &img_filtrada, 7);
        //writePGMImage(&img_filtrada, outputFilename);
        // Criar uma estrutura pgm para a imagem quantizada
        struct Image img_quantizada_filtrada, img_quantizada_original;


        // Quantizar a imagem suavizada em 4 níveis
        quantizar(&img, &img_quantizada_original, 8);
        quantizar(&img_filtrada, &img_quantizada_filtrada, 8);
        // Criar uma matriz SCM para a imagem quantizada
        snprintf(quantizadaFilename, sizeof(quantizadaFilename), "%s%squantizada.pgm", OUTPUT, dir->d_name); 
        //writePGMImage(&img_quantizada_filtrada, quantizadaFilename);
        snprintf(quantizadaFilename, sizeof(quantizadaFilename), "%s%squantizada_original.pgm", OUTPUT, dir->d_name); 
       // writePGMImage(&img_quantizada_original, quantizadaFilename);

        //int scm[64];
        // Computar a matriz SCM da imagem quantizada
        //computar_scm(&img_quantizada, scm, 8);
        // Imprimir a matriz SCM na tela
        //imprimir_scm(scm, 8);

        applyscm(&img_quantizada_original, &img_quantizada_filtrada, 8, epstr);
        // Liberar a memória alocada para as imagens

        //unsigned char *scmMatrix;
        // computeSCM(&img_filtrada, &img_quantizada, 8);

        //fprintSCM(fptr, scmMatrix, 8);

        // Escreve stroma ou epithelium, 1,0 respectivamente
	      // extractLabelSCM(fptr, entry->d_name);

        // struct Image *qtz = &img_quantizada;
        // struct Image *filt = &img_filtrada;



        // unsigned char *scmMatrix;
        // scmMatrix = computeSCM(filt->Data, qtz->Data,img.height,img.width, 8);

        // fprintSCM(fptr, scmMatrix, 8);


        free(img.Data);
        free(img_filtrada.Data);
        free(img_quantizada_original.Data);
        free(img_quantizada_filtrada.Data);
        // free(scmMatrix);

       }
    }
      closedir(d);
    }
  
  fclose(fptr);
  // Fim da medição do tempo
  clock_t fim = clock();
  // Calcular o tempo decorrido em segundos
  double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Imprimir o tempo na tela
  printf("Tempo: %f segundos\n", tempo);
  // Retornar 0 para indicar sucesso
  return 0;
}

