#Creation de l'executable 'STI'
# -o : Choisir le nom de l'executable
# -Wall : Afficher tous les Warnings
# -g : Nettoyer les fichiers temporaires
STI: main.o lectureFichiers.o ecritureFichiers.o
	gcc main.o lectureFichiers.o ecritureFichiers.o -Wall -g -o STI

main.o: main.c
	gcc -c -Wall main.c -o main.o

lectureFichiers.o: lectureFichiers.c
	gcc -c -Wall lectureFichiers.c -o lectureFichiers.o

ecritureFichiers.o: ecritureFichiers.c
	gcc -c -Wall ecritureFichiers.c -o ecritureFichiers.o

clean:
	rm *.o