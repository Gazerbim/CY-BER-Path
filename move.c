#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "fonction.h"



int checkMove(Cell** map, char dir, int Posx, int Posy ){
    //en fonction du type de mvt, verifier si il y a un robot 2 cases plus loin ou une cible une case plus loin (dans la direction), et si oui return 1, sinon return 0.
    if(dir=='z'){
        if( map[Posy-1][Posx].wall>0){
            return 1;
        }
        else if(map[Posy-2][Posx].robot>0){
            return 1;
        }
    }
    if(dir=='q'){
        if( map[Posy][Posx-1].wall>0){
            return 1;
        }
        else if(map[Posy][Posx-2].robot>0 ){
            return 1;
        }
    }
    if(dir=='s'){
        if(map[Posy+1][Posx].wall>0){
            return 1;
        }
        else if(map[Posy+2][Posx].robot>0   ){
            return 1;
        }
    }
    if(dir=='d'){
        if(  map[Posy][Posx+1].wall>0){
            return 1;
        }
        else if(map[Posy][Posx+2].robot>0 ){
            return 1;
        }
    }
    else if(dir !='z' && dir !='d' && dir!='q' && dir!= 's'){
        printf("Direction invalide!\n");
        return 2;
    }
    return 0;
}

int findRobot(Cell ** map, int *x, int *y, int widthMap,int lenghtMap, int numrobot){
    for(int i=0; i<lenghtMap;i++){
        for(int j=0; j<widthMap; j++){
            if (map[i][j].robot==numrobot){
                *x=j;
                *y=i;
                return 1;
            }
        }
    }
    return 0;
}

int checkTarget(Cell ** map, int Rx, int Ry, int targ){
    if (map[Ry][Rx].target==targ){
        return 1;
    }
    return 0;
}

void updateCoord(Cell ** map, int x, int y, int newX, int newY, int numRobot){
    map[y][x].robot=0;
    map[newY][newX].robot=numRobot;
    }

/*char getch_ncurses() {
    char ch;
    initscr(); // Initialisation de ncurses
    cbreak(); // Désactiver la mise en mémoire tampon de ligne
    noecho(); // Désactiver l'écho de la saisie
    //printw("direction ?\r");
    //fflush(stdout);
    //refresh();
    //keypad(stdscr, TRUE); // Activer la prise en charge des touches spéciales
    ch = getch(); // Lire une seule touche
    endwin(); // Restaurer le mode terminal normal
    return ch;
}*/

int moveInDirection(Cell** map, int lenghtMap,int widthMap, int targ,int numRobot ){
    int x=0;
    int y=0;
    int safeCoord=findRobot(map, &x, &y,lenghtMap,widthMap, numRobot);
    if (safeCoord=0){
        printf("erreur : Robot non trouve");
        exit(1);
    }
    int Rx=x; // new coordinates of the robot
    int Ry=y; // ----------------------------
    char dir;
    //commence la boucle pour bouger
    int checkEnd=0;
    printf("direction ?");
    //fflush(stdout);
    //dir =getch_ncurses();
    scanf(" %c",&dir);
    while (checkEnd==0){
        checkEnd=checkMove(map, dir, Rx, Ry);
        if(checkEnd==2){
            return 2;
        }
        if (checkEnd==0){
            if(dir=='z'){
            	Ry -= 2;
            }
            if(dir=='q'){
            	Rx -= 2;
            }
            if(dir=='s'){
                Ry += 2;
            }
            if(dir=='d'){
                Rx += 2;
            }
	    printf("\033[H\033[2J");
            updateCoord(map, x, y, Rx, Ry, numRobot);
            printMap(map, lenghtMap, widthMap);
	    x=Rx;
	    y=Ry;
	    usleep(50000);

        }
    }
    //printf("\033[H\033[2J");
    //updateCoord(map, x, y, Rx, Ry, numRobot);
    //printMap(map, lenghtMap, widthMap);
    int cond=checkTarget(map, Rx, Ry, targ);
        if (cond==1){
            return 1;
        }
    return 0;
}


int abandon(int a){
	int reponse;
	int verification;
	if(a==10){
		do{
		printf("\nvoulez-vous abandonnez ?\n\n1 --> Oui\n2 --> Nan\n");
		scanf("%d", &reponse);
		if(reponse==1 || reponse==2){
			verification=1;
		}
		else{
			verification=0;
			while(getchar() != '\n'); //flushes the input buffer until a newline character ('\n') is encountered
            		printf("nombre saisie invalide veullez réessayer.\n");
		}
		}while(verification!=1);
		if (reponse==1){
			return -1;
		}
		if(reponse==2){
			return 0;
		}
	}
	return a;
}
int moveTurn(Cell ** map, int targ, int lenghtMap, int widthMap, int numRobot ){
    int cpt=0;
    int endGame=0;
    int i=0;
    while (endGame!=1){
        endGame=moveInDirection(map, lenghtMap,widthMap, targ, numRobot);
        if(endGame!=2){
            cpt++;
	}
	i=abandon(i);
	if (i==-1){
        return -1;//the player didn't manage to find the path
	}
	i++;
    }
    //printf("\ncompteur : %d\n",cpt);
    return cpt;
}
