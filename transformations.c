#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"

/**  
 * \file transformation.c
 * \brief Fichier dans lequel on à codé toutes les transformations
 * \author Le Batard--Polès Erwan
 		   Vacheret Alex
 		   Romanet Vincent
 * Toutes les transformations sont dans ce fichier, nous avons également coder certaines fonctions 
 * pour éviter la dupplication de code telle que allo_tableau ou _creation_masque et applicatoin_masque 
 */


/**
* \fn int binarisation
* \brief Fonction pour faire la binarisation d'une image
* Si l'image est en couleur alors la passe en niveau de gris avant de faire d'autre opération
* On compare chaque valeur des pixels avec une valeur seuil.
* Si la valeur du pixel est supérieur alors elle prend la valeur 255.
* Sinon la valeur prend la valeur 0.
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
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
					imageATransfo->mat[lig][col].r = 1;
					imageATransfo->mat[lig][col].g = 1;
					imageATransfo->mat[lig][col].b = 1;
				}
				//Si la valeur est en dessous du seuil il prend la valeur 1
				else {
					imageATransfo->mat[lig][col].r = 0;
					imageATransfo->mat[lig][col].g = 0;
					imageATransfo->mat[lig][col].b = 0;
				}
			}
			
		}
		// On change le type de fichier d'ecriture, pour economiser de la memoire
		if(imageATransfo->type <= 3)
			imageATransfo->type = 1;
		else 
			imageATransfo->type = 4;
	}
	
	return 1;
}

/**
* \fn int négatif
* \brief Fonction pour renvoyer le complémentaire de l'image par rapport aux couleurs de bases
* Cette fonction marche avec des images couleurs ou en niveau de gris
* On remplace les valeurs de chaque composante par (255 - la valeur du pixel)
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
int negatif(IMAGE *image){
	int lig,col;

	//Double boucle pour parcourir le tableau
	for(lig=0;lig<image->nb_lig;lig++){
		for(col=0;col<image->nb_col;col++){
			//On applique la formule pour changer la valeur de chaque composante selon le type de fichier
			image->mat[lig][col].r = image->max_val - (image->mat[lig][col].r);
			image->mat[lig][col].g = image->max_val - (image->mat[lig][col].g);
			image->mat[lig][col].b = image->max_val - (image->mat[lig][col].b);
		}
	}
	return 1;
}

/**
* \fn int négatif
* \brief Fonction pour mettre en niveau de gris 
* Cette fonction marche seulement si l'image de base est en couleur 
* On effectue la formule suivante pour changer la valeur de chaque pixel : (0.3*valeur.r + 0.59*valeur.g + 0.11*valeur.b)
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
int niveauGris(IMAGE *image){

	//On effectue la transformation seulement si l'image est en couleur
	if(image->type == 3 || image->type == 6){
		float gris;
		int lig, col;
		for(lig=0;lig<image->nb_lig;lig++){
			for(col=0;col<image->nb_col;col++){
				gris = (0.3*(image->mat[lig][col].r)) + (0.59*(image->mat[lig][col].g))+(0.11*(image->mat[lig][col].b));
				image->mat[lig][col].r = gris;
				image->mat[lig][col].g = gris;
				image->mat[lig][col].b = gris;
			}
		}
		// On change le type de fichier d'ecriture, pour economiser de la memoire
		if(image->type <= 3)
			image->type = 2;
		else 
			image->type = 5;
	}

	return 1;
}

/**
* \fn int symétrie_verticale
* \brief Fonction faire une symétrie verticale de l'image
* Cette fonction marche pour n'importe quelle image 
* On effectue une symétrie de l'image verticalement par rapport à l'axe horizontal
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
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

/**
* \fn int symétrie_horizontale
* \brief Fonction faire une symétrie horizontale de l'image
* Cette fonction marche pour n'importe quelle image 
* On effectue une symétrie de l'image horizontalement par rapport à l'axe vertical
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
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

/**
* \fn int redimensionnement
* \brief Fonction redimensionner une image
* Cette fonction marche pour n'importe quelle image en couleur ou niveau de gris
* L'utilisateur rentre les coordonnées de deux points et l'image est réduite selon ces points
* Si l'utilisateur rentre des points hors de l'image elles sont remises à 0 ou a 255.
*
* \return L'image transformée passer en paramètre donc 1 si tout va bien.
*/
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

	//Allocation de la copie de l'image
	alloc_tableau(&copieImage);

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
	image->nb_lig = ordSortie-ordEntree +1;
	image->nb_col = absSortie-absEntree +1;
	image->type = copieImage.type;
	image->max_val = copieImage.max_val;

	alloc_tableau(image);	

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
		int lig,col, min = imageATransfo->mat[0][0].r, max = imageATransfo->mat[0][0].r;

		//Recherche du Min et du Max
		for (lig = 0; lig < imageATransfo->nb_lig; lig++){
			for (col = 0; col < imageATransfo->nb_col; col++){
				if (imageATransfo->mat[lig][col].r < min)
					min = imageATransfo->mat[lig][col].r;
				if (imageATransfo->mat[lig][col].r > max)
					max = imageATransfo->mat[lig][col].r;			
			}
		}

		printf("\tValeur max : %d\n\tValeur min : %d\n", max, min);
		// On acoluste les valeurs sur l'echelle [0;max]
		for (lig = 0; lig < imageATransfo->nb_lig; lig++){
			for (col = 0; col < imageATransfo->nb_col; col++){
				//On change toutes les composantes avec la formules trouvés dans l'etude theorique
				imageATransfo->mat[lig][col].r = (imageATransfo->max_val * (imageATransfo->mat[lig][col].r - min))/(max - min);
				imageATransfo->mat[lig][col].g = (imageATransfo->max_val * (imageATransfo->mat[lig][col].g - min))/(max - min);
				imageATransfo->mat[lig][col].b = (imageATransfo->max_val * (imageATransfo->mat[lig][col].b - min))/(max - min);
			}
		}

		// On change le type de fichier d'ecriture, pour economiser de la memoire
		if(imageATransfo->type <= 3)
			imageATransfo->type = 2;
		else 
			imageATransfo->type = 5;
	}

	return 1;
}

