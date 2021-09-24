//
// Created by Sebastian Morera on 2021-09-21.
//
//#include <SDL_ttf.h>
//#include <SDL_mixer.h>

#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "constantes.h"
#include "initialize.h"
#include "editeur.h"
#include "jeu.h"

int main()
{
    int continuer = 1;

    /// SDL2 init window and renderer
    char *title = "Mario Sokoban";
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        SDL_ExitWithError("Initialisation de la SDL");

    printf("\nSDL INITIALISED\n");
    SDL_DisplayMode dm;
    SDL_GetCurrentDisplayMode(0, &dm);
    printf("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowTitle(window, title);
    printf("Created Window and Renderer %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);

    /// Load the window icon
    SDL_Surface *icon = NULL;
    init_icone_window(icon, window);

    /// Load the menu in the window
    SDL_Surface *menu = NULL;
    SDL_Texture *textureMenu = NULL;
    SDL_Rect positionMenu = {.x = 0, .y = 0};
    load_menu(positionMenu, menu, textureMenu,window,renderer);

    /// main loop (Events)
    SDL_Event event;

    while(continuer)
    {
        SDL_WaitEvent(&event);
        switch (event.type)
        {
            case SDL_QUIT:
                continuer = 0;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: /* Appui sur la touche Echap, on arrête le programme */
                        continuer = 0;
                        break;

                    case SDLK_KP_1: // Demande à jouer
                        jouer(renderer);

                        SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h);
                        SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu);
                        SDL_RenderPresent(renderer); // Afficher l'image de fond
                        break;

                    case SDLK_KP_2: // Demande l'éditeur de niveaux
                        editeur(renderer);

                        SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h);
                        SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu);
                        SDL_RenderPresent(renderer); // Afficher l'image de fond
                        break;

                    default:
                        break;
                }
                break;

            default:
                break;
        }
    }

    /// Destruction of all existing elements
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return EXIT_SUCCESS;
}