/*
* Filename:	03_SDL_Event.c
* Date:		19/11/2024 
* Name:		EL Joubert
*
* Close a window using enter, otherwise output the key that was pressed
*/

#include <stdio.h>
#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

// main has to take arguments
int main(int argc, char * argv[]) {
	SDL_Init(SDL_INIT_VIDEO);	
	// Current screen resolution: 1920*1080
	SDL_Window * window =  SDL_CreateWindow("SDL Window", 
			SDL_WINDOWPOS_UNDEFINED, 
			SDL_WINDOWPOS_UNDEFINED, 
			WINDOW_WIDTH, 
			WINDOW_HEIGHT, 
			0);

	if (window == NULL) {
		printf("Failed to create window: %s\n", SDL_GetError());
		return 1;
	}


	/* Get the SDL surface associated with the window.  */
	SDL_Surface *  surface = SDL_GetWindowSurface(window);
	if (surface == NULL) 
	{
		printf("Failed to create surface: %s\n", SDL_GetError());
		return 1;
	}

	
	/* Map an RGB triple to an opaque pixel value for a given pixel format.  */
	// Have to update the surface format for it to work for some reason
	Uint32 color = SDL_MapRGB(surface->format, 100, 255, 60);


	/** Perform a fast fill of a rectangle with a specific color.  */
	const SDL_Rect surface_rect = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_FillRect(surface, &surface_rect ,color);

	/* Copy the window surface to the screen.  */

	int lifetime = 10000;
	int close_window = 0;
	SDL_Event event;

	while (lifetime > 0 && !close_window) {
		while (SDL_PollEvent(&event)) {
			int event_scancode = event.key.keysym.scancode;
			int event_keycode = event.key.keysym.sym; // Maps to ascii numbers
			switch (event.type) {
				case SDL_QUIT:
					close_window = 1; 
					break;
				case SDL_KEYDOWN:
					if (event_scancode == SDL_SCANCODE_RETURN) {
						close_window = 1;
					} else {
						printf("Scancode: %d\n", event_scancode);
						printf("Keycode: %c\n", event_keycode);
					}
			}
		}
		SDL_UpdateWindowSurface(window);
	}

	SDL_DestroyWindow(window);

	return 0;
}

