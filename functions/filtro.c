#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../lib/pgm.h"

int applyfilter(char *inputFilename, char *outputFilename, int filterSize) {
    struct Image original, result;
    int sum;
    int divisor = filterSize * filterSize;

    // Load the input PGM image
    readPGMImage(&original, inputFilename);

    result.width = original.width - filterSize + 1;
    result.height = original.height - filterSize + 1;
    result.maxval = original.maxval;

    result.Data = (unsigned char **)malloc(result.height * sizeof(unsigned char *));
    for (int i = 0; i < result.height; i++) {
        result.Data[i] = (unsigned char *)malloc(result.width * sizeof(unsigned char));
    }

    for (int i = 0; i < result.height; i++) {
        for (int j = 0; j < result.width; j++) {
            sum = 0;

            for (int x = 0; x < filterSize; x++) {
                for (int y = 0; y < filterSize; y++) {
                    sum += original.Data[i + x][j + y];
                }
            }

            result.Data[i][j] = sum / divisor;
        }
    }
    
    writePGMImage(&result, outputFilename);

    
}
