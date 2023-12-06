/*
 * C Program to List Files in Directory
	https://www.sanfoundry.com/c-program-list-files-directory/
 */
#include <dirent.h>
#include <stdio.h>
#include <time.h>
 
int main(void)
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
    return(0);
}		