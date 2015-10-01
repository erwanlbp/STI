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

int symetrie_horizontale(IMAGE *image){
	int lig, col;
	PIXEL tmp;
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col< image->nb_col /2;col++){

			tmp=image->mat[lig][col];
			image->mat[lig][col] = image->mat[lig][image->nb_col -col-1];
			image->mat[lig][ image->nb_col -col-1]	=tmp;
		}
	}
	return 1;
}