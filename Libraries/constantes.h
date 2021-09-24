//
// Created by Sebastian Morera on 2021-09-22.
//

#ifndef MARIO_SOKOBAN_CONSTANTES_H
#define MARIO_SOKOBAN_CONSTANTES_H

#define TAILLE_BLOC         34 // Taille d'un bloc (carré) en pixels
#define NB_BLOCS_LARGEUR    12
#define NB_BLOCS_HAUTEUR    12
#define WINDOW_WIDTH        TAILLE_BLOC * NB_BLOCS_LARGEUR
#define WINDOW_HEIGHT       TAILLE_BLOC * NB_BLOCS_HAUTEUR

enum {HAUT, BAS, GAUCHE, DROITE};
enum {VIDE, MUR, CAISSE, OBJECTIF, MARIO, CAISSE_OK};

#endif //MARIO_SOKOBAN_CONSTANTES_H
