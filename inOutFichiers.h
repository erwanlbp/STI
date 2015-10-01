#ifndef DEF_INOUTFICHIERS
#define DEF_INOUTFICHIERS

// Pour ouvrir le fichier image
FILE* ouverture_lecture_fichier_image(const int *argc, char const *argv[], char cheminImage[255], char transformation[255]);
int lecture_fichier(FILE* file_image, IMAGE * tab_pixels);

FILE* ouverture_ecriture_fichier_image(char cheminImage[255], char transformation[255]);
int ecriture_fichier(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[255]);

int lecture_P1(FILE* file_image, IMAGE * tab_pixels);
int lecture_P2(FILE* file_image, IMAGE * tab_pixels);
int lecture_P3(FILE* file_image, IMAGE * tab_pixels);
int lecture_P4(FILE* file_image, IMAGE * tab_pixels);
int lecture_P5(FILE* file_image, IMAGE * tab_pixels);
int lecture_P6(FILE* file_image, IMAGE * tab_pixels);

int ecriture_P1(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P2(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P3(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P4(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P5(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P6(FILE* fichier, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);

#endif