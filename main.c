#include <stdio.h>
#include <stdlib.h>
#include "lib/pgm.h"

int main(int argc, char *argv[]) {

    struct Image img;
    char *filename = argv[1];

    readPGMImage(&img, filename);
    viewPGMImage(&img);
    printf("Largura: %d\n", img.width);
    printf("Altura: %d\n", img.height);
    printf("Valor máximo: %d\n", img.maxval);
    printf("Tipo: %d\n", img.tipo);
    printf("Dados: %p\n", img.Data);
    writePGMImage(&img, "teste.pgm");

    return 0;
}
