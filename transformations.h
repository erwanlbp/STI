#ifndef TRANSFORMATION
#define TRANSFORMATION

int binarisation (IMAGE *imageATransfo);

int negatif(IMAGE *image);

int symetrie_horizontale(IMAGE *copieImage);

int symetrie_verticale (IMAGE *imageATransfo);

int niveauGris(IMAGE *image);

int redimensionnement(IMAGE *image, int absEntree, int ordEntree, int absSortie, int ordSortie);

#endif