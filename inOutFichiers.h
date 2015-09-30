#ifndef DEF_INOUTFICHIERS
#define DEF_INOUTFICHIERS

int lecture_fichier(FILE* file_image, IMAGE * tab_pixels);

int lecture_P1(FILE* file_image, IMAGE * tab_pixels);
int lecture_P2(FILE* file_image, IMAGE * tab_pixels);
int lecture_P3(FILE* file_image, IMAGE * tab_pixels);
int lecture_P4(FILE* file_image, IMAGE * tab_pixels);
int lecture_P5(FILE* file_image, IMAGE * tab_pixels);
int lecture_P6(FILE* file_image, IMAGE * tab_pixels);

int ecriture_P1(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P2(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P3(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P4(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P5(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);
int ecriture_P6(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]);

#endif