int lissage (IMAGE *imageATransfo){

	IMAGE copie;
	creation_Copie(imageATransfo, &copie);

	//On créer le masque, une matrice 3x3 contenant que des 1
	int *masque=NULL;
	masque = malloc(9 * sizeof(int));
	creation_masque(masque,1,1,1,1,1,1,1,1,1);

	//On commence les choses serieuses on fait le lissage
	application_masque(imageATransfo, &copie, masque, 9);

	vider_tab_pixels(&copie);

	return 1;
} 

int laplacien (IMAGE *imageATransfo){

	IMAGE copie;
	creation_Copie(imageATransfo, &copie);

	int *masque=NULL;
	masque = malloc(9 * sizeof(int));
	creation_masque(masque,0,1,0,1,-4,1,0,1,0);

	application_masque(imageATransfo, &copie, masque, 9);

	amelioration_du_contraste(imageATransfo);

	vider_tab_pixels(&copie);

	return 1;
}

int alloc_tableau (IMAGE *imageAlloc){
	int i;

	// On alloue la premiere dimension du tableau
	imageAlloc->mat = malloc(imageAlloc->nb_lig * sizeof(PIXEL));
	if(imageAlloc->mat == NULL){ 
		// Si il y a une erreur on met un message et quitte la fonction
		printf("[X]\tErreur d'allocation sur la premiere dimension alloc_tableau\n");
		return 0;
	}

	// On alloue la deuxieme dimension
	for (i=0; i<imageAlloc->nb_lig; i++){
		imageAlloc->mat[i] = malloc(imageAlloc->nb_col * sizeof(PIXEL));
		
		// Si il y a une erreur on libere la memoire qu'on a allouee avant
		if(imageAlloc->mat[i] == NULL){
			printf("[X]\tErreur d'allocation sur la deuxieme dimension alloc_tableau\n");
			for(i=i-1; i>=0; i--)
				free(imageAlloc->mat[i]);
			free(imageAlloc->mat);
			return 0;
		}
	}

	return 1;
}

