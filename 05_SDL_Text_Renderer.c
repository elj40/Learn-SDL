/*
* Filename:	05_SDL_Text_Renderer.c
* Date:		21/11/2024 
* Name:		EL Joubert
*
* Same as 04_SDL_Text.c, but this time using the renderer so we can use the gpu
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

	/**
	 * Create a 2D rendering context for a window.
	 *
	 * \param window the window where rendering is displayed
	 * \param index the index of the rendering driver to initialize, or -1 to
	 *              initialize the first one supporting the requested flags
	 * \param flags 0, or one or more SDL_RendererFlags OR'd together
	 * \returns a valid rendering context or NULL if there was an error; call
	 *          SDL_GetError() for more information.
	 */
	/* extern DECLSPEC SDL_Renderer * SDLCALL SDL_CreateRenderer(SDL_Window * window, */
	/* 		int index, Uint32 flags); */
	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) 
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
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
	
	/* Sets colour that renderer is going to draw with (this includes the color it clears with) */
	/* extern DECLSPEC int SDLCALL SDL_SetRenderDrawColor(SDL_Renderer * renderer, */
                                           /* Uint8 r, Uint8 g, Uint8 b, */
                                           /* Uint8 a); */
	SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);

	/* extern DECLSPEC int SDLCALL SDL_RenderFillRect(SDL_Renderer * renderer, */
	/* 		const SDL_Rect * rect); */
	SDL_RenderFillRect(renderer, NULL);


	SDL_Color font_color = { 255, 255, 255, 255 };
	SDL_Surface * font_surface = TTF_RenderText_Solid(font, "Press enter to quit", font_color);

	/* extern DECLSPEC SDL_Texture * SDLCALL SDL_CreateTextureFromSurface(SDL_Renderer * renderer, SDL_Surface * surface); */
	SDL_Texture * font_texture = SDL_CreateTextureFromSurface(renderer, font_surface);

	SDL_FreeSurface(font_surface);

      	SDL_Rect font_dest_rect = { 0, 100, font_surface->w, font_surface->h }; 
	/* extern DECLSPEC int SDLCALL SDL_RenderCopy(SDL_Renderer * renderer, */
	/* 		SDL_Texture * texture, */
	/* 		const SDL_Rect * srcrect, */
	/* 		const SDL_Rect * dstrect); */
	SDL_RenderCopy(renderer, font_texture, NULL, &font_dest_rect);

	int close_window = 0;
	SDL_Event event;

	while (!close_window) {
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
		/* extern DECLSPEC void SDLCALL SDL_RenderPresent(SDL_Renderer * renderer); */
		SDL_RenderPresent(renderer);
		/* extern DECLSPEC int SDLCALL SDL_RenderClear(SDL_Renderer * renderer); */
		SDL_RenderClear(renderer);
	}

	SDL_DestroyTexture(font_texture);

	/* extern DECLSPEC void SDLCALL SDL_DestroyRenderer(SDL_Renderer * renderer); */
	SDL_DestroyRenderer(renderer);

	SDL_DestroyWindow(window);
	/* extern DECLSPEC void SDLCALL TTF_CloseFont(TTF_Font *font); */
	TTF_CloseFont(font);

	return 0;
}


