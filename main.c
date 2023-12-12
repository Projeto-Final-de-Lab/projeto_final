#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include "lib/filtro.h"
#include "lib/scm.h"
#include "lib/pgm.h"

#define DATASETS "./oncotex_mean_pgm_3x3"
#define OUTPUT "./filtered/"
int main()
{
    // Inicio da medição do tempo
	clock_t begin, end;
	double time_total=0;
    begin = clock();
    DIR *d;
    struct dirent *dir;
    d = opendir(DATASETS);
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //"." e ".." são os diretórios "atual" e "anterior" e foram
            // removido para evitar poluição na saída
            if(dir->d_name[0] != '.'){
                begin = clock();
                char inputFilename[256];
                char outputFilename[256];

                snprintf(inputFilename, sizeof(inputFilename), "%s/%s", DATASETS, dir->d_name);
                snprintf(outputFilename, sizeof(outputFilename), "%s%sfiltered.pgm",OUTPUT, dir->d_name);

                applyfilter(inputFilename, outputFilename, 3);
                applyscm(inputFilename, outputFilename, 8);
                
            }
        }
        closedir(d);
        DIR *d_output;
    struct dirent *dir_output;
    d_output = opendir(OUTPUT);
    if (d_output)
    {
        while ((dir_output = readdir(d_output)) != NULL)
        {
            if(dir_output->d_name[0] != '.'){
                char inputFilename[256];
                char outputFilename[256];

                snprintf(inputFilename, sizeof(inputFilename), "%s/%s", OUTPUT, dir_output->d_name);
                snprintf(outputFilename, sizeof(outputFilename), "%s%sfiltered.pgm", OUTPUT, dir_output->d_name);

                applyscm(inputFilename, outputFilename, 8);
            }
        }
        closedir(d_output);
    }
    }
    // Fim da medição do tempo  
    end = clock();
    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo Total: %lf\n",time_total);
}