void creation_masque (int *masque, int a, int b, int c, int d, int e, int f, int g, int h, int i){
	masque[0] = a;
	masque[1] = b;
	masque[2] = c;
	masque[3] = d;
	masque[4] = e;
	masque[5] = f;
	masque[6] = g;
	masque[7] = h;
	masque[8] = i;
}

void application_masque (IMAGE *image, IMAGE *copie, int *masque, int diviseur){
	int lig, col;
	PIXEL tmp;

	for (lig = 0; lig < image->nb_lig; lig++){
		for (col = 0; col < image->nb_col; col++){
			tmp.r = 0;
			tmp.g = 0;
			tmp.b = 0;

			if(lig-1 >=0 && col-1 >=0) 							tmp.r += copie->mat[lig-1][col-1].r * masque[0];
			if(lig-1 >=0) 										tmp.r += copie->mat[lig-1][col].r * masque[1];
			if(lig-1 >=0 && col+1 <image->nb_col) 				tmp.r += copie->mat[lig-1][col+1].r * masque[2];
			if(col-1 >=0) 										tmp.r += copie->mat[lig][col-1].r * masque[3];
																tmp.r += copie->mat[lig][col].r * masque[4];
			if(col+1 <image->nb_col) 							tmp.r += copie->mat[lig][col+1].r * masque[5];
			if(lig+1 <image->nb_lig && col-1 >=0) 				tmp.r += copie->mat[lig+1][col-1].r * masque[6];
			if(lig+1 <image->nb_lig) 							tmp.r += copie->mat[lig+1][col].r * masque[7];
			if(lig+1 <image->nb_lig && col+1 <image->nb_col) 	tmp.r += copie->mat[lig+1][col+1].r * masque[8];
			image->mat[lig][col].r = tmp.r / diviseur;


			if(lig-1 >=0 && col-1 >=0) 							tmp.g += copie->mat[lig-1][col-1].g * masque[0];
			if(lig-1 >=0) 										tmp.g += copie->mat[lig-1][col].g * masque[1];
			if(lig-1 >=0 && col+1 <image->nb_col) 				tmp.g += copie->mat[lig-1][col+1].g * masque[2];
			if(col-1 >=0) 										tmp.g += copie->mat[lig][col-1].g * masque[3];
																tmp.g += copie->mat[lig][col].g * masque[4];
			if(col+1 <image->nb_col) 							tmp.g += copie->mat[lig][col+1].g * masque[5];
			if(lig+1 <image->nb_lig && col-1 >=0) 				tmp.g += copie->mat[lig+1][col-1].g * masque[6];
			if(lig+1 <image->nb_lig) 							tmp.g += copie->mat[lig+1][col].g * masque[7];
			if(lig+1 <image->nb_lig && col+1 <image->nb_col) 	tmp.g += copie->mat[lig+1][col+1].g * masque[8];
			image->mat[lig][col].g = tmp.g / diviseur;

			if(lig-1 >=0 && col-1 >=0) 							tmp.b += copie->mat[lig-1][col-1].b * masque[0];
			if(lig-1 >=0) 										tmp.b += copie->mat[lig-1][col].b * masque[1];
			if(lig-1 >=0 && col+1 <image->nb_col) 				tmp.b += copie->mat[lig-1][col+1].b * masque[2];
			if(col-1 >=0) 										tmp.b += copie->mat[lig][col-1].b * masque[3];
																tmp.b += copie->mat[lig][col].b * masque[4];
			if(col+1 <image->nb_col) 							tmp.b += copie->mat[lig][col+1].b * masque[5];
			if(lig+1 <image->nb_lig && col-1 >=0) 				tmp.b += copie->mat[lig+1][col-1].b * masque[6];
			if(lig+1 <image->nb_lig) 							tmp.b += copie->mat[lig+1][col].b * masque[7];
			if(lig+1 <image->nb_lig && col+1 <image->nb_col) 	tmp.b += copie->mat[lig+1][col+1].b * masque[8];
			image->mat[lig][col].b = tmp.b / diviseur;
		}
	}
}

