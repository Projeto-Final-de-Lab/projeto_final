#ifndef PGM_H
#define PGM_H
#define OUTPUT_DIR "./filtered_images"

struct Image {
    int tipo;
    int width;
    int height;
    int maxval;
    unsigned char **Data;
};

void readPGMImage(struct Image *, char *);
void viewPGMImage(struct Image *);
void writePGMImage(struct Image *, char *);
void createOutputDirectory();

#endif