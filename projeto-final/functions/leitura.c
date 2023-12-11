#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>
#include "../lib/pgm.h"


void readPGMImage(struct Image *pio, char *filename){

	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"r"))){
		perror("Erro.");
		exit(1);
	}

	if ( (ch = getc(fp))!='P'){
		puts("A imagem fornecida não está no formato pgm");
		exit(2);
	}
	
	pio->tipo = getc(fp)-48;
	
    #ifdef __linux__
    fseek(fp,1, SEEK_CUR);
    #elif _WIN32
    fseek(fp,0, SEEK_CUR);
    #endif

	while((ch=getc(fp))=='#'){
		while( (ch=getc(fp))!='\n');
	}

	fseek(fp,-1, SEEK_CUR);

	fscanf(fp, "%d %d",&pio->width,&pio->height);
	if (ferror(fp)){ 
		perror(NULL);
		exit(3);
	}	
	fscanf(fp, "%d",&pio->maxval);
	fseek(fp,1, SEEK_CUR);

	pio->Data = (unsigned char*) malloc(pio->height * pio->width * sizeof(unsigned char));

	switch(pio->tipo){
		case 2:
			puts("Lendo imagem PGM (dados em texto)");
			for (int k=0; k < (pio->height * pio->width); k++){
				fscanf(fp, "%hhu", pio->Data+k);
			}
		break;	
		case 5:
			puts("Lendo imagem PGM (dados em binário)");
			fread(pio->Data,sizeof(unsigned char),pio->height * pio->width, fp);
		break;
		default:
			puts("Não está implementado");
	}
	
	fclose(fp);

}

void writePGMImage(struct Image *pio, char *filename){
	FILE *fp;
	char ch;

	if (!(fp = fopen(filename,"wb"))){
		perror("Erro.");
		exit(1);
	}

	fprintf(fp, "%s\n","P5");
	fprintf(fp, "%d %d\n",pio->width, pio->height);
	fprintf(fp, "%d\n", 255);

	fwrite(pio->Data, sizeof(unsigned char),pio->width * pio->height, fp);

	fclose(fp);

}


void viewPGMImage(struct Image *pio){
	printf("Tipo: %d\n",pio->tipo);
	printf("Dimensões: [%d %d]\n",pio->width, pio->height);
	printf("Max: %d\n",pio->maxval);

	for (int k=0; k < (pio->height * pio->width); k++){
		if (!( k % pio->width)) printf("\n");
		printf("%2hhu ",*(pio->Data+k));
	}	
	printf("\n");
}

void diretorios()
{
    // Inicio da medição do tempo
	clock_t begin, end;
	double time_total=0;
    begin = clock();
    DIR *d;
    struct dirent *dir;
    d = opendir("./images");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            //"." e ".." são os diretórios "atual" e "anterior" e foram
            // removido para evitar poluição na saída
            if(dir->d_name[0] != '.'){
                begin = clock();
                printf("%s\n", dir->d_name);

            }
        }
        closedir(d);
    }
    // Fim da medição do tempo  
    end = clock();
    time_total = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Tempo Total: %lf\n",time_total);
}