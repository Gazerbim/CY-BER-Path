#include "fonction.h"



int checkMove(Cell** map, char dir, int Posx, int Posy ){
    //depending on the type of mvt, check if there is a robot 2 squares further or a target one square further (in the direction), and if yes return 1, otherwise return 0.
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
    else if(dir !='z' && dir !='d' && dir!='q' && dir!= 's' && dir!= '*'){ //check to make sure you typed a valid command
        printf("Direction invalide!\n");
        return 2;
    }
    return 0;
}

int findRobot(Cell ** map, int *x, int *y, int widthMap,int lenghtMap, int numrobot){ //find the robot's coordinates
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

int checkTarget(Cell ** map, int Rx, int Ry, int targ){ //check if the robot is on the target
    if (map[Ry][Rx].target==targ){ // use the robot's coordinates to check if his and the target's matches.
        return 1;
    }
    return 0;
}

void updateCoord(Cell ** map, int x, int y, int newX, int newY, int numRobot){ // updates the new coordinates of the robot and deletes the previous ones
    map[y][x].robot=0;
    map[newY][newX].robot=numRobot;
    }



int moveInDirection(Cell** map, int lenghtMap,int widthMap, int targ,int numRobot){ //return the direction to function moveturn
    int x=0;
    int y=0;
    int safeCoord=findRobot(map, &x, &y,lenghtMap,widthMap, numRobot);
    if (safeCoord=0){ // check if there's no problem with the robot's coordinates
        printf("Erreur : Robot non trouvé, le jeu va se fermer.");
        exit(1);
    }
    int Rx=x; // new coordinates of the robot
    int Ry=y; // ----------------------------
    //start the loop to move
    int checkEnd=0;
    printf("Entrez la direction vers laquelle le robot va aller :\nHaut = z\nGauche = q\nDroite = d\nBas = s\nAbandonner = *\nReponse : ");
    viderBuffer(); // select only the 1st character in case the player inputs more than 1 caracter.
    char dir;
    scanf(" %c",&dir); // get the value for the direction
    while (checkEnd==0){ // while there's no wall or other robot in front of the player.
        checkEnd=checkMove(map, dir, Rx, Ry);
	if(dir=='*'){ // in case of abandon.
		return -1;
	    }
        if(checkEnd==2){ // in case of invalid command
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
	    printMapRed(map,lenghtMap,widthMap,targ);
            
	    x=Rx;
	    y=Ry;
	    usleep(50000);

        }
    }
    printMapRed(map,lenghtMap,widthMap,targ);
    int cond=checkTarget(map, Rx, Ry, targ);
        if (cond==1){ // if the robot is on the target.
            return 1;
        }
    return 0;
}


int abandon(char a){ // in case the player want to give up.
	if(a=='*'){
		printf("\nVous avez décidé d'abandonner la partie !\n");
		return 0;
	}
	return 1;
}
int moveTurn(Cell ** map, int targ, int lenghtMap, int widthMap, int numRobot ){ // will run while the player as lons as the player don't reach the target, or don't abandon.
    int cpt=0;
    int endGame=0;
    while (endGame!=1){ // while the player didn't reach the target;
        endGame=moveInDirection(map, lenghtMap,widthMap, targ, numRobot);
	if (endGame==-1){
	printf("\n Vous avez décidé d'abandonner la partie \n");
        return -1;//the player didn't manage to find the path
	}
        if(endGame!=2){ // will increment the movement counter by 1 with each movement
            cpt++;
        }
    }
    //printf("\ncompteur : %d\n",cpt);
    return cpt;
}
