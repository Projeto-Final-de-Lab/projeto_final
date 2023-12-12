#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include "lib/filtro.h"
#include "lib/pgm.h"

#define DATASETS "./oncotex_pgm"
#define FILTER_SIZE 3

int main()
{
    clock_t begin, end;
    double time_total=0;
    DIR *d;
    struct dirent *dir;

    d = opendir(DATASETS);

    if (d)
    {
        begin = clock();
        while ((dir = readdir(d)) != NULL)
        {
            if(dir->d_name[0] != '.'){
                begin = clock();
                char inputFilename[256];
                char outputFilename[256];

                snprintf(inputFilename, sizeof(inputFilename), "%s/%s", DATASETS, dir->d_name);
                snprintf(outputFilename, sizeof(outputFilename), "%s/%s", OUTPUT_DIR, dir->d_name);

                struct pgm *img = readPGMFile(inputFilename);
                filterPGMImage(img, FILTER_SIZE);
                writePGMFile(outputFilename, img);
                freePGM(img);
            }
        }
        closedir(d);
    }

    end = clock();
    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo Total: %lf\n",time_total);
}