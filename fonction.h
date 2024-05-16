#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


typedef struct{  // definition of a table cell
    int wall;
    int target;
    int robot;
}Cell;

void printMap(Cell ** map, int x, int y);
void addBorderWalls(Cell **map, int x,int y);
Cell ** generateMap(int *x, int *y);
int verifyTargetPlacement(Cell ** map, int xT, int yT);
void ** placeTargets(Cell ** map, int x, int y);
void placeAdditionalTerrainWalls(Cell ** map, int xMap, int yMap);
void placeWallsOnAnEdge(Cell ** map, int x, int y);
void placeRobots(Cell ** map, int x, int y);
int checkMove(Cell** map, char dir, int Posx, int Posy );
int findRobot(Cell ** map, int *x, int *y, int widthMap,int lenghtMap, int numrobot);
int moveInDirection(Cell** map, int lenghtMap,int widthMap, int targ,int numRobot );
int abandon(int a);
int moveTurn(Cell ** map, int targ, int lenghtMap, int widthMap, int numRobot );
int chrono(int a);
int harder();
int play(int nb_joueur, int *best,char **nom);
int gestionPoint(int nb_coup_prevu,int nb_coup_fait,int *tabScore,int player,int nb_joueur);
void showScore(int *tabScore, int nb_joueur,char **nom);
void finalMessage(char **nom, int *tabScore,int nb_joueur);
void game(int nb_joueur,int *tabScore,int nb_manche,char **nom);

#endif