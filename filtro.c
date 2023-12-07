#include <stdio.h>
#include <stdlib.h>
#include "lib/pgm.h"

struct Image filtro(struct Image o){

    //img será a imagem filtrada, aux será apenas uma estrutura auxiliar para resolver problemas com bordas
    struct Image img,aux;

    //Definindo img
    img.tipo = o.tipo;
    img.height = o.height;
    img.width = o.width;
    img.maxval = o.maxval;
    if(!(img.Data = (unsigned char **)calloc(img.height,sizeof(unsigned char*)))){
            printf("Faltou memória.");
            exit(1);
    }
    for(int i = 0; i<img.height; i++){
        if(!(img.Data[i] = (unsigned char *)calloc(img.width,sizeof(unsigned char)))){
            printf("Faltou memória.");
            exit(1);
        }
    }
    for(int i=0;i<img.height;i++){
        for(int j=0;j<img.width;j++){
            img.Data[i][j] = o.Data[i][j];
        }
    }

    //Definindo matriz auxiliar
    aux.height = o.height + 2;
    aux.width = o.height + 2;
    if(!(aux.Data = (unsigned char **)calloc(aux.height,sizeof(unsigned char*)))){
            printf("Faltou memória.");
            exit(1);
    }
    for(int i = 0; i<aux.height; i++){
        if(!(aux.Data[i] = (unsigned char *)calloc(aux.width,sizeof(unsigned char)))){
            printf("Faltou memória.");
            exit(1);
        }
    }

    //Colocando o img na auxilar, deixando os espaços das bordas 0.
    for(int i=0;i<img.height;i++){
        for(int j=0;j<img.width;j++){
            aux.Data[i+1][j+1] = img.Data[i][j];
        }
    }

    //Definindo a img a partir da auxiliar, de forma que as bordas serão consideradas 0
    for(int i=0;i<img.height;i++){
        for(int j=0;j<img.width;j++){
            img.Data[i][j] = media(aux,i+1,j+1);
        }
    }

    return img;
}