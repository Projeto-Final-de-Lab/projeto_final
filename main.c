#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include "lib/func.h"
#include "lib/pgm.h"

/*************************************************************/
/* Aluno 01: Luiz Henrique Teixeira Viana                    */
/* Matricula: 20231045050556                                 */
/*                                                           */
/* Aluno 02: Cleiton Martins Portela                         */
/* Matricula: 20231045050432                                 */
/*                                                           */
/* Aluno 03: José Ruan Rodrigues da Silva                    */
/* Matricula: 20231045050475                                 */
/*                                                           */
/* Avaliação 04: Trabalho Final                              */
/* 04.505.23 - 2023.2 - Prof. Daniel Ferreira                */
/* Compilador: gcc.exe (Rev7, Built by MSYS2 project) 13.1.0 */
/*************************************************************/

#define MAX 256
#define DATASETS "./images"
#define OUTPUT "./filtradas/"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <TAM_FILTER> <TAM_SCM>\n", argv[0]);
    return 1;
  }

  char inputCSV[20];
  sprintf(inputCSV, "./%sx%s_%s.csv", argv[1], argv[1], argv[2]);


  FILE *csv;
  char *filename = inputCSV;

  // Abre o arquivo em modo de escrita, criando-o se ele não existir
  csv = fopen(filename, "a+");
  if (csv == NULL) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    exit(1);
  }
  int TAM_FILTER = atoi(argv[1]);
  int TAM_SCM = atoi(argv[2]);

  clock_t inicio = clock();


  DIR *d;
  struct dirent *dir; 
  d = opendir(DATASETS);

  writeCSVHeader(csv, TAM_SCM);

  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if(dir->d_name[0] != '.'){
        char inputFilename[MAX];
        char outputFilename[MAX];
        char quantizadaFilename[MAX];
        
        snprintf(inputFilename, sizeof(inputFilename), "%s/%s", DATASETS, dir->d_name);
        snprintf(outputFilename, sizeof(outputFilename), "%s%sfiltered.pgm", OUTPUT, dir->d_name); 

        char ep_str[16];
        encontrarNome(inputFilename, ep_str);

        struct Image img;
        readPGMImage(&img, inputFilename);
        struct Image img_filtrada;
        filtro_media(&img, &img_filtrada, TAM_FILTER);

        struct Image img_quantizada_filtrada, img_quantizada_original;
        quantizar(&img, &img_quantizada_original, TAM_SCM);
        quantizar(&img_filtrada, &img_quantizada_filtrada, TAM_SCM);

        snprintf(quantizadaFilename, sizeof(quantizadaFilename), "%s%squantizada.pgm", OUTPUT, dir->d_name); 
        snprintf(quantizadaFilename, sizeof(quantizadaFilename), "%s%squantizada_original.pgm", OUTPUT, dir->d_name); 

        unsigned char *scmMatriz = criarSCM(&img_quantizada_original, &img_quantizada_filtrada, TAM_SCM);
        imprimirSCM(csv, scmMatriz, TAM_SCM, ep_str);

        free(img.Data);
        free(scmMatriz);
        free(img_filtrada.Data);
        free(img_quantizada_original.Data);
        free(img_quantizada_filtrada.Data);
      }
    }
    closedir(d);
  }

  fclose(csv);
  clock_t fim = clock();
  double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
  printf("Tempo: %f segundos\n", tempo);
  return 0;
}
