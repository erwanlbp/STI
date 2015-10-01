#include "header.h"
#include "inOutFichiers.h"

FILE* ouverture_lecture_fichier_image(const int *argc, char const *argv[], char nomImage[255], char transformation[255]){

	char cheminImage[255] = "";

	sprintf(nomImage,"test.ppm");

	// Variable contenant le chemin du fichier, par defaut "test.ppm"
	sprintf(cheminImage,"Images/%s","test.ppm");

	// Variable contenant la transformation recue en argument, par defaut "base"	
	sprintf(transformation,"%s","base");

	// On teste si on a recu un chemin de fichier
	if (*argc >= 2){

		// On sauvegarde le chemin de l'image	
		sprintf(nomImage,"%s",argv[1]);

		// On va chercher l'image
		sprintf(cheminImage,"Images/%s",nomImage);

		//On affiche le chemin qu'on a recu
		printf("[O]\tUn chemin de fichier a ete trouve : %s\n",cheminImage);

		if(*argc >= 3){ 
			sprintf(transformation,"%s",argv[2]);
			printf("[O]\tTransformation trouvee : %s\n", transformation);
		}
		else
			printf("[X]\tAucune transformation demandee, transformation par defaut : %s\n", transformation);
	}
	else{ //Sinon on dit qu'on a rien recu et on donne le chemin par defaut
		printf("[X]\tAucun chemin de fichier trouve, chemin par defaut : %s\n",cheminImage);
		printf("[X]\tAucune transformation demandee, transformation par defaut : %s\n", transformation);
	}

	// On ouvre le fichier de l'image
	FILE* fichier = NULL;
	fichier = fopen(cheminImage,"r");

	if(fichier != NULL)
		printf("[O]\tOuverture du fichier image reussie\n");
	else 
		printf("[X]\tOuverture du fichier image rate\n");

	return fichier;
}

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
	int continuer = 1, lig=0, col=0;

	do{
		fscanf(file_image, "%d %d %d", &tab_pixels->mat[lig][col].r, &tab_pixels->mat[lig][col].g, &tab_pixels->mat[lig][col].b);

		if(feof(file_image)) 
			continuer = 0;

		col++;  
		if(col == tab_pixels->nb_col){
			col = 0;
			lig++;
		}
		if(lig == tab_pixels->nb_lig)
			continuer = 0;

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

