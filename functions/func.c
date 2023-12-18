#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../lib/pgm.h"

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

void filtro_media(struct Image *img, struct Image *out, int n) {
  // Verificar se os ponteiros são válidos

  // Alocar memória para a imagem de saída
  out->tipo = img->tipo;
  out->width = img->width;
  out->height = img->height;
  out->maxval = img->maxval;
  out->Data = (unsigned char *)malloc(out->width * out->height * sizeof(unsigned char));
  if (out->Data == NULL) return;

  // Definir o raio da janela
  int r = n / 2;

  // Percorrer cada pixel da imagem de entrada, incluindo as bordas
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      // Calcular a soma dos valores dos pixels vizinhos dentro da janela
      int sum = 0;
      int count = 0; // Contar quantos pixels estão dentro do domínio
      for (int k = -r; k <= r; k++) {
        for (int l = -r; l <= r; l++) {
          // Verificar se o pixel vizinho está dentro do domínio da imagem de entrada
          if (i + k >= 0 && i + k < img->height && j + l >= 0 && j + l < img->width) {
            sum += img->Data[(i + k) * img->width + (j + l)];
            count++;
          }
        }
      }
      // Dividir a soma pelo número de pixels na janela que estão dentro do domínio para obter a média
      int avg = sum / count;

      // Atribuir a média ao pixel correspondente na imagem de saída
      out->Data[i * out->width + j] = avg;
    }
  }
}

void quantizar(struct Image *img, struct Image *out, int N) {
  // Copiar os atributos da imagem original para a imagem quantizada
  out->tipo = img->tipo;
  out->width = img->width;
  out->height = img->height;
  out->maxval = img->maxval;
  // Alocar memória para os dados da imagem quantizada
  out->Data = (unsigned char *)malloc(out->height * out->width * sizeof(unsigned char));
  // Calcular o intervalo de cada nível de quantização
  int intervalo = (img->maxval + 1) / N;
  // Percorrer os pixels da imagem original
  for (int i = 0; i < img->height; i++) {
    for (int j = 0; j < img->width; j++) {
      // Obter o valor do pixel na imagem original
      int valor = img->Data[i * img->width + j];
      // Calcular o nível de quantização correspondente
      int nivel = valor / intervalo;
      // Atribuir o valor médio do nível ao pixel na imagem quantizada
      out->Data[i * out->width + j] = nivel * intervalo + intervalo / 2;
    }
  }
}

void encontrarNome(char *nameinput, char *nameoutput){
  if(nameinput[9] == '0'){
    strcpy(nameoutput, "epithelium");
  } else {
    strcpy(nameoutput, "stroma");
  }
}

unsigned char* criarSCM(struct Image *img, struct Image *qtzd, int N){
  unsigned char *scm = calloc(N * N, sizeof(unsigned char));

  // Verifica se os tamanhos das imagens são iguais
  if (img->height != qtzd->height || img->width != qtzd->width) {
    printf("As imagens devem ter o mesmo tamanho\n");
    exit(1);
  }

  // Calcula a matriz scm a partir dos valores dos pixels das imagens
  for(int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            // Normaliza os valores dos pixels para o intervalo [0, N-1]
            int x = img->Data[i * img->width + j] * (N - 1) / 255;
            int y = qtzd->Data[i * qtzd->width + j] * (N - 1) / 255;
            // Incrementa a frequência do par (x, y) na matriz scm
            scm[x*N+y]++;
        }
  }

  return scm;
}

void imprimirSCM(FILE *arquivo, unsigned char *scm, int N, char *final){
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fprintf(arquivo, "%d, ", scm[i*N+j]);
    }
  }
  fprintf(arquivo, "%s\n", final);
}



void writeCSVHeader(FILE *file, int quantizationLevels) {
    // Escreve a primeira linha do arquivo CSV com a contagem de 0 até nivel*nivel
    for (int i = 0; i < quantizationLevels; i++) {
        for (int j = 0; j < quantizationLevels; j++) {
            fprintf(file, "%d, ", i * quantizationLevels + j+1);
        }
    }
    fprintf(file, "%d\n", quantizationLevels*quantizationLevels+1);
}
