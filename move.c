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
    else if(dir !='z' && dir !='d' && dir!='q' && dir!= 's' && dir!= '*'){
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



int moveInDirection(Cell** map, int lenghtMap,int widthMap, int targ,int numRobot){ //return the direction to function moveturn
    int x=0;
    int y=0;
    int safeCoord=findRobot(map, &x, &y,lenghtMap,widthMap, numRobot);
    if (safeCoord=0){
        printf("Erreur : Robot non trouvé, le jeu va se fermer.");
        exit(1);
    }
    int Rx=x; // new coordinates of the robot
    int Ry=y; // ----------------------------
    //commence la boucle pour bouger
    int checkEnd=0;
    printf("Entrez la direction vers laquelle le robot va aller :\nHaut = z\nGauche = q\nDroite = d\nBas = s\nAbandonner = *\nReponse : ");
    char dir;
    scanf(" %c",&dir); // get the value from the direction
    while (checkEnd==0){
        checkEnd=checkMove(map, dir, Rx, Ry);
	if(dir=='*'){
		return -1;
	    }
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
	    printfMapRed(map,lenghtMap,widthMap,targ);
            
	    x=Rx;
	    y=Ry;
	    usleep(50000);

        }
    }
    printMap(map, lenghtMap, widthMap);
    //printf("\033[H\033[2J");
    //updateCoord(map, x, y, Rx, Ry, numRobot);
    //printMap(map, lenghtMap, widthMap);
    int cond=checkTarget(map, Rx, Ry, targ);
        if (cond==1){
            return 1;
        }
    return 0;
}


int abandon(char a){
	if(a=='*'){
		printf("\nVous avez décidé d'abandonner la partie !\n");
		return 0;
	}
	return 1;
}
int moveTurn(Cell ** map, int targ, int lenghtMap, int widthMap, int numRobot ){
    int cpt=0;
    int endGame=0;
    while (endGame!=1){
        endGame=moveInDirection(map, lenghtMap,widthMap, targ, numRobot);
	if (endGame==-1){
	printf("\n Vous avez décidé d'abandonner la partie \n");
        return -1;//the player didn't manage to find the path
	}
        if(endGame!=2){
            cpt++;
        }
    }
    //printf("\ncompteur : %d\n",cpt);
    return cpt;
}
