#ifndef DEF_HEADER
#define DEF_HEADER
 
/**  
 * \file header.h
 * \brief Header principale
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Création des deux structures du programme et des fonctions principales
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//Idees de plus : 
// Fonction de test si le fichier image est valide, bien forme



// Format lancement programme : 
// ./STI [chemin image = img_test.ppm] [transformation = Aucune]
// Donc si on met pas d'argument au programme il chargera l'image de test et fera rien

/**
 * \struct PIXEL 
 * \brief Représentation d'un pixel
 *
 * PIXEL est une structure composée de 3 entiers.
 * Les 3 entiers représentent les 3 couleurs primaires.
 * r : Rouge
 * v : Vert
 * b : Bleu
 */
typedef struct PIXEL PIXEL;
struct PIXEL
{
	int r; /*!< Rouge */
	int g; /*!< Vert */
	int b; /*!< Bleu */
};

typedef struct IMAGE IMAGE;
struct IMAGE
{
	PIXEL ** mat;
	int type;
	int nb_lig;
	int nb_col;
	int max_val;
};

// Pour ecrire une ligne de séparation dans le terminal
void ligne_separation(const char separateur);

//Pour effacer l'ecran selon l'OS
void effacer_ecran();

// Pour affichers les valeurs contenues dans la matrice de pixels
void afficher_tab_pixels(IMAGE * tab);

// Pour liberer la memoire allouee a la matrice de pixels
void vider_tab_pixels(IMAGE * tab);

#endif