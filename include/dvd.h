#pragma once

#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>

typedef struct DVD {
	float posX;
	float posY;
	float speed;
	float directionX;
	float directionY;
	float width;
	float height;

	SDL_Texture *logo;
	SDL_Color color;
} DVD;

void draw_dvd(DVD dvd);
void update_dvd(DVD *dvd , float dt);
