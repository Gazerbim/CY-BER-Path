#include "fonction.h"

int main(){
	srand(time(NULL));
	int nb_joueur,nb_manche,verification;
	do{
		printf("combien de joueur vont jouer ");
		scanf("%d",&nb_joueur);
		if(nb_joueur>0){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
            		printf("Veuillez saisir un nombre valide supérieur à 0.\n");
		}
	}while(verification!=1);
	int nmb_lettre;
	char *p=NULL;
	char prenom[100];
	char **nom=malloc(nb_joueur*sizeof(char*));
	if(nom==NULL){
		printf("Tab malloc failed, exiting the game\n");
		exit(1);
	}
	for(int i=0;i<nb_joueur;i++){
		printf("saisir le %d eme joueur\n",i+1);
		scanf("%s",prenom);
		nmb_lettre=strlen(prenom);
		p=malloc((nmb_lettre+1)*sizeof(char));
		if(p==NULL){
			exit(i+2);
		}
		int j=0;
		while(prenom[j]!='\0'){
			p[j]=prenom[j];
			j++;
		}
		p[j]='\0';
		nom[i]=p;
	}

	for(int i=0;i<nb_joueur;i++);
	do{
		printf("\nCombien de manche voulez vous faire ?\n");
		scanf("%d",&nb_manche);
		if(nb_manche>0){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
            		printf("Veuillez saisir un nombre valide supérieur à 0.\n");
		}
	}while(verification!=1);
	int *tabScore=malloc(nb_joueur*sizeof(int)); //for stock the score of player
	if(tabScore==NULL){
		printf("Tab malloc failed, exiting the game\n");
		exit(1);
	}
	for(int i=0;i<nb_joueur;i++){
		tabScore[i]=0;
	}
	for (int i=nb_manche;i>0;i--){
		game(nb_joueur,tabScore,nb_manche-i+1,nom);
	}
	finalMessage(nom,tabScore,nb_joueur);


	return 0;
}
