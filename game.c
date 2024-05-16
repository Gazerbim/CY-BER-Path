#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "fonction.h"



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
	do{
        printf("\nQuel niveau de difficulté ?\n1 = easy\n2 = médium\n3 = hard\n");
        scanf("%d",&dif);

		if(dif>=1 && dif<=3){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
            		printf("Veuillez saisir un nombre valide entre 1 et 3.\n");
		}
	}while(verification!=1);

	if (dif == 1){
		printf("\nvous avez choisi le niveau de difficulté easy vous allez avoir 45 sec pour reflechir.\n");
		return 45;
	}
	if (dif == 2){
		printf("\nvous avez choisi le niveau de difficulté médium vous allez avoir 30 sec pour reflechir.\n");
		return 30;
	}

	if (dif == 3){
		printf("\nvous avez choisi le niveau de difficulté hard vous allez avoir 15 sec pour reflechir.\n");
		return 15;
	}
}

int play(int nb_joueur, int *best,char **nom){ //decide who play this party(who wrote the least number of moves)
	int tab[nb_joueur];
	int verification;
	for (int i=0;i<nb_joueur;i++){
		do{
		printf("\njoueur %s enter your gess (write -1 if the level isn't possible):\n",nom[i]);
		scanf("%d",&tab[i]); // number of movements he thinks he is making

		if(tab[i]>0){
			verification=1;
		}else if(tab[i]==-1){ // just to see that the case "-1" is when the level isn't possible
            verification = 1;
		}else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
            		printf("Veuillez saisir un nombre valide supérieur à 0.\n");
		}
		}while(verification!=1);

		printf("\033[H\033[2J");  // delete everything so as not to see the response of other players
	}
	*best=1215752191;  //max value
	int player=0;
	for(int i=0;i<nb_joueur;i++){
		if(*best>tab[i] && tab[i]!=-1){
			*best=tab[i]; // keep in memory the lowest score
			player=i+1; // decide which player will play
		}
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
	printf("\nvoicie les scores:\n");
	for(int i=0;i<nb_joueur;i++){
		printf("\njoueur %s --> %d pts\n",nom[i],tabScore[i]);
	}
}

void finalMessage(char **nom, int *tabScore,int nb_joueur){
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
            printf("Tab malloc failed, exiting the game\n");
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
		printf("\nles grands gagnants de cette partie sont :\n");
		for (int i=0;i<nb_winner;i++){
			printf("%s\n",tab[i]);
		}
		printf("\nbravo à vous !!\n");
	}
	else{
		printf("\nle grand gagnant est :\n%s\n\nbravo à toi !!\n",tab[0]);
	}
}




void game(int nb_joueur,int *tabScore,int nb_manche,char **nom){ //do one party
	int x,y;//les coos de la map
    Cell ** map = generateMap(&x,&y);
    placeWallsOnAnEdge(map,x,y);
    placeTargets(map,x,y);
    placeAdditionalTerrainWalls(map, x,y);
    placeRobots(map,x,y);


	int cible,robot,dif,player;
	int bestScore; // prediction score
	char *robotEmojis[] = {"\U0001F916", "\U0001F47E", "\U0001F47D", "\U0001F47B"}; //list containing robot emoji
	robot=rand()%3+1; //define which robot
	cible=rand()%17+1; // define which target
	printf("\nmanche %d\n",nb_manche);
	dif=harder(); //asks for the level of difficulty
	printf("\nla partie va se lancer dans 2 sec !! \n");
	sleep(2); //wait 10 sec
	printMap(map,x,y);
	printf("\nrobot: %s to cible: %d\n",robotEmojis[robot],cible);
	if(chrono(dif)==1){ //call chrono and once the timer ends returns 1
		printf("\033[H\033[2J"); //delete all
	}
	player=play(nb_joueur,&bestScore,nom); // define who play this party
    if (player==0){
        printf("Tout le monde a dit que le niveau était impossible, alors on part pour une nouvelle manche \n%d",player);
    }else{
        printMap(map,x,y);
        printf("\%s a annoncer le plus petit chemin avec %d coup, il va donc jouer\n",nom[player-1],bestScore);
        int nb_coup_fait=moveTurn(map, cible, x,y,robot+1);
        gestionPoint(bestScore,nb_coup_fait, tabScore,player,nb_joueur);
        showScore(tabScore,nb_joueur,nom);
        bestScore=0;
    }


}
