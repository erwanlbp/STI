#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


void binarisation (IMAGE *imageATransfo){
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


void negatif(IMAGE *copieImage){
	int lig,col;
	for(lig=0;lig<copieImage->nb_lig;lig++){
		for(col=0;col<copieImage->nb_col;col++){
			copieImage->mat[lig][col].r = 255 - (copieImage->mat[lig][col].r);
			copieImage->mat[lig][col].g = 255 - (copieImage->mat[lig][col].g);
			copieImage->mat[lig][col].b = 255 - (copieImage->mat[lig][col].b);
		}
	}
}
