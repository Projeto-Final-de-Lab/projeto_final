#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../lib/pgm.h"



void filterPGMImage(struct Image *img, int matrixSize) {
    int height = img->height;
    int width = img->width;
    unsigned char *newData = (unsigned char*) malloc(height * width * sizeof(unsigned char));
    int count = 0;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            count = 0;
            int sum = 0;
            for (int m = -matrixSize/2; m <= matrixSize/2; m++) {
                for (int n = -matrixSize/2; n <= matrixSize/2; n++) {
                    int y = i + m;
                    int x = j + n;
                    if (y >= 0 && y < height && x >= 0 && x < width) {
                        count++;
                        sum += img->Data[y * width + x];
                    }
                }
            }
            newData[i * width + j] = sum / count;
        }
    }

    free(img->Data);
    img->Data = newData;
}


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

// Função para computar a matriz SCM de uma imagem PGM
// Parâmetros: img - ponteiro para a estrutura pgm da imagem
//             scm - ponteiro para a matriz SCM
//             N - número de níveis de quantização
void computar_scm(struct Image *img, int *scm, int N) {
  // Inicializar a matriz SCM com zeros
  for (int i = 0; i < N * N; i++) {
    scm[i] = 0;
  }
  // Percorrer os pixels da imagem, ignorando as bordas
  for (int i = 1; i < img->height - 1; i++) {
    for (int j = 1; j < img->width - 1; j++) {
      // Obter o valor do pixel na imagem
      int valor = img->Data[i * img->width + j];
      // Calcular o nível de quantização correspondente
      int nivel = valor / ((img->maxval + 1) / N);
      // Percorrer os quatro vizinhos do pixel (cima, baixo, esquerda, direita)
      for (int k = -1; k <= 1; k += 2) {
        for (int l = -1; l <= 1; l += 2) {
          // Obter o valor do vizinho na imagem
          int vizinho = img->Data[(i + k) * img->width + (j + l)];
          // Calcular o nível de quantização correspondente
          int nivel_vizinho = vizinho / ((img->maxval + 1) / N);
          // Incrementar o elemento da matriz SCM correspondente ao par de níveis
          scm[nivel * N + nivel_vizinho]++;
        }
      }
    }
  }
}

// Função para imprimir a matriz SCM na tela
// Parâmetros: scm - ponteiro para a matriz SCM
//             N - número de níveis de quantização
void imprimir_scm(int *scm, int N) {
  // Percorrer os elementos da matriz SCM
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      // Imprimir o elemento na tela, separado por um espaço
      printf("%d ", scm[i * N + j]);
    }
    // Imprimir uma quebra de linha após cada linha da matriz
    printf("\n");
  }
}

