#pragma once

#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

bool window_init(const char *title, int width, int height);
void window_shutdown();

SDL_Window *window_get();
int window_get_width();
int window_get_height();

SDL_Renderer *renderer_get();
