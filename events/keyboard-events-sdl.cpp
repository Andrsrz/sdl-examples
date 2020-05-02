/* Example of simple keyboard input with SDL */

#include <iostream>
#include <SDL/SDL.h>

int main(){
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *butterfly;
	SDL_Rect src, dest;
	Uint32 colorkey;
	SDL_Event event;

	/* Initialize SDL's video system and check for errors */
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Make sure SDL_Quit gets called when the program exits! */
	atexit(SDL_Quit);

	/* Attempt to set a 500x500 hicolor (16-bit) video mode. */
	screen = SDL_SetVideoMode(500, 500, 16, 0);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Load the bitmap file */
	background = SDL_LoadBMP("../media/background.bmp");
	butterfly = SDL_LoadBMP("../media/butterfly.bmp");
	if((background == NULL) || (butterfly == NULL)){
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
	SDL_BlitSurface(background, &src, screen, &dest);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	std::cout << "Press 'Q' to quit" << std::endl;

	/* Start the event loop. Keep reading events until there
	 * is an error, or the user presses a key. */
	while(SDL_WaitEvent(&event) != 0){
		SDL_keysym keysym;

		/* SDL_WaitEvent has filled in our event structure
		 * with the next event. We check its type field to
		 * find out what happened. */
		switch(event.type){
			case SDL_KEYDOWN:
				std::cout << "Key pressed!" << std::endl;
				keysym = event.key.keysym;
				std::cout << "SDL key sym is: " << keysym.sym << std::endl;
				std::cout << SDL_GetKeyName(keysym.sym) << std::endl;

				/* Report the left shift modifier */
				if(event.key.keysym.mod &KMOD_LSHIFT){
					std::cout << "Left Shift is down." << std::endl;
				}else{
					std::cout << "Left Shift is up." << std::endl;
				}

				/* Did the user press Q? */
				if(keysym.sym == SDLK_q){
					std::cout << "’Q’ pressed, exiting." << std::endl;
					exit(0);
				}
				break;
			case SDL_KEYUP:
				std::cout << "Key released" << std::endl;
				std::cout << "SDL keysym is: " << keysym.sym << std::endl;
				std::cout << SDL_GetKeyName(keysym.sym) << std::endl;

				/* Report the left shift modifier */
				if(event.key.keysym.mod &KMOD_LSHIFT){
					std::cout << "Left Shift is down." << std::endl;
				}else{
					std::cout << "Left Shift is up." << std::endl;
				}

				break;
			case SDL_QUIT:
				exit(0);
		}
	}

	return 0;
}
