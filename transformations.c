#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


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