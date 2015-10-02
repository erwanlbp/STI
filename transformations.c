#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"


int binarisation (IMAGE *imageATransfo){

	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
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

int negatif(IMAGE *image){
	int lig,col;

	//Double boucle pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			//On applique la formule pour changer la valeur de chaque composante
			image->mat[lig][col].r = 255 - (image->mat[lig][col].r);
			image->mat[lig][col].g = 255 - (image->mat[lig][col].g);
			image->mat[lig][col].b = 255 - (image->mat[lig][col].b);
		}
	}
	return 1;
}

int niveauGris(IMAGE *image){
	//On effectue la transformation seulement si l'image est en couleur
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

int symetrie_verticale (IMAGE *imageATransfo){
	int lig, col;
	PIXEL tmp;

	//Double boucle pour parcourir tout le tableau
	for (lig = 0; lig < imageATransfo->nb_lig / 2; lig++)
	{
		for (col = 0; col < imageATransfo->nb_col; col++)
		{
			//On creer une variable temporaire pour echanger les valeurs des pixels
			tmp = imageATransfo->mat[lig][col];
			imageATransfo->mat[lig][col] = imageATransfo->mat[imageATransfo->nb_lig - lig - 1][col];
			imageATransfo->mat[imageATransfo->nb_lig - lig - 1][col] = tmp;
		}
	}
	return 1;
}

int symetrie_horizontale(IMAGE *image){
	int lig, col;
	PIXEL tmp;
	//Double boucle for pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col< image->nb_col /2;col++){
			// On met dans une variable temporaire
			tmp=image->mat[lig][col];
			// On met dans le pixel actuel le pixel symetrique par raport a l'axe central vertical
			image->mat[lig][col] = image->mat[lig][image->nb_col -col-1];
			// On met dans le pixel symetrique les valeurs dans le pixel temporaire
			image->mat[lig][ image->nb_col -col-1]	=tmp;
		}
	}
	return 1;
}


