#include "header.h"
#include "inOutFichiers.h"

int lecture_P1(FILE* file_image, MATRICE * tab_pixels){

	return 1;
}

int lecture_P2(FILE* file_image, MATRICE * tab_pixels){

	return 1;
}

int lecture_P3(FILE* file_image, MATRICE * tab_pixels){
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

int lecture_P4(FILE* file_image, MATRICE * tab_pixels){

	return 1;
}

int lecture_P5(FILE* file_image, MATRICE * tab_pixels){

	return 1;
}

int lecture_P6(FILE* file_image, MATRICE * tab_pixels){

	return 1;
}

