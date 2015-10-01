#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


IMAGE negatif(IMAGE image){
	int lig,col;
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			image->mat[lig][col].r = 255 - image->mat[lig][col].r;
			image->mat[lig][col].g = 255 - image->mat[lig][col].g;
			image->mat[lig][col].b = 255 - image->mat[lig][col].b;
		}
	}
	return image;
}