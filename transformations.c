#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


int binarisation (IMAGE *imageATransfo){

	if(imageATransfo->type == 3 || imageATransfo->type == 6){
		niveauGris(imageATransfo);
	}

	if(imageATransfo->type != 1 && imageATransfo->type != 4){
		int lig, col, seuil = 127;

		//Double boucle pour parcourir tout le tableau
		for(lig = 0; lig<imageATransfo->nb_lig; lig++)
		{
			for(col=0; col<imageATransfo->nb_col; col++){
				//Si la valeur est en dessous du seuil il prend la valeur 0
				if (imageATransfo->mat[lig][col].r < seuil)
				{
					imageATransfo->mat[lig][col].r = 0;
					imageATransfo->mat[lig][col].g = 0;
					imageATransfo->mat[lig][col].b = 0;
				}
				//Si la valeur est en dessous du seuil il prend la valeur 255
				else {
					imageATransfo->mat[lig][col].r = 255;
					imageATransfo->mat[lig][col].g = 255;
					imageATransfo->mat[lig][col].b = 255;
				}
			}
			
		}
	}
	return 1;
}

int symetrie_verticale (IMAGE *imageATransfo){
	int i, j;
	PIXEL tmp;


	//Double boucle pour parcourir tout le tableau
	for (i = 0; i < imageATransfo->nb_col / 2; i++)
	{
		for (j = 0; j < imageATransfo->nb_lig; j++)
		{
			//On créer une variable temporaire pour échanger les valeurs des pixels
			tmp = imageATransfo->mat[i][j];
			imageATransfo->mat[i][j] = imageATransfo->mat[imageATransfo->nb_col - i + 1][j];
			imageATransfo->mat[imageATransfo->nb_col - i + 1][j] = tmp;
		}
	}
	return 1;
}

int negatif(IMAGE *image){
	int lig,col;
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			image->mat[lig][col].r = 255 - (image->mat[lig][col].r);
			image->mat[lig][col].g = 255 - (image->mat[lig][col].g);
			image->mat[lig][col].b = 255 - (image->mat[lig][col].b);
		}
	}
	return 1;
}


int niveauGris(IMAGE *image){
	if(image->type == 3 || image->type == 6){
		int gris, lig, col;
		for(lig=0;lig<image->nb_lig;lig++){
			for(col=0;col<image->nb_col;col++){
				gris = (0.3*(image->mat[lig][col].r)) + (0.59*(image->mat[lig][col].g))+(0.11*(image->mat[lig][col].b));
				image->mat[lig][col].r = gris;
				image->mat[lig][col].g = gris;
				image->mat[lig][col].b = gris;
			}
		}
	}
	return 1;
}


// Fonction qui fait la symétrie horizontale par rapport à l'axe central vertical
int symetrie_horizontale(IMAGE *image){
	int lig, col;
	PIXEL tmp;
	//Double boucle for pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col< image->nb_col /2;col++){
			// On met dans une variable temporaire
			tmp=image->mat[lig][col];
			// On met dans le pixel actuel le pixel symétrique par raport à l'axe central vertical
			image->mat[lig][col] = image->mat[lig][image->nb_col -col-1];
			// On met dans le pixel symétrique les valeurs dans le pixel temporaire
			image->mat[lig][ image->nb_col -col-1]	=tmp;
		}
	}
	return 1;
}


int redimensionnement(IMAGE *image, int absEntree, int ordEntree, int absSortie, int ordSortie){
	int lig, col, tmp;

	//Vérification de l'abscisse d'entrée
	if (absEntree<0){
		absEntree = 0;
	}
	if(absEntree>image->nb_col){
		absEntree = image->nb_col;
	}

	//Vérification de l'ordonnée d'entrée
	if (ordEntree<0){
		ordEntree = 0;
	}
	if(ordEntree>image->nb_lig){
		ordEntree = image->nb_lig;
	}

	//Vérification de l'abscisse de sortie
	if (absSortie<0){
		absSortie = 0;
	}
	if(absSortie>image->nb_col){
		absSortie = image->nb_col;
	}

	//Vérification de l'ordonnée de sortie
	if (ordSortie<0){
		ordSortie = 0;
	}
	if(ordSortie>image->nb_lig){
		ordSortie = image->nb_lig;
	}

	//Remet les valeurs comme si on faisait un "crop" de en haut à gauche vers en bas à droite
	if(absSortie<absEntree){
		tmp = absSortie;
		absSortie = absEntree;
		absEntree = tmp;
	}
	if(ordSortie<ordEntree){
		tmp = ordSortie;
		ordSortie = ordEntree;
		ordEntree = tmp;
	}

	
	IMAGE copieImage;
	copieImage.mat = NULL;
	copieImage.nb_lig = image->nb_lig;
	copieImage.nb_col = image->nb_col;
	copieImage.type = image->type;
	copieImage.max_val = image->max_val;

	copieImage.mat = malloc(copieImage.nb_lig * sizeof(PIXEL));

	//Vérification de l'allocation de la première dimension du nouveau tableau
	if(copieImage.mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau copieImage de pixels dans redimensionnement\n");
		return 0;
	}

	// Création de la deuxième dimension du nouveau tableau
	for(lig=0; lig< copieImage.nb_lig; lig++){
		copieImage.mat[lig]=malloc((copieImage.nb_col) * sizeof(PIXEL));
		//Vérification de l'allocation de la deuxième dimension du nouveau
		if(copieImage.mat[lig]==NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau copieImage de pixels dans redimensionnement\n");
			for(lig=lig-1; lig>=0; lig--){
				free(copieImage.mat[lig]);
			}
			free(copieImage.mat);
			return 0;
		}
	}// Fin de la copie de l'image reçue



	//Copie des valeurs de image dans copieImage
	for(lig=0;lig<copieImage.nb_lig;lig++){
		for(col=0;col<copieImage.nb_col;col++){
			copieImage.mat[lig][col]=image->mat[lig][col];
		}
	}


	//Libération de la mémoire de l'image reçue
	vider_tab_pixels(image);
	//Réallocation d'un nouveau tableau de taille réduite à image
	image->mat=NULL;
	image->nb_lig = ordSortie-ordEntree;
	image->nb_col = absSortie-absEntree;
	image->type = copieImage.type;
	image->max_val = copieImage.max_val;
	image->mat = malloc((image->nb_lig)* sizeof(PIXEL));


	//Vérification de l'allocation de la première dimension du nouveau tableau
	if(image->mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau de pixels dans redimensionnement\n");
		return 0;
	}

	// Création de la deuxième dimension du nouveau tableau
	for(lig=0; lig< image->nb_lig +1; lig++){
		image->mat[lig]=malloc((image->nb_col +1) * sizeof(PIXEL));
		//Vérification de l'allocation de la deuxième dimension du nouveau
		if(image->mat[lig]==NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau de pixels dans redimensionnement\n");
			for(lig=lig-1; lig>=0; lig--){
				free(image->mat[lig]);
			}
			free(image->mat);
			return 0;
		}
	}//Fin de la réallocation du nouveau tableau de taille réduite à image


	// Affectation des valeurs de copieImage dans image
	for(lig=ordEntree; lig<=ordSortie; lig++){
		for(col=absEntree; col<=absSortie;col++){
			image->mat[lig-ordEntree][col-absEntree] = copieImage.mat[lig][col];
		}
	}

	//Vidage copieImage
	vider_tab_pixels(&copieImage);
	return 0;

}