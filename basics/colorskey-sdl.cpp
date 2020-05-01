/*
 * Example of blitting with colorskey in SDL
 */

#include <SDL/SDL.h>
#include <iostream>

int main(){
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *player;
	SDL_Rect src, dest, src2, dest2, src3, dest3;
	Uint32 colorkey;

	// Initialize SDL's video system and check for erros.
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Make sure SDL_Quit gets called when the program exits!
	atexit(SDL_Quit);

	// Attempt to set a 640x480 hicolor (16-bit) video mode.
	screen = SDL_SetVideoMode(500, 500, 16, 0);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Load the bitmap file.
	background = SDL_LoadBMP("../media/background.bmp");
	player = SDL_LoadBMP("../media/pink-guy.bmp");
	if((background == NULL) || (player == NULL)){
		std::cout << "Unable to load bitmap." << std::endl;
		return 1;
	}

	/* Background */
	src.x = 0;
	src.y = 0;
	src.w = background->w;
	src.h = background->h;
	dest.x = 0;
	dest.y = 0;
	dest.w = background->w;
	dest.h = background->h;
	/* Player */
	src2.x = 0;
	src2.y = 0;
	src2.w = player->w;
	src2.h = player->h;
	dest2.x = screen->w - player->w + 60;
	dest2.y = 90;
	dest2.w = player->w;
	dest2.h = player->h;

	// Draw
	SDL_BlitSurface(background, &src, screen, &dest);
	SDL_BlitSurface(player, &src2, screen, &dest2);

	/*
	 * The player is stored in a white background.
	 * We use SDL_MapRGB function to obtain the correct pixel
	 * value for pure white.
	 */
	colorkey = SDL_MapRGB(player->format, 255, 255, 255);

	/*
	 * We'll now enable this surface's colorkey and draw it again.
	 * To turn off the colorkey again, we would replace SDL_SRCCOLORKEY
	 * flag with zero.
	 */
	SDL_SetColorKey(player, SDL_SRCCOLORKEY, colorkey);
	src3.x = 0;
	src3.y = 0;
	src3.w = player->w;
	src3.h = player->h;
	dest3.x = 30;
	dest3.y = 90;
	dest3.w = player->w;
	dest3.h = player->h;
	// Draw
	SDL_BlitSurface(player, &src3, screen, &dest3);

	// Ask SDL to update the screen
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	// Pause for a few seconds as the viewer gasps in awe
	SDL_Delay(10000);

	// Free the memory that was allocated to the bitmap
	SDL_FreeSurface(background);
	SDL_FreeSurface(player);

	return 0;
}
