/*
* Filename:	04_SDL_Text.c
* Date:		19/11/2024 
* Name:		EL Joubert
*
* Display text using SDL_ttf and surfaces
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define FONT_FILE "C:\\Windows\\Fonts\\complex_IV25.ttf"

// main has to take arguments
int main(int argc, char * argv[]) {

	SDL_Init(SDL_INIT_VIDEO);	

	/* extern DECLSPEC int SDLCALL TTF_Init(void); */
	TTF_Init();

	// Current screen resolution: 1920*1080
	SDL_Window * window =  SDL_CreateWindow("SDL Window", 
			SDL_WINDOWPOS_CENTERED, 
			SDL_WINDOWPOS_CENTERED, 
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

	/* extern DECLSPEC TTF_Font * SDLCALL TTF_OpenFont(const char *file, int ptsize); */
	TTF_Font * font = TTF_OpenFont(FONT_FILE, 48);
	
	/* Map an RGB triple to an opaque pixel value for a given pixel format.  */
	// Have to update the surface format for it to work for some reason
	Uint32 color = SDL_MapRGB(surface->format, 50, 50, 100);


	/** Perform a fast fill of a rectangle with a specific color.  */
	const SDL_Rect surface_rect = {0,0, WINDOW_WIDTH, WINDOW_HEIGHT};
	SDL_FillRect(surface, &surface_rect ,color);

	/* Copy the window surface to the screen.  */

	int lifetime = 10000;
	int close_window = 0;
	SDL_Event event;

	SDL_Color font_color = { 255, 255, 255, 255 };

	/* extern DECLSPEC SDL_Surface * SDLCALL TTF_RenderText_Solid(TTF_Font *font, */
	/*                 const char *text, SDL_Color fg); */
	SDL_Surface * font_surface = TTF_RenderText_Solid(font, "Press enter to quit", font_color);

	/* SDL_BlitSurface is a macro of SDL_UpperBlit */
	/* extern DECLSPEC int SDLCALL SDL_UpperBlit */
	/* 	(SDL_Surface * src, const SDL_Rect * srcrect, */
	/* 	 SDL_Surface * dst, SDL_Rect * dstrect); */
      	SDL_Rect font_dest_rect = { 0, 100, font_surface->w, font_surface->h }; 
	SDL_BlitSurface(font_surface, NULL, surface, &font_dest_rect);

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
	/* extern DECLSPEC void SDLCALL TTF_CloseFont(TTF_Font *font); */
	TTF_CloseFont(font);

	return 0;
}


