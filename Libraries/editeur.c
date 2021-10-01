//
// Created by Sebastian Morera on 2021-09-22.
//

#include "editeur.h"

void editeur(SDL_Renderer *renderer)
{
    SDL_Surface *mur = NULL, *caisse = NULL, *objectif = NULL, *mario = NULL, *caisseOk = NULL;
    SDL_Rect position, positionObject;
    SDL_Event event;

    int continuer = 1, clicGaucheEnCours = 0, clicDroitEnCours = 0, nbMario = 0;
    int objetActuel = MUR, i = 0, j = 0;
    int carte[NB_BLOCS_LARGEUR][NB_BLOCS_HAUTEUR] = {0};

    // Loading of objects and level
    mur = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mur.jpg");
    SDL_Texture *textureMur = SDL_CreateTextureFromSurface(renderer, mur);
    SDL_FreeSurface(mur);
    SDL_QueryTexture(textureMur, NULL, NULL, &position.w, &position.h);
    SDL_QueryTexture(textureMur, NULL, NULL, &positionObject.w, &positionObject.h);

    caisse = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/caisse.jpg");
    SDL_Texture *textureCaisse = SDL_CreateTextureFromSurface(renderer, caisse);
    SDL_FreeSurface(caisse);
    SDL_QueryTexture(textureCaisse, NULL, NULL, &position.w, &position.h);
    SDL_QueryTexture(textureCaisse, NULL, NULL, &positionObject.w, &positionObject.h);

    objectif = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/objectif.png");
    SDL_Texture *textureObjectif = SDL_CreateTextureFromSurface(renderer, objectif);
    SDL_FreeSurface(objectif);
    SDL_QueryTexture(textureObjectif, NULL, NULL, &position.w, &position.h);
    SDL_QueryTexture(textureObjectif, NULL, NULL, &positionObject.w, &positionObject.h);

    mario = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/mario_bas.gif");
    SDL_Texture *textureMario = SDL_CreateTextureFromSurface(renderer, mario);
    SDL_FreeSurface(mario);
    SDL_QueryTexture(textureMario, NULL, NULL, &position.w, &position.h);
    SDL_QueryTexture(textureMario, NULL, NULL, &positionObject.w, &positionObject.h);

    caisseOk = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/caisse_ok.jpg");
    SDL_Texture *textureCaisseOk = SDL_CreateTextureFromSurface(renderer, caisseOk);
    SDL_FreeSurface(caisseOk);
    SDL_QueryTexture(textureCaisseOk, NULL, NULL, &position.w, &position.h);
    SDL_QueryTexture(textureCaisseOk, NULL, NULL, &positionObject.w, &positionObject.h);

    if (!chargerNiveau(carte))
        exit(EXIT_FAILURE);

    nbMario = howManyMarios(carte);

    SDL_ShowCursor(SDL_DISABLE);

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    // On met l'objet actuellement choisi (mur, caisse...) à l'endroit du clic
                    if(objetActuel == MARIO)
                    {
                        nbMario = howManyMarios(carte);
                        if(nbMario != 1)
                        {
                            carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                            clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
                        }
                    }
                    else
                    {
                        carte[event.button.x / TAILLE_BLOC][event.button.y / TAILLE_BLOC] = objetActuel;
                        clicGaucheEnCours = 1; // On retient qu'un bouton est enfoncé
                    }
                }
                else if (event.button.button == SDL_BUTTON_RIGHT) // Clic droit pour effacer
                {
                    if(objetActuel == MARIO)
                    {
                        if(nbMario == 1)
                            nbMario--;
                    }
                    carte[event.button.x / TAILLE_BLOC][event.button.y /TAILLE_BLOC] = VIDE;
                    clicDroitEnCours = 1;
                }
                break;

            case SDL_MOUSEBUTTONUP: // On désactive le booléen qui disait qu'un bouton était enfoncé
                if (event.button.button == SDL_BUTTON_LEFT)
                    clicGaucheEnCours = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    clicDroitEnCours = 0;
                break;

            case SDL_MOUSEMOTION:
                positionObject.x = event.motion.x - (TAILLE_BLOC/2);
                positionObject.y = event.motion.y - (TAILLE_BLOC/2);
                if (clicGaucheEnCours) // Si on déplace la souris et que le bouton gauche de la souris est enfoncé
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = objetActuel;
                }
                else if (clicDroitEnCours) // Pareil pour le bouton droit de la souris
                {
                    carte[event.motion.x / TAILLE_BLOC][event.motion.y / TAILLE_BLOC] = VIDE;
                }
                break;

            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        continuer = 0;
                        break;

                    case SDLK_s:
                        sauvegarderNiveau(carte);
                        break;

                    case SDLK_c:
                        chargerNiveau(carte);
                        break;

                    case SDLK_KP_1:
                        objetActuel = MUR;
                        break;

                    case SDLK_KP_2:
                        objetActuel = CAISSE;
                        break;

                    case SDLK_KP_3:
                        objetActuel = OBJECTIF;
                        break;

                    case SDLK_KP_4:
                        objetActuel = MARIO;
                        break;

                    case SDLK_KP_5:
                        objetActuel = CAISSE_OK;
                        break;
                }
                break;
        }

        SDL_RenderClear(renderer); // Clear the entire screen

        // Positioning of our objects on the screen
        for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
            {
                position.x = i * TAILLE_BLOC;
                position.y = j * TAILLE_BLOC;

                switch(carte[i][j])
                {
                    case MUR:
                        SDL_RenderCopy(renderer, textureMur, NULL, &position);
                        break;
                    case CAISSE:
                        SDL_RenderCopy(renderer, textureCaisse, NULL, &position);
                        break;
                    case OBJECTIF:
                        SDL_RenderCopy(renderer, textureObjectif, NULL, &position);
                        break;
                    case MARIO:
                        SDL_RenderCopy(renderer, textureMario, NULL, &position);
                        break;
                    case CAISSE_OK:
                        SDL_RenderCopy(renderer, textureCaisseOk, NULL, &position);
                        break;
                }
            }
        }

        switch(objetActuel)
        {
            case MUR:
                SDL_RenderCopy(renderer, textureMur, NULL, &positionObject);
                break;
            case CAISSE:
                SDL_RenderCopy(renderer, textureCaisse, NULL, &positionObject);
                break;
            case OBJECTIF:
                SDL_RenderCopy(renderer, textureObjectif, NULL, &positionObject);
                break;
            case MARIO:
                SDL_RenderCopy(renderer, textureMario, NULL, &positionObject);
                break;
            case CAISSE_OK:
                SDL_RenderCopy(renderer, textureCaisseOk, NULL, &positionObject);
                break;
            default:
                break;
        }

        SDL_RenderPresent(renderer);

    } // End of while loop

}

int howManyMarios(int carte[][NB_BLOCS_HAUTEUR])
{
    int nbMario = 0, i = 0, j = 0;

    for (i = 0 ; i < NB_BLOCS_LARGEUR ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_HAUTEUR ; j++)
        {
            switch(carte[i][j])
            {
                case MARIO:
                    nbMario++;
                    break;
            }
        }
    }

    return nbMario;
}