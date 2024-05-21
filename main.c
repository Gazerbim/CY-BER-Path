#include "fonction.h"

int main(){
	srand(time(NULL));//initialisation of the random seed
	int nb_players,nb_games,verification;
	printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
	do{
		printf("Combien de joueur(s) vont jouer ?: ");
		scanf("%d",&nb_players);
		if(nb_players>0){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
                    printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
            		printf(" /!\ Veuillez saisir un nombre valide supérieur à 0. /!\ \n");
		}
	}while(verification!=1);
	int nmb_letter;
	char *p=NULL;
	char prenom[100];
	char **names=malloc(nb_players*sizeof(char*)); //malloc of the names array
	if(names==NULL){
        printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
		printf("L'allocation du tableau a planté, le programme va se fermer.\n");
		exit(1);
	}
	for(int i=0;i<nb_players;i++){
	    printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
		printf("Saisir le pseudo du %deme joueur :",i+1);
		scanf("%s",prenom);
		nmb_letter=strlen(prenom);
		p=malloc((nmb_letter+1)*sizeof(char));
		if(p==NULL){
			exit(i+2);
		}
		int j=0;
		while(prenom[j]!='\0'){
			p[j]=prenom[j];
			j++;
		}
		p[j]='\0';
		names[i]=p;
	}

	for(int i=0;i<nb_players;i++);
	do{
        printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
		printf("\nCombien de manche(s) voulez vous faire ?:");
		scanf("%d",&nb_games);
		if(nb_games>0){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
                    printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
            		printf("/!\ Veuillez saisir un nombre valide superieur à 0. /!\\n");
		}
	}while(verification!=1);
	int *tabScore=malloc(nb_players*sizeof(int)); //to store the scores of the players
	if(tabScore==NULL){
        printf("\033[H\033[2JBIENVENUE DANS CY-BERPATH!\n\n\n");
		printf("L'alloc n'a pas réussi, le programme va se fermer.\n");
		exit(5);
	}
	for(int i=0;i<nb_players;i++){
		tabScore[i]=0;
	}
	for (int i=nb_games;i>0;i--){
		game(nb_players,tabScore,nb_games-i+1,names);
	}
	finalMessage(names,tabScore,nb_players); //print the final message.

	return 0;
}
