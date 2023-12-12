#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../lib/pgm.h"


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
  printf("%c\n", nameinput[9]);
  if(nameinput[9] == '0'){
    nameoutput = 'epithelium';
  } else {
    nameoutput = 'stroma';
  }
}


int applyscm(struct Image *img, struct Image *qtzd, int N, char *final){

  FILE *fptr;
  char *filename = "./program.csv";

  // Abre o arquivo em modo de escrita, criando-o se ele não existir
  fptr = fopen(filename, "a+");
  if (fptr == NULL) {
    printf("Erro ao abrir o arquivo %s\n", filename);
    exit(1);
  }

  // Verifica se os tamanhos das imagens são iguais
  if (img->height != qtzd->height || img->width != qtzd->width) {
    printf("Erro: as imagens devem ter o mesmo tamanho\n");
    exit(1);
  }

  // Aloca memória para a matriz scm de tamanho N x N
  int **scm = malloc(N * sizeof(int *));
  if (scm == NULL) {
    printf("Erro ao alocar memória para a matriz scm\n");
    exit(1);
  }
  for (int i = 0; i < N; i++) {
    scm[i] = calloc(N, sizeof(int));
    if (scm[i] == NULL) {
      printf("Erro ao alocar memória para a matriz scm\n");
      exit(1);
    }
  }

  // Calcula a matriz scm a partir dos valores dos pixels das imagens
  for(int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            // Normaliza os valores dos pixels para o intervalo [0, N-1]
            int x = img->Data[i * img->width + j] * (N - 1) / 255;
            int y = qtzd->Data[i * qtzd->width + j] * (N - 1) / 255;
            // Incrementa a frequência do par (x, y) na matriz scm
            scm[x][y]++;
        }
  }

  // Escreve a matriz scm no arquivo separado por vírgulas
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      fprintf(fptr, "%d, ", scm[i][j]);
    }
  }
  fprintf(fptr, "%s\n", final);

  // Fecha o arquivo
  fclose(fptr);

  // Libera a memória da matriz scm
  for (int i = 0; i < N; i++) {
    free(scm[i]);
  }
  free(scm);
}




unsigned char *computeSCM(unsigned char *Data1, unsigned char *Data2, int columns, int rows, int levels) {

    // Aloca ponteiro para os dados
    unsigned char *scmMatrix = (unsigned char *)calloc((levels) * (levels), sizeof(unsigned char));
    if (scmMatrix == NULL) return 0;

    // Utiliza os valores de ambos os dados como index da matriz (Data1[i], Data2[i])
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            scmMatrix[Data1[i * columns + j] * (levels) + Data2[i * columns + j]]++;
        }
    }

    return scmMatrix;
}

void fprintSCM(FILE *file, unsigned char *scmMatrix, int quantizationLevels) {

    // Printa cada um dos valores dos dados da SCM
    for (int i = 0; i < quantizationLevels; i++) {
        for (int j = 0; j < quantizationLevels; j++) {
            fprintf(file, "%d, ", scmMatrix[i * (quantizationLevels) + j]);
        }
    }
}