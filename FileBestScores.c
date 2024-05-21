#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "fonction.h"

void update_score(char **nom, int *tabScore, int nb_joueur){
    FILE* bestscore = NULL;
    fopen("BestScores.txt", "r+");
    if (bestscore == NULL){
        printf("ouverture impossible");
        exit();
        }

    char content[1000];
    fgets(content, 999, bestscore)

    fclose(bestscore);
