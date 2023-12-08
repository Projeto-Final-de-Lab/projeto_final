#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include "lib/filtro.h"
#include "lib/pgm.h"

#define DATASETS "./oncotex_mean_pgm_3x3"
#define FILTER_SIZE 3

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
                snprintf(outputFilename, sizeof(outputFilename), "%sfiltered.pgm", dir->d_name);

                applyfilter(inputFilename, outputFilename, FILTER_SIZE);

                

            }
        }
        closedir(d);
    }
    // Fim da medição do tempo  
    end = clock();
    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo Total: %lf\n",time_total);
}
