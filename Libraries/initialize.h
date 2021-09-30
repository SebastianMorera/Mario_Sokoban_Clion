//
// Created by Sebastian Morera on 2021-09-23.
//

#ifndef MARIO_SOKOBAN_INITIALIZE_H
#define MARIO_SOKOBAN_INITIALIZE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "constantes.h"

void init_sdl();
void init_window_and_renderer(char *title, SDL_Window *window, SDL_Renderer *renderer);
void init_icone_window(SDL_Surface *icon, SDL_Window *window);
void load_menu(SDL_Rect positionMenu, SDL_Surface *menu, SDL_Texture *textureMenu, SDL_Window *window, SDL_Renderer *renderer);
void init_audio();

void SDL_ExitWithDestruction(SDL_Renderer *renderer, SDL_Window *window, const char *message);
void SDL_ExitWithError(const char *message);

#endif //MARIO_SOKOBAN_INITIALIZE_H
