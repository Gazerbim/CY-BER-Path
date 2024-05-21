#include "fonction.h"





void printMap(Cell ** map, int x, int y){ // Print the map : if a robot and a target are on the same cell, only the robot will be printed
    printf("\033[H\033[2J"); // clear the screen
    //printf("\x1b[44m"); //change the background color
    for(int i = 0; i<y; i++){
        for(int j = 0; j<x; j++){
            if (map[i][j].robot>0){
                if (map[i][j].robot==1){
                    printf("\U0001F916");
                }else if (map[i][j].robot==2){
                    printf("\U0001F47E");
                }else if (map[i][j].robot==3){
                    printf("\U0001F47D");
                }else if (map[i][j].robot==4){
                    printf("\U0001F47B");
                }
            }else if (map[i][j].target>=10){
                printf("%d", map[i][j].target);
            }else if (map[i][j].target>0){
                printf("%d ", map[i][j].target);
            }else if (map[i][j].wall){
                printf("\u2588\u2588");
            }else{
                printf("  ");
            }
        }
        printf("\n");
    }
    printf("\n");
}

void addBorderWalls(Cell **map, int x,int y){ // add the edge's walls
    //printf("Starting edges placement...\n");
    for(int i = 0;i<x;i++){
        map[0][i].wall=1;
    }
    sleep(0.1);
    //printf("|");
    for(int i = 0;i<y;i++){
        map[i][x-1].wall=1;
    }
    //printf("|");
    for(int i = 0; i<x;i++){
        map[y-1][i].wall=1;
    }
    //printf("|");
    for(int i = 0;i<y;i++){
        map[i][0].wall=1;
    }
    //printf("|\n");
    //printf("Edges placement finished !\n");
}


Cell ** generateMap(int *x, int *y){ // Gen the blank map with the edges as walls
    int width = rand() % 6 + 15; // def of the playground's width
    int length = rand() % 6 + 15;  // def of the playground's length
    //printf("\033[H\033[2J Map coordinates generation");


    *y = width*2+1;
    *x = length*2+1;
    //printf("Map coordinates set !\n Starting Cells creation...\n");

    Cell ** map = malloc((*y)*sizeof(Cell*)); // Creation of the playground
    if (map==NULL){  // allocation assertion
        printf("Tab malloc failed, exiting the game\n");
        exit(1);
    }else{
        for(int i = 0; i < *y; i++){ // Corrected loop for y
            map[i] = malloc((*x) * sizeof(Cell));
            if (map[i]==NULL){  // allocation assertion
                free(map);
                printf("Tab[i] malloc failed, exiting the game\n");
                exit(2);
            }
            for (int j = 0; j < *x; j++) { // initialize all the cells' values at 0
                map[i][j].robot = 0;
                map[i][j].target = 0;
                map[i][j].wall = 0;
            }
            //printf("|");
        }
    }
    //printf("\n Cell generation done ! Adding border walls...\n");
    addBorderWalls(map,*x,*y);
    //printf("Border walls added ! Blank map done\n");
    return map;
}

int verifyTargetPlacement(Cell ** map, int xT, int yT){ // Verify if a target can be put at this location based on the rules
    //printf("    Starting target placement verification...");
    if (map[yT-2][xT-2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-2][xT].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-2][xT+2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT][xT-2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT][xT+2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+2][xT-2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+2][xT].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+2][xT+2].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT][xT].target>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }

    if (map[yT+2][xT-1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+2][xT+1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+1][xT-2].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-1][xT-2].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+1][xT+2].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-1][xT+2].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-2][xT-1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-2][xT+1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT-1][xT].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT][xT+1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT+1][xT].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    if (map[yT][xT-1].wall>0){
        //printf("Bad ! Retrying\n");
        return 1;
    }
    //printf("Checked ! Creating the target\n");
    return 0;
}

