/*
 * Example of alpha blending with SDL.
 * g++ alpha-sdl.cpp -o main `sdl-config --libs --cflags` -lSDL_image
 */

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>

int main(){
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *butterfly_no_alpha;
	SDL_Surface *butterfly_with_alpha;
	SDL_Rect src, dest;

	// Initialize SDL's video system and check for errors.
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Make sure SLD_Quit gets called when the program exits!
	atexit(SDL_Quit);

	// Attempt to set a 640x480 hicolor (16-bit) video mode.
	screen = SDL_SetVideoMode(640, 480, 16, 0);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Load the bitmap file. Now using IMG_Load
	background = IMG_Load("../media/background.png");
	butterfly_no_alpha = IMG_Load("../media/butterfly_no_alpha.png");
	butterfly_with_alpha = IMG_Load("../media/butterfly_with_alpha.png");
	if((background == NULL) || (butterfly_no_alpha == NULL) || (butterfly_with_alpha) == NULL){
		std::cout << "Unable to load bitmap" << std::endl;
		return 1;
	}

	/* Background */
	src.x = 0;
	src.y = 0;
	src.w = background->w;
	src.h = background->h;
	dest.x = 0;
	dest.x = 0;
	dest.w = background->w;
	dest.h = background->h;
	SDL_BlitSurface(background, &src, screen, &dest);

	/*
	 * Butterfly with no Alpha channel
	 * Set a 50% transparency factor for the entire surface
	 */
	SDL_SetAlpha(butterfly_no_alpha, SDL_SRCALPHA, 0); // The image will not be transparent
	src.w = butterfly_no_alpha->w;
	src.h = butterfly_no_alpha->h;
	dest.w = src.w;
	dest.h = src.h;
	dest.x = 40;
	dest.y = 50;
	SDL_BlitSurface(butterfly_no_alpha, &src, screen, &dest);

	/*
	 * Butterfly with Alpha channel
	 * We must specifically enable alpha blending.
	 */
	SDL_SetAlpha(butterfly_with_alpha, SDL_SRCALPHA, 128);
	src.w = butterfly_with_alpha->w;
	src.h = butterfly_with_alpha->h;
	dest.w = src.w;
	dest.h = src.h;
	dest.x = 180;
	dest.y = 50;
	SDL_BlitSurface(butterfly_with_alpha, &src, screen, &dest);

	// Ask SDL to update the screen
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	// Pause for a few seconds as the viewer gasps in awe
	SDL_Delay(10000);
	// Free the memory that was allocated to the bitmap
	SDL_FreeSurface(background);
	SDL_FreeSurface(butterfly_no_alpha);
	SDL_FreeSurface(butterfly_with_alpha);

	return 0;
}
