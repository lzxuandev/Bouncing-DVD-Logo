#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "window.h"
#include "dvd.h"

#define WINDOW_TITLE "Bounching DVD Logo"
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600
#define DVD_SPEED 150.0f

float get_frame_time();

int main()
{
	bool running = true;

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_Init failed: %s", SDL_GetError());
		return 1;
	}

	if (!window_init(WINDOW_TITLE, WINDOW_WIDTH, WINDOW_HEIGHT)) {
		window_shutdown();
		SDL_Quit();
		return 1;
	}

	SDL_Texture *logo = IMG_LoadTexture(renderer_get(), "assets/dvd-logo.png");

	if (!logo) {
		SDL_Log("Failed to load texture: %s", SDL_GetError());
		window_shutdown();
		SDL_Quit();
		return 1;
	}

	DVD dvd = {
		.speed = DVD_SPEED,
		.directionX = 1,
		.directionY = 1,
		.logo = logo,
		.color = {255, 255, 255, 255},
	};

	SDL_GetTextureSize(logo, &dvd.width, &dvd.height);

	while (running) {

		SDL_Event event;

		while (SDL_PollEvent(&event)) {

			if (event.type == SDL_EVENT_QUIT || (event.type == SDL_EVENT_KEY_DOWN && event.key.scancode == SDL_SCANCODE_ESCAPE)) {
				running = false;
			}
		}

		float dt = get_frame_time();
		update_dvd(&dvd, dt);

		SDL_SetRenderDrawColor(renderer_get(), 5, 5, 5, 255);
		SDL_RenderClear(renderer_get());

		draw_dvd(dvd);

		SDL_RenderPresent(renderer_get());
	}

	SDL_DestroyTexture(logo);

	window_shutdown();

	SDL_Quit();
	return 0;
}

float get_frame_time(void)
{
	static Uint64 lastTime = 0;
    Uint64 currentTime = SDL_GetTicksNS();

    if (lastTime == 0) {
        lastTime = currentTime;
        return 0.0f;
    }

    float dt = (float)(currentTime - lastTime) / 1000000000.0f;

    lastTime = currentTime;

    return dt;
}
