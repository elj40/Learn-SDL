/*
* Filename:	07_SDL_Button.c
* Date:		21/11/2024 
* Name:		EL Joubert
*
* Make a slow moving button that closes the application
*/

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#define FACTOR 40
int windowWidth = 16*FACTOR;
int windowHeight = 9*FACTOR;

#define FONT_PATH "C:\\Windows\\Fonts\\Candaral.ttf"

#define BUTTON_SPEED 0.1

int closeWindow = 0;

int closeButton(SDL_Renderer * pRend, TTF_Font * pFont, SDL_FRect button) {
	const SDL_Rect buttonRounded = {
		(int) button.x,
		(int) button.y,
		(int) button.w,
		(int) button.h,
	};

	SDL_Point mousePos;
	int mouseButton = SDL_GetMouseState(&mousePos.x, &mousePos.y);
	int hover = SDL_PointInRect(&mousePos, &buttonRounded);
	int clicked = mouseButton == SDL_BUTTON_LEFT; 

	if (hover) {
		if (clicked) { // Pressing the button
			SDL_SetRenderDrawColor(pRend, 200, 100, 100, 255);
		} else {				// Hovering
			SDL_SetRenderDrawColor(pRend, 200, 100, 100, 255);
		}
	} else {
		SDL_SetRenderDrawColor(pRend, 100, 50, 50, 255);
	}


	const SDL_Color white = { 255, 255, 255, 255 };
	SDL_Surface * pFontSurface = TTF_RenderText_Solid(pFont, "EXIT", white);
	SDL_Texture * pFontTexture = SDL_CreateTextureFromSurface(pRend, pFontSurface);

	SDL_RenderFillRect(pRend, &buttonRounded);
	SDL_RenderCopy(pRend, pFontTexture, NULL, &buttonRounded);

	SDL_FreeSurface(pFontSurface);
	SDL_DestroyTexture(pFontTexture);

	return hover && clicked;
}

int main(int argc, char * argv[]) {
	printf("07_SDL_Button.c running...\n\n");

	SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO);
	TTF_Init();

	TTF_Font * pFontCanderall = TTF_OpenFont(FONT_PATH, 36);

	SDL_Window * pWindow = SDL_CreateWindow("Moving button", 50, 50, windowWidth, windowHeight, SDL_WINDOW_RESIZABLE);
	SDL_Renderer * pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED);

	SDL_FRect button = {0.0, 0.0, 80.0, 40.0};
	float velX = BUTTON_SPEED;
	float velY = BUTTON_SPEED;

	SDL_Event event;
	while (!closeWindow)
	{
		while (SDL_PollEvent(&event)) 
		{
			switch(event.type) {
			case SDL_QUIT:
				closeWindow = 1;
				break;
			case SDL_MOUSEBUTTONDOWN:
				{
				int mouseX, mouseY;
				mouseX = event.button.x;
				mouseY = event.button.y;
				printf("Mouse-> x: %d, y: %d\n", mouseX, mouseY);
				} break;
			case SDL_KEYDOWN:
				{
				int key = event.key.keysym.sym;
				if (key == SDLK_RETURN) closeWindow = 1;
				} break;
			case SDL_WINDOWEVENT:
				SDL_GetWindowSize(pWindow, &windowWidth, &windowHeight);
				break;
			default:
				break;
			}
		}
		
		button.x += velX;
		button.y += velY;

		if (button.x + button.w >= windowWidth || button.x <= 0) velX *= -1;
		if (button.y + button.h >= windowHeight || button.y <= 0) velY *= -1;

		SDL_SetRenderDrawColor(pRenderer, 10, 10, 10, 255);
		SDL_RenderClear(pRenderer);
		{
			int clicked = closeButton(pRenderer, pFontCanderall, button);
			if (clicked == SDL_BUTTON_LEFT) {
				printf("Button clicked\n");
				closeWindow = 1;
			}
		}
		SDL_RenderPresent(pRenderer);
	}

	SDL_DestroyWindow(pWindow);
	SDL_DestroyRenderer(pRenderer);
	SDL_Quit();

	return 0;
}
