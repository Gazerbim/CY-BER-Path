
#include "fonction.h"

void move_cursor(int row, int col) {
    printf("\e[%d;%dH", row, col);
}
void printRobot() {
    for(int i=0;i<10;i++){
        printf("   ____    \n");
        printf("  | o o|   \n");
        printf("  |  ^ |   \n");
        printf("  | [_]|   \n");
        printf("  |____|   \n");
        printf("  \\ | | / \n");
        printf("   \\| |/  \n");
        printf("    |_|    \n");
        printf("    / \\   \n");
        printf("   /   \\  \n");
        move_cursor(0,30);
        usleep(300000);  // Pause for 300ms
        printf("   ____    \n");
        printf("  | o o|   \n");
        printf("  |  ^ |   \n");
        printf("  | [_]|   \n");
        printf("  |____|   \n");
        printf("    | |    \n");
        printf(" ---| |--- \n");
        printf("    |_|    \n");
        printf("    / \\   \n");
        printf("   /   \\  \n");
        move_cursor(0,30);
        usleep(300000);  // Pause for 300ms
        printf("   ____    \n");
        printf("  | o o|   \n");
        printf("  |  ^ |   \n");
        printf("  | [_]|   \n");
        printf("  |____|   \n");
        printf("    | |    \n");
        printf("   /| |\\  \n");
        printf("  / |_| \\ \n");
        printf("    / \\   \n");
        printf("   /   \\  \n");
        move_cursor(0,30);
        usleep(300000);  // Pause for 300ms
        printf("   ____    \n");
        printf("  | o o|   \n");
        printf("  |  ^ |   \n");
        printf("  | [_]|   \n");
        printf("  |____|   \n");
        printf("    | |    \n");
        printf(" ---| |--- \n");
        printf("    |_|    \n");
        printf("    / \\   \n");
        printf("   /   \\  \n");
        move_cursor(0,30);
        usleep(300000);  // Pause for 300ms
    }
}


int chrono(int a){ // initializes a dynamic stopwatch
	int min;
	int sec;
	for( int i=a;i>0;i--){
		min=i/60;
		sec=i-(min*60);
		if (min>0){
            printf("%d min %d sec   \r",min,sec); // /r will allow us to return the cursor to the beginning of the line in order to rewrite it
		}
		else{
            printf("%d sec        \r",sec);
		}
		fflush(stdout); //allows you to force the display of the chrono before it is rewritten by \r
		sleep(1);
	}
	return 1;
}

int harder(){ // choose the difficulty between 3
	int dif;
	int verification;
	printf("\033[H\033[2J===========CHOIX DE LA DIFFICULTE===========\n\n\n");
	do{
        printf("\nQuel niveau de difficulté ?\n  1 = Facile\n  2 = Moyen\n  3 = Dur\n");
        scanf("%d",&dif);
		if(dif>=1 && dif<=3){
			verification=1;
		}
		else{
			verification=0;
			viderBuffer();
			
                printf("\033[H\033[2J===========CHOIX DE LA DIFFICULTE===========\n\n\n");
                printf("Veuillez saisir un nombre valide entre 1 et 3.\n");
		}
	}while(verification!=1);

	if (dif == 1){
        printf("\033[H\033[2J===========CHOIX DE LA DIFFICULTE===========\n\n\n");
		printf("\nVous avez choisi le niveau de difficulté facile : vous allez avoir 45 secondes pour réflechir au chemin.\n");
		return 45;
	}
	if (dif == 2){
	    printf("\033[H\033[2J===========CHOIX DE LA DIFFICULTE===========\n\n\n");
		printf("\nVous avez choisi le niveau de difficulté moyen : vous allez avoir 30 secondes pour réflechir au chemin.\n");
		return 30;
	}

	if (dif == 3){
        printf("\033[H\033[2J===========CHOIX DE LA DIFFICULTE===========\n\n\n");
		printf("\nVous avez choisi le niveau de difficulté dur : vous allez avoir 15 secondes pour réflechir au chemin.\n");
		return 15;
	}
}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int play(int nb_joueur, int *best, char **nom) {
    int tab[nb_joueur];
    int verification;
    int input;

    for (int i = 0; i < nb_joueur; i++) {
        printf("\033[H\033[2J===========CHOIX DU NOMBRE D'ETAPES===========\n\n\n");
        do {
            printf("\n%s, entrez le nombre de mouvements à faire avant d'atteindre la cible voulue (écrivez -1 si la cible n'est pas atteignable): ", nom[i]);
            verification = scanf("%d", &input);

            if (verification == 1 && (input > 0 || input == -1)) {
                tab[i] = input;
                break;
            } else {
                viderBuffer(); // Vider le buffer d'entrée
                printf("\033[H\033[2J===========CHOIX DU NOMBRE D'ETAPES===========\n\n\n");
                printf("Veuillez saisir un nombre valide supérieur à 0 ou -1.\n");
            }
        } while (1);

        printf("\033[H\033[2J"); // Effacer l'écran pour ne pas voir les réponses des autres joueurs
    }

    *best = 1215752191; // Max 32-bit value
    int player = 0;
    int count = 0;
    int j = 0;
    int count2 =0;
    for (int i = 0; i < nb_joueur; i++) {
        if (*best > tab[i] && tab[i] != -1) {
            *best = tab[i]; // Conserver le score le plus bas
            player = i + 1; // Déterminer quel joueur va jouer
        }
	if(*best == tab[i]){
		count++;
	}
	
    }
    j=rand()%count+0;
    while(count2 != j){ // if there are several times the lowest score it draws lots who will play
	    if(*best == tab[count2]){
		    player=count2+1;
	    }
	    count2++;
    }
    return player;
}


