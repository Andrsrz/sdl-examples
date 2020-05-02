/* Example of simple keyboard input with SDL */

#include <iostream>
#include <SDL/SDL.h>
#include "../classes/butterfly.hpp"

const int TWO = 2;
const int MAX_SPEED = 6;
enum Directions {Right, Left, Up, Down};

void resetBackground(SDL_Surface* background, SDL_Rect src, SDL_Surface* screen, SDL_Rect dest);
void initButterfly(Butterfly *butterfly, SDL_Surface* screen);
void drawButterfly(Butterfly *butterfly, SDL_Surface* screen, SDL_Surface* butterflySurface);
void moveButterfly(Butterfly *butterfly, Directions direction);
void animateButterfly(Butterfly *butterfly, SDL_Surface* screen, SDL_Surface* butterflySurface, Directions direction);

int main(){
	SDL_Surface *screen;
	SDL_Surface *temp;
	SDL_Surface *background;
	SDL_Surface *butterfly;
	SDL_Rect src, dest;
	SDL_Event event;
	Directions direction;

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

	/* Load the background bitmap file */
	temp = SDL_LoadBMP("../media/background.bmp");
	background = SDL_DisplayFormat(temp);
	if(background == NULL){
		std::cout << "Unable to load bitmap." << std::endl;
		return 1;
	}
	SDL_FreeSurface(temp);

	/* Load the butterfly image */
	temp = SDL_LoadBMP("../media/butterfly.bmp");
	if(temp == NULL){
		std::cout << "Unable to load bitmap!." << std::endl;
		return 1;
	}

	/* Set the butterfly’s colorkey. */
	SDL_SetColorKey(temp,
					SDL_SRCCOLORKEY,
					(Uint16) SDL_MapRGB(temp->format,
										255, 255, 255));

	/* Convert butterfly to the display's format. We do this after
	 * we set the colorkey, since colorkey blits can sometimes be
	 * optimized for a particular display. */
	butterfly = SDL_DisplayFormat(temp);
	if(butterfly == NULL){
		std::cout << "Unable to load bitmap!." << std::endl;
		return 1;
	}
	SDL_FreeSurface(temp);

	/* Background */
	src.x = 0;
	src.y = 0;
	src.w = background->w;
	src.h = background->h;
	dest.x = 0;
	dest.y = 0;
	dest.w = background->w;
	dest.h = background->h;
	/* Draw */
	SDL_BlitSurface(background, &src, screen, &dest);
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	/* Create and Draw Butterfly */
	Butterfly *butt = new Butterfly();
	initButterfly(butt, screen);
	drawButterfly(butt, screen, butterfly);
	SDL_Flip(screen);

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

				/* Four direction movement */
				if(keysym.sym == SDLK_RIGHT){
					direction = Right;
					resetBackground(background, src, screen, dest);
					animateButterfly(butt, screen, butterfly, direction);
				}else if(keysym.sym == SDLK_LEFT){
					direction = Left;
					resetBackground(background, src, screen, dest);
					animateButterfly(butt, screen, butterfly, direction);
				}else if(keysym.sym == SDLK_UP){
					direction = Up;
					resetBackground(background, src, screen, dest);
					animateButterfly(butt, screen, butterfly, direction);
				}else if(keysym.sym == SDLK_DOWN){
					direction = Down;
					resetBackground(background, src, screen, dest);
					animateButterfly(butt, screen, butterfly, direction);
				}

				/* Did the user press Q? */
				if(keysym.sym == SDLK_q){
					delete butt;
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
				delete butt;
				exit(0);
		}
	}

	return 0;
}

void resetBackground(SDL_Surface* background, SDL_Rect src, SDL_Surface* screen, SDL_Rect dest){
	/* Reset background to not left a butterflies trail. */
	src.x = 0;
	src.y = 0;
	src.w = background->w;
	src.h = background->h;
	dest = src;
	SDL_BlitSurface(background, &src, screen, &dest);
}

/* This routine loop through the array of butterflies and sets each to a random
 * starting position and direction. */
void initButterfly(Butterfly *butterfly, SDL_Surface* screen){
	butterfly->setX( rand() % screen->w );
	butterfly->setY( rand() % screen->h );
}

/* This routine draws each butterfly to the screen surface. */
void drawButterfly(Butterfly *butterfly, SDL_Surface* screen, SDL_Surface* butterflySurface){
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = butterflySurface->w;
	src.h = butterflySurface->h;
	/*
	 * The butterfly’s position specifies its center.
	 * We subtract half of its width and height to get
	 * its upper left corner.
	*/
	dest.x = butterfly->getX() - butterflySurface->w / TWO;
	dest.y = butterfly->getY() - butterflySurface->h / TWO;
	dest.w = butterflySurface->w;
	dest.h = butterflySurface->h;
	SDL_BlitSurface(butterflySurface, &src, screen, &dest);
}

/* This routine moves each butterfly by its motion vector. */
void moveButterfly(Butterfly *butterfly, Directions direction){
	if(direction == Right){
		butterfly->setX( butterfly->getX() + ::MAX_SPEED );
	}else if(direction == Left){
		butterfly->setX( butterfly->getX() - ::MAX_SPEED );
	}else if(direction == Up){
		butterfly->setY( butterfly->getY() - ::MAX_SPEED );
	}else if(direction == Down){
		butterfly->setY( butterfly->getY() + ::MAX_SPEED );
	}
}

void animateButterfly(Butterfly *butterfly, SDL_Surface* screen, SDL_Surface* butterflySurface, Directions direction){
	moveButterfly(butterfly, direction);
	drawButterfly(butterfly, screen, butterflySurface);
	SDL_Flip(screen);
}
