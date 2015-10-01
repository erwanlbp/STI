#include "header.h"
#include "inOutFichiers.h"
#include "transformations.h"

int main(int argc, char const *argv[])
{ 
	//Pour effacer l'ecran
	effacer_ecran();

	ligne_separation('=');

	char cheminImage[255] = "";
	char transformation[255] = "";

	// On ouvre le fichier de l'image
	FILE* file_image = ouverture_lecture_fichier_image(&argc,argv,cheminImage,transformation);
	if(file_image == NULL)
		return 1;
	
	IMAGE tab_pixels;
	if(lecture_fichier(file_image, &tab_pixels)){
		printf("\tNombre de Colonnes: %d ; Nombre de Lignes: %d ; Valeur Maximal: %d\n",tab_pixels.nb_col,tab_pixels.nb_lig,tab_pixels.max_val);
		printf("[O]\tLecture complete du fichier image reussie");
	}
	else{
		printf("[X]\tProbleme de lecture du fichier image\n");
		return 1;
	}

	// On ferme le fichier quand on a finit de travailler dessus
	fclose(file_image);
	file_image = NULL;

	afficher_tab_pixels(&tab_pixels);

	// ########################################	
	//  Appels des fonctions de transformation
	// ########################################	

	symetrie_verticale(&tab_pixels);
	afficher_tab_pixels(&tab_pixels);

	file_image = ouverture_ecriture_fichier_image(cheminImage,transformation);
	if(file_image == NULL)
		return 1;

	if(ecriture_fichier(file_image,&tab_pixels,cheminImage,transformation))
		printf("[O]\tEcriture du fichier reussie, transformation sauvegardee\n");
	else
		printf("[X]\tEcriture du fichier rate, transformation non sauvegardee\n");

	// On libère le tableau de pixels
	//vider_tab_pixels(&tab_pixels);

	ligne_separation('=');

	return 0;  
} 

void vider_tab_pixels(IMAGE * tab){
	int i;
	printf("Entree vidage\n");
	// Pour chaque case de la IMAGE
	for (i=0; i<tab->nb_lig; i++){
		// On libere la memoire allouee dynamiquement
		free(tab->mat[i]);
		printf("ligne %d ok\n",i);

	}
	printf("1D finie\n");

	// Puis on libere la memoire allouee pour la premiere dimension de la IMAGE
	free(tab->mat);
	printf("2D finie\nFin vidage");

}

void afficher_tab_pixels(IMAGE * tab){
	ligne_separation('-');
	int lig,col;

	for (lig=0; lig<tab->nb_lig; lig++){
		for (col=0; col<tab->nb_lig; col++){
			if(tab->type == 3 || tab->type == 6)
				printf("%d %d %d\t",tab->mat[lig][col].r,tab->mat[lig][col].g,tab->mat[lig][col].b);
			else
				printf("%d ", tab->mat[lig][col].r);
		}	
		printf("\n");
	}

	ligne_separation('-');
}

void ligne_separation(const char separateur){
	// On ecrit 100 fois le caractere recu en argument
	printf("\n");
	int i;
	for (i = 0; i < 100; ++i)
	{
		printf("%c",separateur);
	}
	printf("\n\n");
}

void effacer_ecran(){
	// Decide de l'OS a la compilation
	#ifdef _WIN32
	system("cls");
	#elif __unix__ 
	system("clear");
	#elif __linux__
	system("clear");
	#endif
}