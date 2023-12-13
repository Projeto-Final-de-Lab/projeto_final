#include "../lib/pgm.h"

void filtro_media(struct Image *img, struct Image *out, int n);
void quantizar(struct Image *img, struct Image *out, int N);
void encontrarNome(char *nameinput, char *nameoutput);
int applyscm(struct Image *img, struct Image *qtzd, int N, char *final, FILE *fptr);
void writeCSVHeader(FILE *file, int quantizationLevels);