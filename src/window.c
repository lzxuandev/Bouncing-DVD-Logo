#include "window.h"
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_video.h>

static SDL_Window *window     = NULL;
static SDL_Renderer *renderer = NULL;

// SDL_WINDOW_FULLSCREEN:         Fullscreen window at desktop resolution
// SDL_WINDOW_OPENGL:             Window usable with an OpenGL context
// SDL_WINDOW_HIDDEN:             Window is not visible
// SDL_WINDOW_BORDERLESS:         Window without borders or title bar
// SDL_WINDOW_RESIZABLE:          Window can be resized
// SDL_WINDOW_MINIMIZED:          Window starts minimized
// SDL_WINDOW_MAXIMIZED:          Window starts maximized
// SDL_WINDOW_MOUSE_GRABBED:      Window grabs mouse input
// SDL_WINDOW_INPUT_FOCUS:        Window has keyboard input focus
// SDL_WINDOW_MOUSE_FOCUS:        Window has mouse focus
// SDL_WINDOW_EXTERNAL:           Window was created outside SDL
// SDL_WINDOW_MODAL:              Window behaves as a modal window
// SDL_WINDOW_HIGH_PIXEL_DENSITY: Window supports high pixel density rendering
// SDL_WINDOW_MOUSE_CAPTURE:      Window captures mouse input
// SDL_WINDOW_ALWAYS_ON_TOP:      Window stays above other windows
// SDL_WINDOW_UTILITY:            Window is treated as a utility window
// SDL_WINDOW_TOOLTIP:            Window is treated as a tooltip
// SDL_WINDOW_POPUP_MENU:         Window is treated as a popup menu
// SDL_WINDOW_KEYBOARD_GRABBED:   Window grabs keyboard input
// SDL_WINDOW_VULKAN:             Window usable with a Vulkan instance
// SDL_WINDOW_METAL:              Window usable with a Metal instance
// SDL_WINDOW_TRANSPARENT:       Window supports a transparent buffer
// SDL_WINDOW_NOT_FOCUSABLE:     Window cannot receive input focus

bool window_init(const char *title, int width, int height)
{
	window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);

    if (!window) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create window: %s\n", SDL_GetError());
		return false;
    }

    renderer = SDL_CreateRenderer(window, NULL);

	if (!renderer) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create renderer: %s\n", SDL_GetError());
		return false;
	}

	// vsync on: synchronized with the monitor's refresh rate.
	if (!SDL_SetRenderVSync(renderer, 1)) {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "VSync unavailable: %s", SDL_GetError());
	}

	return true;
}

void window_shutdown()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    renderer = NULL;
    window   = NULL;
}

SDL_Window *window_get()
{
    return window;
}

int window_get_width()
{
	int width = 0;

	SDL_GetWindowSize(window, &width, NULL);

	return width;
}

int window_get_height()
{
	int height = 0;

	SDL_GetWindowSize(window, NULL, &height);

	return height;
}

SDL_Renderer *renderer_get()
{
	return renderer;
}