void creation_Copie(IMAGE *image, IMAGE *copie){

	copie->nb_lig = image->nb_lig;
	copie->nb_col = image->nb_col;
	copie->type = image->type;
	copie->max_val = image->max_val;
	alloc_tableau(copie);

	//On copie l'image de base dans la copie allouee dynamiquement
	int lig, col;
	for (lig = 0; lig < image->nb_lig; lig++){
		for (col = 0; col < image->nb_col; col++){
			copie->mat[lig][col] = image->mat[lig][col];
		}
	}
}

void gradientSimple( IMAGE *image){
	int lig, col; 
	IMAGE copieImageGx, copieImageGy;
	int *masqueX=NULL;
	int *masqueY=NULL;
	//Allocation du masque
	masqueX = malloc(9 * sizeof(int));
	masqueY = malloc(9 * sizeof(int));
	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(image->type == 3 || image->type == 6){
		niveauGris(image);
	}

	//Création de la copieImage pour le gradient en X
	copieImageGx.mat = NULL;
	creation_Copie(image, &copieImageGx);

	//Création de la copieImage pour le gradient en Y
	copieImageGy.mat = NULL;
	creation_Copie(image, &copieImageGy);

	creation_masque(masqueX, 0, 0, 0, 0, -1, 1, 0, 0, 0);
	creation_masque(masqueY, 0, 0, 0, 0, -1, 0, 0, 1, 0);

	//Aplication du premier masque par rapport a l'axe X
	application_masque(image, &copieImageGx, masqueX, 9);

	//Application du second masque par rapport a l'axe Y
	application_masque(&copieImageGy, &copieImageGx, masqueY, 9);

	//On recupere image auquel on a applique le masqueX et copieImageGy auquel on a applique le masqueY

	//On fait une double boucle pour recuperer l'image finale avec le gradient simple
	for(lig=0; lig<image->nb_lig;lig++){
		for(col=0; col<image->nb_col;col++){
			image->mat[lig][col].r = abs(image->mat[lig][col].r) + abs(copieImageGy.mat[lig][col].r);
			image->mat[lig][col].g = abs(image->mat[lig][col].g) + abs(copieImageGy.mat[lig][col].g);
			image->mat[lig][col].b = abs(image->mat[lig][col].b) + abs(copieImageGy.mat[lig][col].b);
		}
	}

	vider_tab_pixels(&copieImageGx);
	vider_tab_pixels(&copieImageGy);
}

void gradientSobel( IMAGE *image){
	int lig, col; 
	IMAGE copieImageGx, copieImageGy;
	int *masqueX=NULL;
	int *masqueY=NULL;
	//Allocation du masque
	masqueX = malloc(9 * sizeof(int));
	masqueY = malloc(9 * sizeof(int));
	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(image->type == 3 || image->type == 6){
		niveauGris(image);
	}

	//Création de la copieImage pour le gradient en X
	copieImageGx.mat = NULL;
	creation_Copie(image, &copieImageGx);

	//Création de la copieImage pour le gradient en Y
	copieImageGy.mat = NULL;
	creation_Copie(image, &copieImageGy);

	creation_masque(masqueX, -1, 0, 1, -2, 0, 2, -1, 0, 1);
	creation_masque(masqueY, 1, 2, 1, 0, 0, 0, -1, -2, -1);

	//Aplication du premier masque par rapport a l'axe X
	application_masque(image, &copieImageGx, masqueX, 1);

	//Application du second masque par rapport a l'axe Y
	application_masque(&copieImageGy, &copieImageGx, masqueY, 1);

	//On recupere image auquel on a applique le masqueX et copieImageGy auquel on a applique le masqueY

	//On fait une double boucle pour recuperer l'image finale avec le gradient simple
	for(lig=0; lig<image->nb_lig;lig++){
		for(col=0; col<image->nb_col;col++){
			image->mat[lig][col].r = abs(image->mat[lig][col].r) + abs(copieImageGy.mat[lig][col].r);
			image->mat[lig][col].g = abs(image->mat[lig][col].g) + abs(copieImageGy.mat[lig][col].g);
			image->mat[lig][col].b = abs(image->mat[lig][col].b) + abs(copieImageGy.mat[lig][col].b);
		}
	}

	vider_tab_pixels(&copieImageGx);
	vider_tab_pixels(&copieImageGy);
}

