#include "fonction.h"


void fusionner(Player tab[], int debut, int milieu, int fin) {//trifusion technique seen in class so I don't comment
    int indexA, indexB;
    Player aux[100]; // Tableau auxiliaire pour les structures Player

    // Copie des deux moitiés dans le tableau auxiliaire
    for (int i = debut; i <= milieu; i++) {
        aux[i] = tab[i];
    }
    for (int i = milieu + 1; i <= fin; i++) {
        aux[i] = tab[fin - i + milieu + 1];
    }

    indexA = debut;
    indexB = fin;

    // Fusion des deux moitiés depuis le tableau auxiliaire dans le tableau original
    for (int i = debut; i <= fin; i++) {
        if (aux[indexA].score >= aux[indexB].score) {
            tab[i] = aux[indexA];
            indexA++;
        } else {
            tab[i] = aux[indexB];
            indexB--;
        }
    }
}

void triFusionRec(Player tab[],int debut,int fin){ //trifusion technique seen in class so I don't comment
	int milieu;
	if(debut<fin){
		milieu=(debut+fin)/2;
		triFusionRec(tab,debut,milieu);
		triFusionRec(tab,milieu+1,fin);
		fusionner(tab,debut,milieu,fin);
	}
}
void triFusion(Player tab[], int size){ //trifusion technique seen in class so I don't comment
	triFusionRec(tab, 0 ,size-1);
	}


// fucntion for show the information of the players
void showPlayer(Player Playerss[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%dème --> Nom: %s, Score: %d\n", i + 1, Playerss[i].name, Playerss[i].score); // printf the top 10 of best players
    }
}

// function for read the bestscore and the name in the file
int readBestScore(Player bestplayers[]) {
    FILE *fichier = fopen("BestScores.txt", "r"); //open the file name's BestScore.txt
    if (fichier == NULL) {
        return 0; // No score has been recorded yet
    }

    int count = 0;
    while (fscanf(fichier, "%s %d", bestplayers[count].name, & bestplayers[count].score) != EOF && count < 10) { //read the file and take the first chaine of character and number entire and go to the next line
        count++;
    }

    fclose(fichier);
    return count;
}

// function for write the bestscore and the name in the file
void writeBestScore(Player bestplayers[], int count) {
    FILE *fichier = fopen("BestScores.txt", "w");
    if (fichier == NULL) {
        printf("Erreur d'ouverture du fichier\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fichier, "%s %d\n", bestplayers[i].name, bestplayers[i].score); //print in the file the information about the Best player
    }

    fclose(fichier);
}

void top10Score(int nb_players, Player *Playerss){//function for write the top 10 bestscore in this game
    Player bestplayers[10] = {0}; //Initialize to zero
    int numberbestplayers = readBestScore(bestplayers);

    // Add new players to the top players list
    int totalplayers = numberbestplayers + nb_players;
    Player *allplayers = (Player *)malloc(totalplayers * sizeof(Player));
    if (allplayers == NULL) {
        printf("Erreur d'allocation de mémoire\n");
        free(Playerss);
        exit(1);
    }


    // Copy the best existing players
    for (int i = 0; i < numberbestplayers; i++) {
        allplayers[i] = bestplayers[i];
    }

    // Add new players
    for (int i = 0; i < nb_players; i++) {
        allplayers[9 + i] = Playerss[i];
    }

    // Sort all players by score using merge sort
    triFusion(allplayers,totalplayers);


    // Keep only the 10 best
    numberbestplayers = totalplayers < 10 ? totalplayers : 10;
    for (int i = 0; i < 10; i++) {
        bestplayers[i] = allplayers[i];
    }

    // Write top 10 players to file
    writeBestScore(bestplayers, 10);

    // Show Top 10 Players
    printf("\nLes 10 meilleurs joueurs:\n");
    showPlayer(bestplayers, 10);

    free(allplayers);
}
