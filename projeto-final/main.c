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
  DIR *d;
  //DIR *f;
  struct dirent *dir;
  //struct dirent *fdir;
    
  d = opendir(DATASETS);
  //f = opendir(OUTPUT);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      //"." e ".." são os diretórios "atual" e "anterior" e foram
      // removido para evitar poluição na saída
      if(dir->d_name[0] != '.'){
        char inputFilename[256];
        char outputFilename[256];
        //char outputScm[256];
        snprintf(inputFilename, sizeof(inputFilename), "%s/%s", DATASETS, dir->d_name);
        snprintf(outputFilename, sizeof(outputFilename), "%s%sfiltered.pgm", OUTPUT, dir->d_name); 
        // Criar uma estrutura pgm para a imagem original
        struct Image img;
        // Ler a imagem do arquivo
        readPGMImage(&img, inputFilename);
        // Criar uma estrutura pgm para a imagem suavizada
        struct Image img_suavizada;
        // Aplicar o filtro da média com janela 3x3 na imagem original
        filtro_media(&img, &img_suavizada, 7);
        writePGMImage(&img_suavizada, outputFilename);
        // Criar uma estrutura pgm para a imagem quantizada
        struct Image img_quantizada;
        // Quantizar a imagem suavizada em 4 níveis
        quantizar(&img_suavizada, &img_quantizada, 8);
        // Criar uma matriz SCM para a imagem quantizada
        int scm[64];
        // Computar a matriz SCM da imagem quantizada
        computar_scm(&img_quantizada, scm, 8);
        // Imprimir a matriz SCM na tela
        imprimir_scm(scm, 8);
        // Liberar a memória alocada para as imagens
        free(img.Data);
        free(img_suavizada.Data);
        free(img_quantizada.Data);

       }
    }
      closedir(d);
      //closedir(f);
    }
  

  // Fim da medição do tempo
  clock_t fim = clock();
  // Calcular o tempo decorrido em segundos
  double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  // Imprimir o tempo na tela
  printf("Tempo: %f segundos\n", tempo);
  // Retornar 0 para indicar sucesso
  return 0;
}

