//
// Created by Sebastian Morera on 2021-09-22.
//

#ifndef MARIO_SOKOBAN_EDITEUR_H
#define MARIO_SOKOBAN_EDITEUR_H

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "fichiers.h"
#include "constantes.h"

void editeur(SDL_Renderer *renderer);
int howManyMarios(int carte[][NB_BLOCS_HAUTEUR]);

#endif //MARIO_SOKOBAN_EDITEUR_H
