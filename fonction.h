#ifndef FONCTION_H
#define FONCTION_H

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define RED_TEXT "\x1b[31m"
#define RESET_TEXT "\x1b[0m"

typedef struct{ // definition of a player for save the score 
    char name[50];
    int score;
}Player;

typedef struct{  // definition of a table cell
    int wall;
    int target;
    int robot;
}Cell;

void top10Score(int nb_players,Player *Playerss);
void writeBestScore(Player bestplayers[], int count);
int readBestScore(Player bestplayers[]);
void showPlayer(Player Playerss[], int n);
void fusionner(Player tab[], int debut,int milieu, int fin);
void triFusionRec(Player tab[],int debut,int fin);
void triFusion(Player tab[], int size);
void printMapRed(Cell ** map, int x, int y,int cible);
void addBorderWalls(Cell **map, int x,int y);
Cell ** generateMap(int *x, int *y);
int verifyTargetPlacement(Cell ** map, int xT, int yT);
void ** placeTargets(Cell ** map, int x, int y);
void placeAdditionalTerrainWalls(Cell ** map, int xMap, int yMap);
void placeWallsOnAnEdge(Cell ** map, int x, int y);
void placeRobots(Cell ** map, int x, int y);
int checkMove(Cell** map, char dir, int Posx, int Posy );
int findRobot(Cell ** map, int *x, int *y, int widthMap,int lenghtMap, int numrobot);
int moveInDirection(Cell** map, int lenghtMap,int widthMap, int targ,int numRobot);
int abandon(char a);
int moveTurn(Cell ** map, int targ, int lenghtMap, int widthMap, int numRobot );
int chrono(int a);
int harder();
int play(int nb_joueur, int *best,char **nom);
int gestionPoint(int nb_coup_prevu,int nb_coup_fait,int *tabScore,int player,int nb_joueur);
void showScore(int *tabScore, int nb_joueur,char **nom);
void finalMessage(char **nom, int *tabScore,int nb_joueur);
void game(int nb_joueur,int *tabScore,int nb_manche,char **nom);
void viderBuffer();
#endif
