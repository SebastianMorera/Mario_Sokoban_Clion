//
// Created by Sebastian Morera on 2021-09-22.
//

#include "jeu.h"

void jouer(SDL_Renderer *renderer)
{
    int continuer = 1, objectifsRestants = 0, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    SDL_Surface *mario[4] = {NULL}; // 4 surfaces pour 4 directions de mario
    SDL_Surface *mur = NULL, *caisse = NULL, *caisseOK = NULL, *objectif = NULL, *marioActuel = NULL;
    SDL_Rect position, positionJoueur;
    SDL_Event event;

    // Chargement des sprites (décors, personnage...)
    mur = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mur.jpg");
    SDL_Texture *textureMur = SDL_CreateTextureFromSurface(renderer, mur);
    SDL_FreeSurface(mur);

    caisse = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/caisse.jpg");
    SDL_Texture *textureCaisse = SDL_CreateTextureFromSurface(renderer, caisse);
    SDL_FreeSurface(caisse);

    caisseOK = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/caisse_ok.jpg");
    SDL_Texture *textureCaisseOK = SDL_CreateTextureFromSurface(renderer, caisseOK);
    SDL_FreeSurface(caisseOK);

    objectif = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/objectif.png");
    SDL_Texture *textureObjectif = SDL_CreateTextureFromSurface(renderer, objectif);
    SDL_FreeSurface(objectif);

    mario[BAS] = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mario_bas.gif");
    SDL_Texture *textureMario_Bas = SDL_CreateTextureFromSurface(renderer, mario[BAS]);
    marioActuel = mario[BAS]; // Mario sera dirigé vers le bas au départ
    SDL_Texture *textureMarioActuel = SDL_CreateTextureFromSurface(renderer, marioActuel);
    SDL_FreeSurface(mario[BAS]);

    mario[GAUCHE] = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mario_gauche.gif");
    SDL_Texture *textureMario_Gauche = SDL_CreateTextureFromSurface(renderer, mario[GAUCHE]);
    SDL_FreeSurface(mario[GAUCHE]);

    mario[HAUT] = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mario_haut.gif");
    SDL_Texture *textureMario_Haut = SDL_CreateTextureFromSurface(renderer, mario[HAUT]);
    SDL_FreeSurface(mario[HAUT]);

    mario[DROITE] = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mario_droite.gif");
    SDL_Texture *textureMario_Droite = SDL_CreateTextureFromSurface(renderer, mario[DROITE]);
    SDL_FreeSurface(mario[DROITE]);

    // Chargement du niveau
    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE); // On arrête le jeu si on n'a pas pu charger le niveau

    // Recherche de la position de Mario au départ
    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            if (carte[i][j] == MARIO) // Si Mario se trouve à cette position
            {
                positionJoueur.x = i;
                positionJoueur.y = j;
                carte[i][j] = VIDE;
            }
        }
    }

    play_audio_start();

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

                    case SDLK_UP:
                        marioActuel = mario[HAUT];
                        textureMarioActuel = textureMario_Haut;
                        deplacerJoueur(carte, &positionJoueur, HAUT);
                        break;

                    case SDLK_DOWN:
                        marioActuel = mario[BAS];
                        textureMarioActuel = textureMario_Bas;
                        deplacerJoueur(carte, &positionJoueur, BAS);
                        break;

                    case SDLK_RIGHT:
                        marioActuel = mario[DROITE];
                        textureMarioActuel = textureMario_Droite;
                        deplacerJoueur(carte, &positionJoueur, DROITE);
                        break;

                    case SDLK_LEFT:
                        marioActuel = mario[GAUCHE];
                        textureMarioActuel = textureMario_Gauche;
                        deplacerJoueur(carte, &positionJoueur, GAUCHE);
                        break;

                    default:
                        break;
                }
                break;
        }

        /* On efface l'écran */
        SDL_RenderClear(renderer); // Clear the entire screen to our selected color.

        // Placement des objets à l'écran
        objectifsRestants = 0;

        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_QueryTexture(textureMur, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureMur, NULL, &position);
                        break;

                    case CAISSE:
                        SDL_QueryTexture(textureCaisse, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureCaisse, NULL, &position);
                        break;

                    case CAISSE_OK:
                        SDL_QueryTexture(textureCaisseOK, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureCaisseOK, NULL, &position);
                        break;

                    case OBJECTIF:
                        SDL_QueryTexture(textureObjectif, NULL, NULL, &position.w, &position.h);
                        SDL_RenderCopy(renderer, textureObjectif, NULL, &position);
                        objectifsRestants = 1;
                        break;

                    default:
                        break;
                }
            }
        }

        // Si on n'a trouvé aucun objectif sur la carte, c'est qu'on a gagné
        if (!objectifsRestants)
            continuer = 0;

        // On place le joueur à la bonne position
        position.x = positionJoueur.x * TAILLE_BLOC;
        position.y = positionJoueur.y * TAILLE_BLOC;

        SDL_QueryTexture(textureMarioActuel, NULL, NULL, &position.w, &position.h);
        SDL_RenderCopy(renderer, textureMarioActuel, NULL, &position);

        SDL_RenderPresent(renderer);

    } // Fin du while(continuer)

    if (!objectifsRestants)
    {
        play_audio_completed();
        levelCompleted(renderer);
    }
}