int gestionPoint(int nb_coup_prevu,int nb_coup_fait,int *tabScore,int player,int nb_joueur){ // give the good number of point
    if(nb_coup_fait==-1){ // the player gave up
        for (int i = 0; i < nb_joueur; i++) {
        		if (i != player-1) {
            			tabScore[i]++;
			}
		}
		return *tabScore;
    }
	else if(nb_coup_prevu == nb_coup_fait){
		tabScore[player-1]=tabScore[player-1]+2;
		return *tabScore;
	}
	else if(nb_coup_prevu < nb_coup_fait){
		tabScore[player-1]--;
		return *tabScore;
	}
	else{
		for (int i = 0; i < nb_joueur; i++) {
        		if (i != player-1) {
            			tabScore[i]++;
			}
		}
		return *tabScore;
	}

}

void showScore(int *tabScore, int nb_joueur,char **nom){ // show score
    printf("\033[H\033[2J===========AFFICHAGE DES SCORES===========\n\n\n");
	printf("Voici les scores:\n");
	for(int i=0;i<nb_joueur;i++){
		printf("%s --> %d pts\n",nom[i],tabScore[i]);
	}
	sleep(3);
}

void finalMessage(char **nom, int *tabScore,int nb_joueur){
    printf("===========FIN DE LA PARTIE===========\n\n\n");
	int max=tabScore[0];
	int nb_winner=0;
	for (int i=0;i<nb_joueur;i++){
		if(max<tabScore[i]){
			max=tabScore[i];
		}
	}
	for (int i=0;i<nb_joueur;i++){
		if(max==tabScore[i]){
			nb_winner++;
		}
	}
	char **tab = malloc(nb_winner * sizeof(char *));
        if (tab == NULL) {
            printf("L'alloc du tableau a raté, le jeu va se fermer.\n");
            exit(1);
        }
	int indice =0;
	for (int i=0;i<nb_joueur;i++){
		if(max==tabScore[i]){
			tab[indice]=nom[i];
			indice++;
		}
	}
	if(nb_winner>1){
        printf("\n\n===========FIN DE LA PARTIE===========\n\n\n");
		printf("\nLes grands gagnants de cette partie sont :\n");
		for (int i=0;i<nb_winner;i++){
			printf("%s\n",tab[i]);
		}
		printf("\nBravo à vous !!\n");
	}
	else{
		printf("\nLe grand gagnant est %s\n\nBravo!!\n",tab[0]);
	}
}




void game(int nb_joueur,int *tabScore,int nb_manche,char **nom){ //do one party
	int x,y;//the coordinates of the map
    Cell ** map = generateMap(&x,&y);
    placeWallsOnAnEdge(map,x,y);
    placeTargets(map,x,y);
    placeAdditionalTerrainWalls(map, x,y);
    placeRobots(map,x,y);
        // map generation

	int cible,robot,dif,player;
	int bestScore; // prediction score
	char *robotEmojis[] = {"\U0001F916", "\U0001F47E", "\U0001F47D", "\U0001F47B"}; //list containing robot emoji
	robot=rand()%3+1; //define which robot
	cible=rand()%17+1; // define which target
	printf("\nManche %d\n",nb_manche);
	dif=harder(); //asks for the level of difficulty
	printf("\nla partie va se lancer dans 2 sec !! \n");
	sleep(2); //wait 10 sec
	printMapRed(map,x,y,cible);

	printf("\nrobot %s à la cible cible %d\n",robotEmojis[robot],cible);
	if(chrono(dif)==1){ //call chrono and once the timer ends returns 1
		printf("\033[H\033[2J"); //delete all
	}
	player=play(nb_joueur,&bestScore,nom); // define who play this party
    if (player==0){
        printf("Tout le monde a dit que le niveau était impossible, alors on part pour une nouvelle manche \n");
    }else{
        printMapRed(map,x,y,cible);

        printf("\%s a annoncer le plus petit chemin avec %d coup, il va donc jouer\n",nom[player-1],bestScore);
        int nb_coup_fait=moveTurn(map, cible, x,y,robot+1);
        gestionPoint(bestScore,nb_coup_fait, tabScore,player,nb_joueur);
        showScore(tabScore,nb_joueur,nom);
        bestScore=0;
    }


}
