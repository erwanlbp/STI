#ifndef TRANSFORMATION
#define TRANSFORMATION

int binarisation (IMAGE *imageATransfo);

int negatif(IMAGE *image);

int symetrie_horizontale(IMAGE *copieImage);

int symetrie_verticale (IMAGE *imageATransfo);

int niveauGris(IMAGE *image);

int amelioration_du_contraste (IMAGE *imageATransfo);

int lissage (IMAGE *imageATransfo);

#endif