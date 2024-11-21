/*
* Filename:	06_SDL_Shapes.c
* Date:		21/11/2024 
* Name:		EL Joubert
*
* Using SDL to draw shapes that bounce on the screen
*/

#include <stdio.h>
#include <SDL2/SDL.h>

#define FACTOR 40
#define WINDOW_WIDTH 16*FACTOR
#define WINDOW_HEIGHT 9*FACTOR

int main(int argc, char * argv[]) {
	printf("Hello world!\n");

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to init SDL: %s\n", SDL_GetError());
		return 1;
	}

	SDL_Window * pWindow;
	SDL_Renderer * pRenderer;

	/* extern DECLSPEC int SDLCALL SDL_CreateWindowAndRenderer( */
	/* 		int width, int height, Uint32 window_flags, */
	/* 		SDL_Window **window, SDL_Renderer **renderer); */
	if (SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &pWindow, &pRenderer) == -1) {
		printf("Failed to create window and renderer: %s\n", SDL_GetError());
		return 1;
	}

	int closeWindow = 0;
	SDL_Event event;

	int event_key;

	SDL_Rect rect = {0, 0, 40, 40};

	int vel_x = 1;
	int vel_y = 1;

	while (!closeWindow)
	{
		while (SDL_PollEvent(&event)) {
			switch (event.type) 
			{
			case SDL_QUIT:
				closeWindow = 1;
				break;
			case SDL_KEYDOWN:
				{
					event_key = event.key.keysym.sym;
					printf("Key: %c %3d\n", event_key, event_key);
					if (event_key == SDLK_RETURN) {
						closeWindow = 1;
					}
				}
			}
		}
		SDL_SetRenderDrawColor(pRenderer, 20, 20, 40, 255);
		SDL_RenderClear(pRenderer); 
		{	
			SDL_SetRenderDrawColor(pRenderer, 255, 0, 0, 255);
			SDL_RenderFillRect(pRenderer, &rect);
		} 
		SDL_RenderPresent(pRenderer);
		
		rect.x += vel_x;
		rect.y += vel_y;

		if (rect.x >= WINDOW_WIDTH) {
			vel_x = -1;
		} else if (rect.x <= 0) {
			vel_x = 1;	
		}

		if (rect.y >= WINDOW_HEIGHT) {
			vel_y = -1;
		} else if (rect.y <= 0) {
			vel_y = 1;	
		}
		
	}

	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();

	return 0;
}
