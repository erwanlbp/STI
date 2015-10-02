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