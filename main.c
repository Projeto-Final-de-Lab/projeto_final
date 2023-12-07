#include <stdio.h>
#include <stdlib.h>
#include "lib/pgm.h"

int main(int argc, char *argv[]) {

    struct Image img;
    struct Image new_image;
    char *filename = argv[1];

    readPGMImage(&img, filename);
    viewPGMImage(&img);

    writePGMImage(&img, "teste.pgm");

    return 0;
}
