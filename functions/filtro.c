#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../lib/pgm.h"

void filterPGMImage(struct pgm *img, int matrixSize) {
    int height = img->r;
    int width = img->c;
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
                        sum += img->pData[y * width + x];
                    }
                }
            }
            newData[i * width + j] = sum / count;
        }
    }

    free(img->pData);
    img->pData = newData;
}

