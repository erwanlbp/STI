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

void creation_masque (int *masque, const int a, const int b, const int c, const int d, const int e, const int f, const int g, const int h, const int i);

void application_masque (IMAGE *image, IMAGE *copie, int *masque, int diviseur);

void gradientSimple(IMAGE *image);

void gradientSobel(IMAGE *image);

void detectionContoursSobel( IMAGE * image);

int detectionContoursLaplacien (IMAGE *imageATransfo);

int reductionBruit(IMAGE *image);

int triTab (int *masque, int taille);

int masqueCustom (IMAGE *image, const int argc, const char *argv[]);

void creation_Copie(IMAGE *image, IMAGE *copie);

#endif