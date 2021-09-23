//
// Created by Sebastian Morera on 2021-09-22.
//

#ifndef MARIO_SOKOBAN_JEU_H
#define MARIO_SOKOBAN_JEU_H

#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "fichiers.h"

void jouer(SDL_Renderer *renderer);
void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction);
void deplacerCaisse(int *premiereCase, int *secondeCase);

#endif //MARIO_SOKOBAN_JEU_H
