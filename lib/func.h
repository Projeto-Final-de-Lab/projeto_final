#include "../lib/pgm.h"

void filtro_media(struct Image *, struct Image *, int);
void quantizar(struct Image *, struct Image *, int);
void encontrarNome(char *, char *);
unsigned char* criarSCM(struct Image *, struct Image *, int);
void imprimirSCM(FILE *, unsigned char *, int , char *);
void writeCSVHeader(FILE *, int);
