//
// Created by Sebastian Morera on 2021-09-23.
//

#include "initialize.h"

SDL_Color white = {255, 255, 255};

TTF_Font *font = NULL;
SDL_Rect headerTextRect;
SDL_Texture *headerText = NULL;
SDL_Texture *image = NULL;

// Our sample rectangle that we can drag around the viewport
SDL_Rect sampleRect = {.x = 10, .y = 10, .w = 100, .h = 100};
SDL_bool inSampleRect = SDL_FALSE;

// Our sample 'music'
Mix_Music *music = NULL;

/**
 * Initialise SDL2 and output some useful display info
 */
void init_sdl()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("[Error] SDL Init : %s \n", SDL_GetError());
    } else {
        printf("SDL INITIALISED\n");
        SDL_DisplayMode dm;
        SDL_GetCurrentDisplayMode(0, &dm);

        printf("Display mode is %dx%dpx @ %dhz\n", dm.w, dm.h, dm.refresh_rate);
    }
}

/**
 * Initialise an SDL Window and Renderer
 *
 * This uses SDL_CreateWindowAndRenderer. They can alternatively be created separately. See SDL2 Docs
 */
void init_window_and_renderer(char *title, SDL_Window *window, SDL_Renderer *renderer)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    SDL_SetWindowTitle(window, title);
    printf("Created Window and Renderer %dx%d\n", WINDOW_WIDTH, WINDOW_HEIGHT);
}

/**
 * Load the window icon
 */
void init_icone_window(SDL_Surface *icon, SDL_Window *window)
{
    icon = IMG_Load("caisse.jpg");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);
}

/**
 * Load the game menu
 */
void load_menu(SDL_Rect positionMenu, SDL_Surface *menu, SDL_Texture *textureMenu, SDL_Window *window, SDL_Renderer *renderer)
{
    menu = IMG_Load("/Users/sebastianmorera/Documents/Programmation/C Projects/Clion/Mario_Sokoban/Images et resources/menu.jpg");
    if (menu == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger image");

    textureMenu = SDL_CreateTextureFromSurface(renderer, menu);
    SDL_FreeSurface(menu);

    if (textureMenu == NULL)
        SDL_ExitWithDestruction(renderer, window, "Impossible de creer la texture");

    if(SDL_QueryTexture(textureMenu, NULL, NULL, &positionMenu.w, &positionMenu.h) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible de charger la texture");

    if(SDL_RenderCopy(renderer, textureMenu, NULL, &positionMenu) != 0)
        SDL_ExitWithDestruction(renderer, window, "Impossible d afficher la texture");

    SDL_RenderPresent(renderer); // Afficher l'image de fond
}

void init_audio()
{
    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) != 0) {
        printf("[Error] Error Initialising Audio : %s\n", SDL_GetError());
    } else {
        printf("Audio Initialised\n");
    }
}

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message)
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_ExitWithError(message);
}

void SDL_ExitWithError(const char *message)
{
    SDL_Log("Erreur: %s > %s \n", message ,SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}