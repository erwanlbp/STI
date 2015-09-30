#include "header.h"
#include "inOutFichiers.h"

int ecriture_fichier(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[255]){

	switch(tab_pixels->type){
		case 1:
		printf("\tFichier P1 : COMPLETE\n");
		ecriture_P1(file_image, tab_pixels, cheminImage, transformation);
		break;

		case 2:
		printf("\tFichier P2 : COMPLETE\n");
		ecriture_P2(file_image, tab_pixels, cheminImage, transformation);
		break;

		case 3:
		printf("\tFichier P3 : COMPLETE\n");
		ecriture_P3(file_image, tab_pixels, cheminImage, transformation);
		break;

		case 4:
		printf("\tFichier P4 : COMPLETE\n");
		ecriture_P4(file_image, tab_pixels, cheminImage, transformation);
		break;

		case 5:
		printf("\tFichier P5 : COMPLETE\n");
		ecriture_P5(file_image, tab_pixels, cheminImage, transformation);
		break;

		case 6:
		printf("\tFichier P6 : COMPLETE\n");
		ecriture_P6(file_image, tab_pixels, cheminImage, transformation);
		break;

		default: 
		printf("[X]\tNombre magique du fichier image inconnu\n");
		break;
	}
	
	return 1;
}

int ecriture_P1(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P2(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P3(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	char chemin[255] = "";
	sprintf(chemin,"%s_%s",transformation,cheminImage);

	FILE* fichier = fopen(chemin,"w");
	if(fichier == NULL){
		printf("[X]\tErreur ouverture fichier ecriture\n");
	}
	fprintf(fichier, "P3\n%d %d\n%d", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){
			if(col % 70 > 65)
				fprintf(fichier,"\n");
			else
				fprintf(fichier,"\t");
			fprintf(fichier, "%d %d %d", tab_pixels->mat[lig][col].r, tab_pixels->mat[lig][col].g, tab_pixels->mat[lig][col].b);
		}
		printf("\n");
	}

	fclose(fichier);

	return 1; 
}

int ecriture_P4(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P5(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P6(FILE* file_image, const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

