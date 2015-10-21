#ifndef TRANSFORMATION
#define TRANSFORMATION

/**  
 * \file Lecture trasnformation.h
 * \brief Prototypes des fonctions de transformation
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Ensemble des prototypes pour les fonctions de transformation qui sont dans transformation.c
 */

void binarisation (IMAGE *imageATransfo);

void negatif(IMAGE *image);
 
void symetrie_horizontale(IMAGE *copieImage);

void symetrie_verticale (IMAGE *imageATransfo);

void niveauGris(IMAGE *image);

int redimensionnement(IMAGE *image, const int argc, const char *argv[]);

void amelioration_du_contraste (IMAGE *imageATransfo);

int lissage (IMAGE *imageATransfo);

int laplacien (IMAGE *imageATransfo);

int alloc_tableau (IMAGE *imageAlloc);

void creation_masque (int *masque, const int a, const int b, const int c, const int d, const int e, const int f, const int g, const int h, const int i);

void application_masque (IMAGE *image, IMAGE *copie, const int *masque, int diviseur);

int gradient( IMAGE *image, const char *transformation);

int detectionContoursSobel( IMAGE * image);

int detectionContoursLaplacien (IMAGE *imageATransfo);

void reductionBruit(IMAGE *image);

void triTab (int *masque);

int masqueCustom (IMAGE *image, const int argc, const char *argv[]);

int creation_Copie(IMAGE *image, IMAGE *copie);

#endif