void detectionContoursSobel(IMAGE * image){
	gradientSobel(image);
	binarisation(image);
}

int detectionContoursLaplacien (IMAGE *imageATransfo){
	int col, lig, L0 = 160, G0 = 55;

	IMAGE copieLaplacien;
	copieLaplacien.mat = NULL;
	creation_Copie(imageATransfo, &copieLaplacien);

	IMAGE copieGradient;
	copieGradient.mat = NULL;
	creation_Copie(imageATransfo, &copieGradient);

	//L'image doit être lissée avant de pouvoir en détecter ses contours
	lissage(imageATransfo);

	for (lig = 0; lig < imageATransfo->nb_lig; lig++)
	{
		for (col = 0; col < imageATransfo->nb_col; col++)
		{
			if ((copieLaplacien.mat[lig][col].r < L0) && (copieGradient.mat[lig][col].r > G0))
			{
				imageATransfo->mat[lig][col].r = 255;
				imageATransfo->mat[lig][col].g = 255;
				imageATransfo->mat[lig][col].b = 255;
			}
			else
			{
				imageATransfo->mat[lig][col].r = 0;
				imageATransfo->mat[lig][col].g = 0;
				imageATransfo->mat[lig][col].b = 0;
			}
		}
	}

	vider_tab_pixels(&copieLaplacien);
	vider_tab_pixels(&copieGradient);

	return 1;
}

int reductionBruit(IMAGE *image){
	int lig,col;
	int masqueLumi[9]={0};

	//Si l'image est en couleur il y a besoin de la passer en niveau de gris
	if(image->type == 3 || image->type == 6){
		niveauGris(image);
	}

	//Double boucle for ou l'on prend les valeurs autour du pixel actuel pour trouver la valeur 
	// la plus petite. 
	for(lig=1;lig<image->nb_lig-2;lig++){
		for(col=1;col<image->nb_col-2;col++){
			//On crée le masque a chaque tour de boucle
			creation_masque(masqueLumi,
				image->mat[lig-1][col-1].r,image->mat[lig-1][col].r,image->mat[lig-1][col+1].r,
				image->mat[lig][col-1].r,image->mat[lig][col].r,image->mat[lig][col+1].r,
				image->mat[lig+1][col-1].r,image->mat[lig+1][col].r,image->mat[lig+1][col+1].r);
			//On trie le masque
			triTab(masqueLumi, 9);
			//On associe le pixel actuel à la valeur mediane du masque
			image->mat[lig][col].r = masqueLumi[4];
			image->mat[lig][col].g = masqueLumi[4];
			image->mat[lig][col].b = masqueLumi[4];
		}
	}
	return 1;
}

int triTab (int *masque, int taille){
	int tmp = 0, i, j;

	for (i = 0; i < taille; ++i)
	{
		tmp = masque[i];
		j = i;
		while ((j > 0) && (masque[j-1] > tmp))
		{
			masque[j] = masque[j-1];
			j --;
		} 
		masque[j] = tmp;
	}
	return 1;
}

int masqueCustom (IMAGE *imageATransfo, const int argc, const char *argv[]){

	//On vérifie que tous les arguments sont envoyés
	if(argc != 13){
		printf("[X]\tMerci de rentrer toutes les valeurs du masque\n");
		return 1;
	}

	//On alloue de la mémoire pour le masque a appliquer
	int *masque=NULL;
	masque = malloc(9 * sizeof(int));

	creation_masque(masque ,atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), atoi(argv[9]), atoi(argv[10]), atoi(argv[11]));

	//On créer une copie qui va contenir les valeurs afin d'appliquer le masque avec les valeurs d'origine
	IMAGE copieImage;
	copieImage.mat = NULL;
	creation_Copie(imageATransfo, &copieImage);

	application_masque(imageATransfo, &copieImage, masque, atoi(argv[12]));

	//On vide la copie alloué en mémoire
	vider_tab_pixels(&copieImage);

	return 1;
}