void deplacerJoueur(int carte[][NB_BLOCS_HAUTEUR], SDL_Rect *pos, int direction)
{
    switch (direction)
    {
        case HAUT:
            if (pos->y - 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x][pos->y - 1] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x][pos->y - 1] == CAISSE || carte[pos->x][pos->y - 1] == CAISSE_OK) &&
                (pos->y - 2 < 0 || carte[pos->x][pos->y - 2] == MUR || carte[pos->x][pos->y - 2] == CAISSE || carte[pos->x][pos->y - 2] == CAISSE_OK))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur ! On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x][pos->y - 1], &carte[pos->x][pos->y - 2]);
            pos->y--; // On peut enfin faire monter le joueur (oufff !)
            break;

        case BAS:
            if (pos->y + 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x][pos->y + 1] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x][pos->y + 1] == CAISSE || carte[pos->x][pos->y + 1] == CAISSE_OK) &&
                (pos->y + 2 < 0 || carte[pos->x][pos->y + 2] == MUR || carte[pos->x][pos->y + 2] == CAISSE || carte[pos->x][pos->y + 2] == CAISSE_OK))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur ! On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x][pos->y + 1], &carte[pos->x][pos->y + 2]);
            pos->y++; // On peut enfin faire monter le joueur (oufff !)
            break;

        case GAUCHE:
            if (pos->x - 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x - 1][pos->y] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x - 1][pos->y] == CAISSE || carte[pos->x - 1][pos->y - 1] == CAISSE_OK) &&
                (pos->x - 2 < 0 || carte[pos->x - 2][pos->y] == MUR || carte[pos->x - 2][pos->y] == CAISSE || carte[pos->x - 2][pos->y] == CAISSE_OK))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur ! On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x - 1][pos->y], &carte[pos->x - 2][pos->y]);
            pos->x--; // On peut enfin faire monter le joueur (oufff !)
            break;

        case DROITE:
            if (pos->x + 1 < 0) // Si le joueur dépasse l'écran, on arrête
                break;
            if (carte[pos->x + 1][pos->y] == MUR) // S'il y a un mur, on arrête
                break;
            // Si on veut pousser une caisse, il faut vérifier qu'il n'y a pas de mur derrière (ou une autre caisse, ou la limite du monde)
            if ((carte[pos->x + 1][pos->y] == CAISSE || carte[pos->x + 1][pos->y + 1] == CAISSE_OK) &&
                (pos->x + 2 < 0 || carte[pos->x + 2][pos->y] == MUR || carte[pos->x + 2][pos->y] == CAISSE || carte[pos->x + 2][pos->y] == CAISSE_OK))
                break;

            // Si on arrive là, c'est qu'on peut déplacer le joueur ! On vérifie d'abord s'il y a une caisse à déplacer
            deplacerCaisse(&carte[pos->x + 1][pos->y], &carte[pos->x + 2][pos->y]);
            pos->x++; // On peut enfin faire monter le joueur (oufff !)
            break;
        default:
            break;
    }
}

void deplacerCaisse(int *premiereCase, int *secondeCase)
{
    if (*premiereCase == CAISSE || *premiereCase == CAISSE_OK)
    {
        if (*secondeCase == OBJECTIF)
            *secondeCase = CAISSE_OK;
        else
            *secondeCase = CAISSE;

        if (*premiereCase == CAISSE_OK)
            *premiereCase = OBJECTIF;
        else
            *premiereCase = VIDE;
    }
}

void levelCompleted(SDL_Renderer *renderer)
{
    SDL_RenderClear(renderer); // Clear the entire screen
    SDL_Color colorBlack = {0, 0, 0}, colorWhite = {255, 255, 255};

    TTF_Font *police = TTF_OpenFont("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/angelina.ttf", 32);

    /// Congratulations text
    char *texteAfficher = "Congratulations, level solved !";
    SDL_Texture *textureTexte = NULL;
    SDL_Surface* surfaceTexte = TTF_RenderText_Shaded(police, texteAfficher, colorBlack, colorWhite);
    textureTexte = SDL_CreateTextureFromSurface(renderer, surfaceTexte);
    SDL_FreeSurface(surfaceTexte);

    SDL_Rect positionTexte; //create a rect
    positionTexte.x = 50;  //controls the rect's x coordinate
    positionTexte.y = 150; // controls the rect's y coordinte
    TTF_SizeText(police, texteAfficher, &positionTexte.w, &positionTexte.h);
    SDL_RenderCopy(renderer, textureTexte, NULL, &positionTexte);
    SDL_RenderPresent(renderer); // Afficher l'image de fond

    /// Timer initialization
    int tempsActuel = 0, tempsPrecedent = 0, compteur = 0;
    tempsActuel = SDL_GetTicks();

    while (compteur <= 3000)
    {
        tempsActuel = SDL_GetTicks();

        if (tempsActuel - tempsPrecedent >= 100) /* Si 100 ms se sont écoulées depuis le dernier tour de boucle */
        {
            compteur += 100;
            tempsPrecedent = tempsActuel; /* On met à jour le tempsPrecedent */
        }
    }
}

void play_audio_start()
{
    Mix_Music *musicStart = NULL;
    musicStart = Mix_LoadMUS("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/Level_Start.wav");
    if (Mix_PlayMusic(musicStart, 1) != 0) {
        printf("[Error] Could not play music : %s \n", Mix_GetError());
    }
}

void play_audio_completed()
{
    Mix_Music *musicStart = NULL;
    musicStart = Mix_LoadMUS("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/Level_completed.wav");
    if (Mix_PlayMusic(musicStart, 1) != 0) {
        printf("[Error] Could not play music : %s \n", Mix_GetError());
    }
}
