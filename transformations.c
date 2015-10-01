#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


void binarisation (IMAGE *imageATransfo){

	if(imageATransfo->type == 3 || imageATransfo->type == 6){
		niveauGris(imageATransfo);
	}

	if(imageATransfo->type != 1 && imageATransfo->type != 4){
		int i, j, seuil = 127;

		//Double boucle pour parcourir tout le tableau
		for (i = 0; i < imageATransfo->nb_lig; i++)
		{
			for (j = 0; j < imageATransfo->nb_col; j++)
			{
				if (imageATransfo->mat[i][j].r < seuil)
				{
					(imageATransfo->mat[i][j].r) = 0;
					(imageATransfo->mat[i][j].g) = 0;
					(imageATransfo->mat[i][j].b) = 0;
				}
				else {
					(imageATransfo->mat[i][j].r) = 255;
					(imageATransfo->mat[i][j].g) = 255;
					(imageATransfo->mat[i][j].b) = 255;
				}
			}
		}
	}
}

void negatif(IMAGE *image){
	int lig,col;
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			image->mat[lig][col].r = 255 - (image->mat[lig][col].r);
			image->mat[lig][col].g = 255 - (image->mat[lig][col].g);
			image->mat[lig][col].b = 255 - (image->mat[lig][col].b);
		}
	}
}

void niveauGris(IMAGE *image){
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
}