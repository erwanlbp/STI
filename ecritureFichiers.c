#include "header.h"
#include "inOutFichiers.h"

int ecriture_fichier(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[255]){

	switch(tab_pixels->type){
		case 1:	ecriture_P1(tab_pixels, cheminImage, transformation); break;
		case 2:	ecriture_P2(tab_pixels, cheminImage, transformation); break;
		case 3:	ecriture_P3(tab_pixels, cheminImage, transformation); break;
		case 4:	ecriture_P4(tab_pixels, cheminImage, transformation); break;
		case 5:	ecriture_P5(tab_pixels, cheminImage, transformation); break;
		case 6:	ecriture_P6(tab_pixels, cheminImage, transformation); break;
		default: 
		printf("[X]\tNombre magique du fichier image inconnu\n");
		break;
	}
	
	return 1;
}

int ecriture_P1(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P2(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P3(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

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
		fprintf(fichier,"\n");
	}

	fclose(fichier);

	return 1; 
}

int ecriture_P4(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P5(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P6(const IMAGE * tab_pixels, const char cheminImage[255], const char transformation[100]){

	return 1;
}

