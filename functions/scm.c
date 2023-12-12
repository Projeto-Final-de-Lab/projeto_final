#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/pgm.h"

int applyscm(char *imagemEntrada, char *imagemSuavizada, int scmNivel){

    struct Image ent, sua;

    readPGMImage(&ent, imagemEntrada);
    readPGMImage(&sua, imagemSuavizada);

    // Verifica se as imagens têm o mesmo tamanho
    if (ent.height != sua.height || ent.width != sua.width) {
        printf("As imagens devem ter o mesmo tamanho\n");
        return -1;
    }


    FILE *fptr;
    fptr = fopen("program.txt","w");

    if(fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }


    int i, j, x, y;
    int vetor[scmNivel * scmNivel];



    for(i = 0; i < scmNivel; i ++){
        for(j = 0; j < scmNivel; j++){
 
            vetor[((i+1)*(j+1))-1] = 0;

            for(x = 0; x < ent.height; x++){
                for(y = 0; y < ent.width; y++){
                    if((ent.Data[x][y]==i) && (sua.Data[x][y]==j)){
                        vetor[((i+1)*(j+1))-1]++;
                    }
                }
            }
            fprintf(fptr,"%d", vetor[(((i+1)*(j+1))-1)]);
        }
        fprintf(fptr, "\n");
    }

    fclose(fptr);

}