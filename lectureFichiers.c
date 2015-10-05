#include "header.h"
#include "inOutFichiers.h"

/**  
 * \file Lecture fichier.c
 * \brief Lecture des fichiers P1 à P6
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Ensemble des fonctions de lecture des fichiers en fonction de leur type
 */


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

	// On lit le nombre de colonnes et de lignes
	fscanf(file_image,"%d %d",&tab_pixels->nb_col,&tab_pixels->nb_lig);

	// On alloue la premiere dimension
	tab_pixels->mat = malloc(tab_pixels->nb_lig * sizeof(PIXEL));
	if(tab_pixels->mat == NULL){ 
		// Si il y a une erreur on met un message et quitte la fonction
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau de pixels\n");
		return 0;
	}

	// On alloue la deuxieme dimension
	for (i=0; i<tab_pixels->nb_lig; i++){
		tab_pixels->mat[i] = malloc(tab_pixels->nb_col * sizeof(PIXEL));
		
		// Si il y a une erreur on libere la memoire qu'on a allouee avant
		if(tab_pixels->mat[i] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau de pixels\n");
			for(i=i-1; i>=0; i--)
				free(tab_pixels->mat[i]);
			free(tab_pixels->mat);
			return 0;
		}
	}

	// On appelle les differentes fonctions selon le type d'image
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

	// Comme les valeurs des pixels sont soit 1 soit 0
	// La valeur max n'est pas mise dans le fichier mais quand meme
	tab_pixels->max_val = 1;

	int continuer = 1, lig=0, col=0;

	do{
		// On lit un entier, qu'on stocke dans les 3 sous variable du pixel
		fscanf(file_image, "%d", &tab_pixels->mat[lig][col].r);
		tab_pixels->mat[lig][col].g = tab_pixels->mat[lig][col].r;
		tab_pixels->mat[lig][col].b = tab_pixels->mat[lig][col].r;

		// Si on arrive à la fin du fichier on arrete
		if(feof(file_image)) 
			continuer = 0;

		// On incremente l'indice des colonnes 
		col++;  
		// Si on a atteint le nombre de colonnes on la remet à 0 et on increment la ligne
		if(col == tab_pixels->nb_col){
			col = 0;
			lig++;
		}

		// On arrete de lire si le fichier contient plus de pixels que ce qu'on a lu au debut
		if(lig == tab_pixels->nb_lig)
			continuer = 0;
		
	}while(continuer);

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

int lecture_P2(FILE* file_image, IMAGE * tab_pixels){

	//On lit la valeur maximum de chaque pixel
	fscanf(file_image,"%d",&tab_pixels->max_val);

	int continuer = 1, lig=0, col=0;

	do{
		// On lit un entier, qu'on stocke dans les 3 sous variable du pixel
		fscanf(file_image, "%d", &tab_pixels->mat[lig][col].r);
		tab_pixels->mat[lig][col].g = tab_pixels->mat[lig][col].r;
		tab_pixels->mat[lig][col].b = tab_pixels->mat[lig][col].r;

		// Si on arrive à la fin du fichier on arrete
		if(feof(file_image)) 
			continuer = 0;

		// On incremente l'indice des colonnes 
		col++;  
		// Si on a atteint le nombre de colonnes on la remet à 0 et on increment la ligne
		if(col == tab_pixels->nb_col){
			col = 0;
			lig++;
		}

		// On arrete de lire si le fichier contient plus de pixels que ce qu'on a lu au debut
		if(lig == tab_pixels->nb_lig)
			continuer = 0;

	}while(continuer);

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

int lecture_P3(FILE* file_image, IMAGE * tab_pixels){

	//On lit la valeur maximum de chaque pixel
	fscanf(file_image,"%d",&tab_pixels->max_val);

	int continuer = 1, lig=0, col=0;

	do{
		// On lit 3 entiers, un pour chaque composantes du pixel
		fscanf(file_image, "%d %d %d", &tab_pixels->mat[lig][col].r, &tab_pixels->mat[lig][col].g, &tab_pixels->mat[lig][col].b);

		// Si on arrive à la fin du fichier on arrete
		if(feof(file_image)) 
			continuer = 0;

		// On incremente l'indice des colonnes 
		col++;  
		// Si on a atteint le nombre de colonnes on la remet à 0 et on increment la ligne
		if(col == tab_pixels->nb_col){
			col = 0;
			lig++;
		}

		// On arrete de lire si le fichier contient plus de pixels que ce qu'on a lu au debut
		if(lig == tab_pixels->nb_lig)
			continuer = 0;

	}while(continuer);

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

int lecture_P4(FILE* file_image, IMAGE * tab_pixels){

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

int lecture_P5(FILE* file_image, IMAGE * tab_pixels){

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

int lecture_P6(FILE* file_image, IMAGE * tab_pixels){

	// On retourne 1 pour dire que la fonction s'est bien passe
	return 1;
}