void ** placeTargets(Cell ** map, int x, int y){ // place all the targets in the map
    //printf("Starting target placement...\n");
    int xT, yT;
    int lMap = (x-1)/2; // calculate the "real" length of the map with all possibles robot-reachable cells (the cells where targets could be placed)
    int wMap = (y-1)/2;
    for(int i = 0; i<18; i++){
            //printf("Placing %dst target\n", i);
        do{
            xT = (rand()%(lMap-2))+1; // x of the target without the edges of the map
            yT = (rand()%(wMap-2))+1; // idem for y
            xT = xT*2+1;
            yT = yT*2+1;
        }while(verifyTargetPlacement(map, xT, yT)); // Verify if the target isn't next to another target

        map[yT][xT].target = i+1;
        int typeWall = rand()%4; // What walls will be placed next to the target
        if (typeWall==0){
            map[yT-1][xT].wall = 1;
            map[yT][xT+1].wall = 1;
            map[yT-1][xT+1].wall = 1;
        }
        if (typeWall==1){
            map[yT][xT-1].wall = 1;
            map[yT-1][xT].wall = 1;
            map[yT-1][xT-1].wall = 1;
        }
        if (typeWall==2){
            map[yT+1][xT].wall = 1;
            map[yT][xT-1].wall = 1;
            map[yT+1][xT-1].wall = 1;
        }
        if (typeWall==3){
            map[yT+1][xT].wall = 1;
            map[yT][xT+1].wall = 1;
            map[yT+1][xT+1].wall = 1;
        }
    }
    //printf("Target placement finished !\n");
}

void placeAdditionalTerrainWalls(Cell ** map, int xMap, int yMap){
    int xT, yT;
    int lMap = (xMap-1)/2; // calculate the "real" length of the map with all possibles robot-reachable cells (the cells where targets could be placed)
    int wMap = (yMap-1)/2;
    int stop = 0;  // to stop the program if it see that there is not enough place
    int counter = 0;
    for(int i = 0; i<50 && stop==0;i++){
            counter = 0;
        do{
            xT = (rand()%(lMap-2))+1; // x of the wall without the edges of the map
            yT = (rand()%(wMap-2))+1; // idem for y
            xT = xT*2+1;
            yT = yT*2+1;
            if(counter>=15){  // stopping the program if there is not enough place
                stop = 1;
            }
            counter++;
        }while(verifyTargetPlacement(map, xT, yT)&&!stop); // Verify if the wall isn't next to another or something else
        if (!stop){
            int typeWall = rand()%4; // What walls will be placed
            if (typeWall==0){
                map[yT-1][xT].wall = 1;
                map[yT][xT+1].wall = 1;
                map[yT-1][xT+1].wall = 1;
            }
            if (typeWall==1){
                map[yT][xT-1].wall = 1;
                map[yT-1][xT].wall = 1;
                map[yT-1][xT-1].wall = 1;
            }
            if (typeWall==2){
                map[yT+1][xT].wall = 1;
                map[yT][xT-1].wall = 1;
                map[yT+1][xT-1].wall = 1;
            }
            if (typeWall==3){
                map[yT+1][xT].wall = 1;
                map[yT][xT+1].wall = 1;
                map[yT+1][xT+1].wall = 1;
            }
        }
    }
}

void placeWallsOnAnEdge(Cell ** map, int x, int y){ // Places 2 walls per edge
    //printf("Border walls placement started...\n");
    int wall1, wall2;
    do{
        wall1 = rand()%(x/2-2)*2+2;
        wall2 = rand()%(x/2-2)*2+2;
    }while(wall1==wall2);
    map[1][wall1].wall=1;
    map[1][wall2].wall=1;
    //printf("|");

    do{
        wall1 = rand()%(y/2-2)*2+2;
        wall2 = rand()%(y/2-2)*2+2;
    }while(wall1==wall2);
    map[wall1][1].wall=1;
    map[wall2][1].wall=1;
    //printf("|");

    do{
        wall1 = rand()%(y/2-2)*2+2;
        wall2 = rand()%(y/2-2)*2+2;
    }while(wall1==wall2);
    map[wall1][x-2].wall=1;
    map[wall2][x-2].wall=1;
    //printf("|");

    do{
        wall1 = rand()%(x/2-2)*2+2;
        wall2 = rand()%(x/2-2)*2+2;
    }while(wall1==wall2);
    map[y-2][wall1].wall=1;
    map[y-2][wall2].wall=1;
    //printf("|\nBorder walls placement finished !\n");
}

void placeRobots(Cell ** map, int x, int y){ // place robots
    //printf("\nRobot placement started...\n");
    int xR, yR;
    int lMap = (x-1)/2; // These two lines calculate the number of possibles cells without the walls' cells (LengthMap and WidthMap)
    int wMap = (y-1)/2;
    for(int i = 0; i<4; i++){
        do{
            xR = (rand()%(lMap-2))+1; // x of the robot without the edges of the map
            yR = (rand()%(wMap-2))+1; // idem for y
            xR = xR*2+1;
            yR = yR*2+1;
        }while((map[yR][xR].target>0)||(map[yR][xR].robot>0)); // Verify the robot placement
        map[yR][xR].robot = i+1;
        //printf("|");
    }
    //printf("\nRobot placement finished !\n");
}

