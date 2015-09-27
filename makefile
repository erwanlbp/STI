#Creation de l'executable 'STI'
# -o : Choisir le nom de l'executable
# -Wall : Afficher tous les Warnings
# -g : Nettoyer les fichiers temporaires
STI: main.c
	gcc main.c -Wall -g -o STI

clean:
	rm *.o