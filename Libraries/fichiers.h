//
// Created by Sebastian Morera on 2021-09-22.
//

#ifndef MARIO_SOKOBAN_FICHIERS_H
#define MARIO_SOKOBAN_FICHIERS_H

#include <stdio.h>
#include "constantes.h"

int chargerNiveau(int niveau[][NB_BLOCS_HAUTEUR]);
int sauvegarderNiveau(int niveau[][NB_BLOCS_HAUTEUR]);

#endif //MARIO_SOKOBAN_FICHIERS_H
