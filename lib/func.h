#include "../lib/pgm.h"

void filtro_media(struct Image *img, struct Image *out, int n);
void quantizar(struct Image *img, struct Image *out, int N);
void encontrarNome(char *nameinput, char *nameoutput);
int applyscm(struct Image *img, struct Image *qtzd, int N, char *final);
unsigned char *computeSCM(unsigned char *Data1, unsigned char *Data2, int columns, int rows, int levels);
void fprintSCM(FILE *file, unsigned char *scmMatrix, int quantizationLevels);