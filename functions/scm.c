#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "../lib/pgm.h"

int applyscm(char *imagemEntrada, char *imagemSuavizada, char *arquivoSaida, int scmNivel){

    struct Image ent, sua, scm;

    readPGMImage(&ent, imagemEntrada);
    readPGMImage(&sua, imagemSuavizada);

    scm.height = scmNivel;
    scm.width = scmNivel;
    scm.maxval = ent.maxval;

    scm.Data = (unsigned char **)malloc(scm.height * sizeof(unsigned char *));
    for (int i = 0; i < scm.height; i++) {
        scm.Data[i] = (unsigned char *)malloc(scm.width * sizeof(unsigned char));
    }

    int i, j, x, y;

    for(i = 0; i < scmNivel; i ++){
        for(j = 0; j < scmNivel; j++){
 
            scm.Data[i][j] = 0;

            for(x = 0; x < ent.height; x++){
                for(y = 0; y < ent.width; y++){
                    if((ent.Data[x][y]==i) && (sua.Data[x][y]==j)){
                        scm.Data[i][j]++;
                    }
                }
            }
        }
    }

    writePGMImage(&scm, arquivoSaida);
}


