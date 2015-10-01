#ifndef DEF_INOUTFICHIERS
#define DEF_INOUTFICHIERS

/**   
 * \file inOutFichiers.h
 * \brief Header des fichiers lectureFichiers.c et ecritureFichiers.c
 * \author Le Batard--Polès Erwan
 * \version 42
 * Rassemble les prototypes des fonctions de lecture et ecriture des fichiers
 */

// Pour ouvrir le fichier image en lecture
FILE* ouverture_lecture_fichier_image(const int *argc, char const *argv[], char cheminImage[255], char transformation[255]);
// Pour scanner les caracteristiques de la matrice et
// appeler les fonctions de lecture des fichiers en fonction du type du fichier
int lecture_fichier(FILE* file_image, IMAGE * tab_pixels);

//Pour ouvrir le fichier de sauvegarde de la transformation de l'image en ecriture
FILE* ouverture_ecriture_fichier_image(char cheminImage[255], char transformation[255]);
//Pour appeler les fonctions d'ecriture du fichier en fonction du type du fichier
int ecriture_fichier(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[255]);

// Fonctions de lecture, P<i> pour le type de fichier
int lecture_P1(FILE* file_image, IMAGE * tab_pixels); // PBM ASCII
int lecture_P2(FILE* file_image, IMAGE * tab_pixels); // PGM ASCII
int lecture_P3(FILE* file_image, IMAGE * tab_pixels); // PPM ASCII
int lecture_P4(FILE* file_image, IMAGE * tab_pixels); // PBM Binaire
int lecture_P5(FILE* file_image, IMAGE * tab_pixels); // PGM Binaire
int lecture_P6(FILE* file_image, IMAGE * tab_pixels); // PPM Binaire

// Fonctions d'ecriture, P<i> pour le type de fichier
int ecriture_P1(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PBM ASCII
int ecriture_P2(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PGM ASCII
int ecriture_P3(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PPM ASCII
int ecriture_P4(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PBM Binaire
int ecriture_P5(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PGM Binaire
int ecriture_P6(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]); // PPM Binaire

#endif