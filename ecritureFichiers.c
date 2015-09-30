#include "header.h"
#include "inOutFichiers.h"
  
int ecriture_P1(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255]){

	return 1;
}

int ecriture_P2(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255]){

	return 1;
}

int ecriture_P3(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	char chemin[255] = "";
	sprintf(chemin,"%s_%s",transformation,cheminImage);

	FILE* fichier = fopen(chemin,"w");
	if(fichier == NULL){
		printf("[X]\tErreur ouverture fichier ecriture\n");
	}
	fprintf(fichier, "P3\n%d %d\n%d", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val);


	return 1; 
}

int ecriture_P4(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255]){

	return 1;
}

int ecriture_P5(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255]){

	return 1;
}

int ecriture_P6(FILE* file_image, IMAGE * tab_pixels, const char cheminImage[255]){

	return 1;
}

