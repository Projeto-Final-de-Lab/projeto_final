#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
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

