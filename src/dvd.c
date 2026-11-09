#include "dvd.h"
#include "window.h"
#include <SDL3/SDL_render.h>

static const SDL_Color dvdColors[] = {
    {164, 212, 184, 255}, // Mint
    {162, 171, 182, 255}, // Silver
    {181, 131, 194, 255}, // Purple
    {214, 160,  68, 255}, // Orange
    { 94, 101, 213, 255}, // Blue
    { 41, 182, 199, 255}, // Cyan
    {145, 222,  89, 255}, // Lime
    { 65, 200, 121, 255}, // Green
    {195,  90, 224, 255}, // Magenta
    {164, 180, 141, 255}, // Olive
    {180, 167, 127, 255}, // Beige
    {102, 156, 229, 255}  // Sky Blue
};

static int dvd_color_count = sizeof(dvdColors) / sizeof(dvdColors[0]);

static void change_logo_color(SDL_Texture *logo)
{
    static int previous = -1;

	int index = SDL_rand(dvd_color_count);

	while (index == previous){
		index = SDL_rand(dvd_color_count);
	}

    previous = index;

    SDL_Color color = dvdColors[index];

    SDL_SetTextureColorMod(logo, color.r, color.g, color.b);
}

void draw_dvd(DVD dvd)
{

	SDL_FRect rect = {dvd.posX, dvd.posY, dvd.width, dvd.height};

	SDL_RenderTexture(renderer_get(), dvd.logo, NULL, &rect);
}

void update_dvd(DVD *dvd, float dt)
{
	dvd->posX += dvd->speed * dvd->directionX * dt;
	dvd->posY += dvd->speed * dvd->directionY * dt;

	bool collide = false;

	if (dvd->posX <= 0) {
		dvd->posX = 0;
		dvd->directionX = 1;
		collide = true;
	}
	else if (dvd->posX + dvd->width >= window_get_width()) {
		dvd->posX = window_get_width() - dvd->width;
		dvd->directionX = -1;
		collide = true;
	}

	if (dvd->posY <= 0) {
		dvd->posY = 0;
		dvd->directionY = 1;
		collide = true;
	}
	else if (dvd->posY + dvd->height >= window_get_height()) {
		dvd->posY = window_get_height() - dvd->height;
		dvd->directionY = -1;
		collide = true;
	}

	if (collide) change_logo_color(dvd->logo);
}
