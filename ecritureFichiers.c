#include "header.h"
#include "inOutFichiers.h"

FILE* ouverture_ecriture_fichier_image(char nomImage[255], char transformation[255]){
	char chemin[255] = "";

	sprintf(chemin,"Images/%s_%s",transformation,nomImage);
 
	FILE* fichier = fopen(chemin,"w");
	if(fichier == NULL){
		printf("[X]\tErreur ouverture fichier ecriture\n");
	}

	if(fichier != NULL)
		printf("[O]\tOuverture du fichier d'ecriture reussie\n");
	else 
		printf("[X]\tOuverture du fichier d'ecriture rate\n");

	return fichier;
}

int ecriture_fichier(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[255]){
	 
	switch(tab_pixels->type){
		case 1:	ecriture_P1(fichier, tab_pixels, nomImage, transformation); break;
		case 2:	ecriture_P2(fichier, tab_pixels, nomImage, transformation); break;
		case 3:	ecriture_P3(fichier, tab_pixels, nomImage, transformation); break;
		case 4:	ecriture_P4(fichier, tab_pixels, nomImage, transformation); break;
		case 5:	ecriture_P5(fichier, tab_pixels, nomImage, transformation); break;
		case 6:	ecriture_P6(fichier, tab_pixels, nomImage, transformation); break;
		default: 
		printf("[X]\tNombre magique du fichier image inconnu\n");
		break;
	}
	
	return 1;
} 

int ecriture_P1(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	fprintf(fichier, "P1\n%d %d\n", tab_pixels->nb_col, tab_pixels->nb_lig); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 			
			fprintf(fichier, "%d", tab_pixels->mat[lig][col].r);
			if(col % 70 > 60)
				fprintf(fichier,"\n");
			else
				fprintf(fichier," ");
		}
		fprintf(fichier,"\n");
	}

	fclose(fichier);
	return 1;
}

int ecriture_P2(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P3(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){
		
	fprintf(fichier, "P3\n%d %d\n%d\n", tab_pixels->nb_col, tab_pixels->nb_lig, tab_pixels->max_val); 

	int lig,col;
	for(lig=0; lig<tab_pixels->nb_lig; lig++){
		for(col=0; col<tab_pixels->nb_col; col++){ 			
			fprintf(fichier, "%d %d %d", tab_pixels->mat[lig][col].r, tab_pixels->mat[lig][col].g, tab_pixels->mat[lig][col].b);
			if(col % 70 > 60)
				fprintf(fichier,"\n");
			else
				fprintf(fichier," ");
		}
		fprintf(fichier,"\n");
	}

	fclose(fichier);

	return 1; 
}

int ecriture_P4(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P5(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	return 1;
}

int ecriture_P6(FILE* fichier, const IMAGE * tab_pixels, const char nomImage[255], const char transformation[100]){

	return 1;
}

