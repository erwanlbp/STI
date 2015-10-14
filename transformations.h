#ifndef TRANSFORMATION
#define TRANSFORMATION

int binarisation (IMAGE *imageATransfo);

int negatif(IMAGE *image);
 
int symetrie_horizontale(IMAGE *copieImage);

int symetrie_verticale (IMAGE *imageATransfo);

int niveauGris(IMAGE *image);

int redimensionnement(IMAGE *image, const int argc, const char *argv[]);

int amelioration_du_contraste (IMAGE *imageATransfo);

int lissage (IMAGE *imageATransfo);

int laplacien (IMAGE *imageATransfo);

int alloc_tableau (IMAGE *imageAlloc);

void creation_masque (int *masque, int a, int b, int c, int d, int e, int f, int g, int h, int i);

void application_masque (IMAGE *image, IMAGE *copie, int *masque, int diviseur);

void gradientSimple(IMAGE *image);

void gradientSobel(IMAGE *image);

void detectionContoursSobel( IMAGE * image);

int detectionContoursLaplacien (IMAGE *imageATransfo);

int masqueCustom (IMAGE *image, const int argc, const char *argv[]);

#endif