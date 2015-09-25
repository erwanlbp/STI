#ifndef DEF_HEADER
#define DEF_HEADER

#include <stdio.h>
#include <stdlib.h>


/*Format fichiers image PPM : 
-----------------------
P3
# Le P3 signifie que les couleurs sont en ASCII, 
# par 3 colonnes et 2 lignes,
 3 2
# ayant 255 pour valeur maximum, et qu'elles sont en RGB. 
255
255   0   0     0 255   0     0   0 255
255 255   0   255 255 255     0   0   0
*/


// Format lancement programme : 
// ./STI [chemin image = img_test.ppm] [transformation = Aucune]
// Donc si on met pas d'argument au programme il chargera l'image de test et fera rien



typedef struct PIXEL PIXEL;
struct PIXEL
{
	int r;
	int g;
	int b;
};

// Pour ecrire une ligne de séparation dans le terminal
void ligne_separation(char separateur);

// Pour ouvrir le fichier image
FILE* ouverture_image(int argc, char const *argv[]);

//Pour effacer l'ecran selon l'OS
void effacer_ecran();

// Regarde si le fichier est bien constitue
int test_validite_fichier(FILE *file_image);


int lecture_fichier(FILE* file_image,PIXEL **tab_pixels,int *nb_col, int *nb_lig, int *max_val);
void afficher_tab_pixels(PIXEL **tab_pixels, int nb_col, int nb_lig);

#endif