int redimensionnement(IMAGE *image, const int argc, const char *argv[]){
	int absEntree=0, ordEntree=0, absSortie=image->nb_col-1, ordSortie=image->nb_lig-1;
	int lig, col, tmp;
	if(argc <=3){
		printf("[X]\tRien n'a ete selectionne, l'image ne sera pas redimensionnee\n");
		return 1;
	}

	if(argc>=4) 
		absEntree = atoi(argv[3]);
	if(argc>=5) 
		ordEntree = atoi(argv[4]);
	if(argc>=6) 
		absSortie = atoi(argv[5]);
	if(argc>=7) 
		ordSortie = atoi(argv[6]);

	//Verification de l'abscisse d'entree
	if (absEntree<0)
		absEntree = 0;
	if(absEntree>=image->nb_col)
		absEntree = image->nb_col-1;

	//Verification de l'ordonnee d'entree
	if (ordEntree<0)
		ordEntree = 0;
	if(ordEntree>=image->nb_lig)
		ordEntree = image->nb_lig-1;

	//Verification de l'abscisse de sortie
	if (absSortie<0)
		absSortie = 0;
	if(absSortie>=image->nb_col)
		absSortie = image->nb_col-1;

	//Verification de l'ordonnee de sortie
	if (ordSortie<0)
		ordSortie = 0;
	if(ordSortie>=image->nb_lig)
		ordSortie = image->nb_lig-1;

	//Remet les valeurs comme si on faisait un "crop" de en haut a gauche vers en bas a droite
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

	//Verification de l'allocation de la premiere dimension du nouveau tableau
	if(copieImage.mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau copieImage de pixels dans redimensionnement\n");
		return 0;
	}

	// Creation de la deuxieme dimension du nouveau tableau
	for(lig=0; lig< copieImage.nb_lig; lig++){
		copieImage.mat[lig]=malloc((copieImage.nb_col) * sizeof(PIXEL));
		//Verification de l'allocation de la deuxieme dimension du nouveau
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


	//Liberation de la memoire de l'image reçue
	vider_tab_pixels(image);
	//Reallocation d'un nouveau tableau de taille reduite a image
	image->mat=NULL;
	image->nb_lig = ordSortie-ordEntree;
	image->nb_col = absSortie-absEntree;
	image->type = copieImage.type;
	image->max_val = copieImage.max_val;
	image->mat = malloc((image->nb_lig)* sizeof(PIXEL));


	//Verification de l'allocation de la premiere dimension du nouveau tableau
	if(image->mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension du tableau de pixels dans redimensionnement\n");
		return 0;
	}

	// Creation de la deuxieme dimension du nouveau tableau
	for(lig=0; lig< image->nb_lig +1; lig++){
		image->mat[lig]=malloc((image->nb_col +1) * sizeof(PIXEL));
		//Verification de l'allocation de la deuxieme dimension du nouveau
		if(image->mat[lig]==NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension du tableau de pixels dans redimensionnement\n");
			for(lig=lig-1; lig>=0; lig--){
				free(image->mat[lig]);
			}
			free(image->mat);
			return 0;
		}
	}//Fin de la reallocation du nouveau tableau de taille reduite a image


	// Affectation des valeurs de copieImage dans image
	for(lig=ordEntree; lig<=ordSortie; lig++){
		for(col=absEntree; col<=absSortie;col++){
			image->mat[lig-ordEntree][col-absEntree] = copieImage.mat[lig][col];
		}
	}

	//Vidage copieImage
	vider_tab_pixels(&copieImage);
	return 1;
}

int amelioration_du_contraste (IMAGE *imageATransfo){
	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(imageATransfo->type == 3 || imageATransfo->type == 6){
		niveauGris(imageATransfo);
	}

	if(imageATransfo->type != 1 && imageATransfo->type != 4){
		int i,j, min = imageATransfo->mat[0][0].r, max = imageATransfo->mat[0][0].r;

		//Recherche du Min et du Max
		for (i = 0; i < imageATransfo->nb_lig; i++)
		{
			for (j = 0; j < imageATransfo->nb_col; j++)
			{
				if (imageATransfo->mat[i][j].r < min)
					min = imageATransfo->mat[i][j].r;
				if (imageATransfo->mat[i][j].r > max)
					max = imageATransfo->mat[i][j].r;			
			}
		}

		//Double boucle pour parcourir tout le tableau
		for (i = 0; i < imageATransfo->nb_lig; i++)
		{
			for (j = 0; j < imageATransfo->nb_col; j++)
			{
				//On change toutes les composantes avec la formules trouves dans l'etude theorique
				imageATransfo->mat[i][j].r = (255/(max-min)) * (imageATransfo->mat[i][j].r - min);
				imageATransfo->mat[i][j].g = (255/(max-min)) * (imageATransfo->mat[i][j].g - min);
				imageATransfo->mat[i][j].b = (255/(max-min)) * (imageATransfo->mat[i][j].b - min);
			}
		}
	}

	return 1;
}

int lissage (IMAGE *imageATransfo){
	int lig, col;
	IMAGE copie;
	copie.nb_lig = imageATransfo->nb_lig;
	copie.nb_col = imageATransfo->nb_col;

	//Allocation dynamique de la copie de l'image 
	copie.mat = malloc(copie.nb_lig * sizeof(PIXEL));
	if(copie.mat == NULL){
		printf("[X]\tErreur d'allocation sur la premiere dimension de la copie du tableau de pixels\n");
		return 0;
	}
	for (lig=0; lig<copie.nb_lig; lig++){
		copie.mat[lig] = malloc(copie.nb_col * sizeof(PIXEL));
		
		if(copie.mat[lig] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension de la copie du tableau de pixels\n");
			for(lig=lig-1; lig>=0; lig--)
				free(copie.mat[lig]);
			free(copie.mat);
			return 0;
		}
	}

	//On copie l'image de base dans la copie allouee dynamiquement
	for (lig = 0; lig < imageATransfo->nb_lig; lig++)
	{
		for (col = 0; col < imageATransfo->nb_col; col++)
		{
			copie.mat[lig][col] = imageATransfo->mat[lig][col];
		}
	}

	//On commence les choses serieuses on fait le lissage
	for (lig = 1; lig < imageATransfo->nb_lig - 2; lig++)
	{
		for (col = 1; col < imageATransfo->nb_col - 2; col++)
		{

			imageATransfo->mat[lig][col].r = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].r)+(imageATransfo->mat[lig-1][col].r)+(imageATransfo->mat[lig-1][col+1].r)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].r)+(imageATransfo->mat[lig][col].r)+(imageATransfo->mat[lig][col+1].r)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].r)+(imageATransfo->mat[lig+1][col].r)+(imageATransfo->mat[lig+1][col+1].r))/ 9;

			imageATransfo->mat[lig][col].g = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].g)+(imageATransfo->mat[lig-1][col].g)+(imageATransfo->mat[lig-1][col+1].g)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].g)+(imageATransfo->mat[lig][col].g)+(imageATransfo->mat[lig][col+1].g)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].g)+(imageATransfo->mat[lig+1][col].g)+(imageATransfo->mat[lig+1][col+1].g))/ 9;

			imageATransfo->mat[lig][col].r = (  //1ere ligne
												(imageATransfo->mat[lig-1][col-1].r)+(imageATransfo->mat[lig-1][col].r)+(imageATransfo->mat[lig-1][col+1].r)+
												//2eme ligne
												(imageATransfo->mat[lig][col-1].r)+(imageATransfo->mat[lig][col].r)+(imageATransfo->mat[lig][col+1].r)+
												//3eme ligne
												(imageATransfo->mat[lig+1][col-1].r)+(imageATransfo->mat[lig+1][col].r)+(imageATransfo->mat[lig+1][col+1].r))/ 9;
		}
	}

	//Il faut eventuellement normaliser on sais pas trop 

	vider_tab_pixels(&copie);

	return 1;
}