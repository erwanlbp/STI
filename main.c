#include "header.h"
 
int main(int argc, char const *argv[])
{
	//Pour effacer l'ecran
	effacer_ecran();

	ligne_separation('=');

	// On ouvre le fichier de l'image
	FILE* file_image = ouverture_image(argc,argv);
	if(file_image != NULL){
		int nb_col,nb_lig,max_val;
		PIXEL **tab_pixels = NULL;
		if(! lecture_fichier(file_image,tab_pixels,&nb_col,&nb_lig,&max_val))
			return 1;

		afficher_tab_pixels(tab_pixels,nb_col,nb_lig);

		int i;
		for (i = 0; i < nb_lig; ++i)
		{
			free(tab_pixels[i]);
		}
		free(tab_pixels);


			// Appels des fonctions de transformation

		// On ferme le fichier quand on a finit de travailler dessus
		fclose(file_image);
	}

	ligne_separation('=');

	return 0;
} 

int lecture_fichier(FILE* file_image,PIXEL **tab_pixels,int *nb_col, int *nb_lig, int *max_val){
	char char_tmp[80] = "";
	int continuer = 1;
	int col=0;
	PIXEL pix_tmp;
	int i = 0;
	int j = 0;

	printf("Lecture fichier : \n");
	fscanf(file_image,"%s",char_tmp);
	printf("%s\n",char_tmp);
	fscanf(file_image,"%d %d",nb_col,nb_lig);
	printf("%d %d\n",*nb_col,*nb_lig);
	tab_pixels = malloc(*nb_lig * sizeof(PIXEL));
	if(tab_pixels == NULL)
		return 0;

	for (i = 0; i < *nb_lig; ++i){
		tab_pixels[i] = malloc(*nb_col * sizeof(PIXEL));
	}

	fscanf(file_image,"%d",max_val);
	printf("%d\n",*max_val);

	do{
		if(fscanf(file_image, "%d %d %d", &pix_tmp.r, &pix_tmp.g, &pix_tmp.b)) 
			printf("%d %d %d\n", pix_tmp.r, pix_tmp.g, pix_tmp.b);
		else
			continuer = 0;

		tab_pixels[i][j] = pix_tmp;
		printf("ok\n");
		j++;  
		if(j==col){
			j = 0;
			i++;
		}
		printf("ligne %d ok\n",j );
	}while(continuer);

	printf("Fin de lecture fichier\n");


	return 1;

}

void afficher_tab_pixels(PIXEL **tab_pixels, int nb_col, int nb_lig){
	int i,j;
	for (j = 0; j < nb_lig; ++j)
	{
		for (i = 0; i < nb_col; ++i)
		{
			printf("%d %d %d  ",tab_pixels[i][j].r,tab_pixels[i][j].g,tab_pixels[i][j].b);
		}	
		printf("\n");
	}
}

FILE* ouverture_image(int argc, char const *argv[]){

	// Variable contenant le chemin du fichier, par defaut "test.ppm"
	char chemin_img[255] = "./test.ppm";

	// On teste si on a recu un chemin de fichier
	if (argc >= 2){
		// On rajoute le "./" au debut du chemin si c'est pas fait
		if(argv[1][0] != '.')
			sprintf(chemin_img,"./%s",argv[1]);
		else
			sprintf(chemin_img,"%s",argv[1]);

		//On affiche le chemin qu'on a recu
		printf("[O]\tUn chemin de fichier a été trouvé : %s\n",chemin_img);
	}
	else //Sinon on dit qu'on a rien recu et on donne le chemin par defaut
		printf("[X]\tAucun chemin de fichier trouvé, chemin par défaut : %s\n",chemin_img);

	// On ouvre le fichier de l'image
	FILE* fichier = NULL;
	fichier = fopen(chemin_img,"r");

	if(fichier != NULL)
		printf("[O]\tOuverture du fichier réussie\n");
	else 
		printf("[X]\tOuverture du fichier raté\n");

	return fichier;
}
/*
int test_validite_fichier(FILE *file_image){

	int valide = 1;
	char char_tmp[80] = "";
	int continuer = 1, i = 1;

	while(continuer){
		fscanf(file_image,"%s",char_tmp);
		if(char_tmp[0] != '#'){
			switch(i){
				case 1 : if(char_tmp != "P3") {
					continuer = 0;
					valide = 0;
				}
				break;


			}
			i++;
		}
	}
	if(valide)
		printf("[O]\tLe fichier est valide\n");
	else 
		printf("[X]\tLe fichier n'est pas valide\n");

	return valide;
}
*/

void ligne_separation(char separateur){
	// On ecrit 100 fois le caractère recu en argument
	printf("\n");
	int i;
	for (i = 0; i < 100; ++i)
	{
		printf("%c",separateur);
	}
	printf("\n\n");
}

void effacer_ecran(){
	// Decide de l'OS à la compilation
	#ifdef _WIN32
	system("cls");
	#elif __unix__ 
	system("clear");
	#elif __linux__
	system("clear");
	#endif
}