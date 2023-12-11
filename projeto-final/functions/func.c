#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include "../lib/pgm.h"

void filtro_media(struct Image *img, struct Image *out, int n) {
  // Copiar os atributos da imagem original para a imagem suavizada
  out->tipo = img->tipo;
  out->width = img->width;
  out->height = img->height;
  out->maxval = img->maxval;
  // Alocar memória para os dados da imagem suavizada
  out->Data = (unsigned char *)malloc(out->height * out->width * sizeof(unsigned char));
  // Calcular o raio da janela do filtro
  int r = n / 2;
  // Percorrer os pixels da imagem original, ignorando as bordas
  for (int i = r; i < img->height - r; i++) {
    for (int j = r; j < img->width - r; j++) {
      // Inicializar a soma dos valores dos pixels na janela
      int soma = 0;
      // Percorrer os pixels na janela do filtro
      for (int k = -r; k <= r; k++) {
        for (int l = -r; l <= r; l++) {
          // Somar os valores dos pixels na janela
          soma += img->Data[(i + k) * img->width + (j + l)];
        }
      }
      // Calcular a média dos valores dos pixels na janela
      int media = soma / (n * n);
      // Atribuir a média ao pixel correspondente na imagem suavizada
      out->Data[i * out->width + j] = media;
    }
  }
}

