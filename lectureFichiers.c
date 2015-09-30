#include "header.h"
#include "inOutFichiers.h"

int lecture_fichier(FILE* file_image, IMAGE * tab_pixels){
	int i = 0;
	
	// On lit le 'P' mais on le garde pas
	fgetc(file_image);

	// On lit le code ASCII du chiffre, donc moins 48 nous donne le chiffre
	tab_pixels->type = fgetc(file_image) - 48;

	fscanf(file_image,"%d %d",&tab_pixels->nb_col,&tab_pixels->nb_lig);

	fscanf(file_image,"%d",&tab_pixels->max_val);

	tab_pixels->mat = malloc(tab_pixels->nb_lig * sizeof(PIXEL));
	if(tab_pixels->mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau de pixels\n");
		return 0;
	}

	for (i=0; i<tab_pixels->nb_lig; i++){
		tab_pixels->mat[i] = malloc(tab_pixels->nb_col * sizeof(PIXEL));
		
		if(tab_pixels->mat[i] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau de pixels\n");
			for(i=i-1; i>=0; i--)
				free(tab_pixels->mat[i]);
			free(tab_pixels->mat);
			return 0;
		}
	}

// A completer Avec : https://fr.wikipedia.org/wiki/Portable_pixmap
	switch(tab_pixels->type){
		case 1:
		printf("\tFichier P1 : PBM ASCII\n");
		lecture_P1(file_image, tab_pixels);
		break;

		case 2:
		printf("\tFichier P2 : PGM ASCII\n");
		lecture_P2(file_image, tab_pixels);
		break;

		case 3:
		printf("\tFichier P3 : PPM ASCII\n");
		lecture_P3(file_image, tab_pixels);
		break;

		case 4:
		printf("\tFichier P4 : PBM Binaire\n");
		lecture_P4(file_image, tab_pixels);
		break;

		case 5:
		printf("\tFichier P5 : PGM Binaire\n");
		lecture_P5(file_image, tab_pixels);
		break;

		case 6:
		printf("\tFichier P6 : PPM Binaire\n");
		lecture_P6(file_image, tab_pixels);
		break;

		default: 
		printf("[X]\tNombre magique du fichier image non trouve\n");
		break;
	}

	return 1;
}


int lecture_P1(FILE* file_image, IMAGE * tab_pixels){

	return 1;
}

int lecture_P2(FILE* file_image, IMAGE * tab_pixels){

	return 1;
}

int lecture_P3(FILE* file_image, IMAGE * tab_pixels){
	int continuer = 1, i=0, j=0, col=0;
  
	do{
		fscanf(file_image, "%d %d %d", &tab_pixels->mat[i][j].r, &tab_pixels->mat[i][j].g, &tab_pixels->mat[i][j].b);

		if(feof(file_image)) 
			continuer = 0;

		j++;  
		if(j==col-1){
			j = 0;
			i++;
		}

	}while(continuer);

	return 1;
}

int lecture_P4(FILE* file_image, IMAGE * tab_pixels){

	return 1;
}

int lecture_P5(FILE* file_image, IMAGE * tab_pixels){

	return 1;
}

int lecture_P6(FILE* file_image, IMAGE * tab_pixels){

	return 1;
}

