#ifndef PGM_H
#define PGM_H
#define OUTPUT_DIR "./filtered_images"

struct pgm{
	int tipo;
	int c;
	int r;
	int mv;
	unsigned char *pData;
};

struct pgm *readPGMFile(char *);
void writePGMImage(struct pgm *pio, char *filename);
void viewPGMImage(struct pgm *pio);

#endif