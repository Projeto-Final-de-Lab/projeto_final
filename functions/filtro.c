#include <stdio.h>
#include <stdlib.h>
#include "../lib/pgm.h"

float media(struct Image o, int x, int y, int tamanho) {
    float soma = 0.0;
    int count = 0;
    int meio = tamanho / 2;

    for (int i = -meio; i <= meio; i++) {
        for (int j = -meio; j <= meio; j++) {
            if (x+i >= 0 && x+i < o.height && y+j >= 0 && y+j < o.width) {
                soma += o.Data[x+i][y+j];
                count++;
            }
        }
    }

    return soma / count;
}

struct Image filtro(struct Image o, int tamanho){

    //img será a imagem filtrada, aux será apenas uma estrutura auxiliar para resolver problemas com bordas
    struct Image new_image;

    //Definindo img
    new_image.tipo = o.tipo;
    new_image.height = o.height;
    new_image.width = o.width;
    new_image.maxval = o.maxval;

    // Alocando memória para os dados da imagem
    new_image.Data = (unsigned char **)malloc(new_image.height * sizeof(unsigned char *));
    for (int i = 0; i < new_image.height; i++) {
        new_image.Data[i] = (unsigned char *)malloc(new_image.width * sizeof(unsigned char));
    }

    for (int i = 0; i < new_image.height; i++) {
        for (int j = 0; j < new_image.width; j++) {
            new_image.Data[i][j] = (unsigned char)media(o, i, j, tamanho);
        }
    }

    return new_image;
}