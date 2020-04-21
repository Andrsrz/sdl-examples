/* Animation with SDL - First Attempt! */

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include "butterfly.hpp"

const int TWO = 2;
const int NUM_BUTTERFLIES = 5;
const int MAX_SPEED = 6;

std::vector<Butterfly> initButterflies(std::vector<Butterfly> butterflies, SDL_Surface* screen);
std::vector<Butterfly> drawButterflies(std::vector<Butterfly> butterflies,
										SDL_Surface* screen,
										SDL_Surface* butterfly);
std::vector<Butterfly> moveButterflies(std::vector<Butterfly> butterflies, SDL_Surface* screen);
void initButterfly(Butterfly *myButterfly, SDL_Surface* screen);
void drawButterfly(Butterfly *myButterfly, SDL_Surface* screen, SDL_Surface* butterfly);
void moveButterfly(Butterfly *myButterfly, SDL_Surface* screen);

int main(){
	SDL_Surface* screen;
	SDL_Surface* butterfly;
	SDL_Surface* background;
	SDL_Rect src, dest;
	int frames;

	// Initialize SDL's video system and check for erros.
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Make sure SDL_Quit gets called then the program exits!
	atexit(SDL_Quit);

	// Attempt to set a 500x500 hicolor (16-bit) video mode.
	screen = SDL_SetVideoMode(500, 500, 16, 0);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Load the bitmap file.
	background = SDL_LoadBMP("background.bmp");
	butterfly = SDL_LoadBMP("butterfly.bmp");
	if((background == NULL) || (butterfly == NULL)){
		std::cout << "Unable to load bitmap" << std::endl;
		return 1;
	}

	/* Set the butterfly’s colorkey. */
	SDL_SetColorKey(butterfly,
					SDL_SRCCOLORKEY,
					(Uint16) SDL_MapRGB(butterfly->format,
										255, 255, 255));

	// std::vector<Butterfly> butterflies {::NUM_BUTTERFLIES};
	Butterfly butt;
	/* Initialize the butterfly position data. */
	// butterflies = initButterflies(butterflies, screen);
	initButterfly(&butt, screen);

	/* Animate 300 frames (approximately 10 seconds). */
	for(frames = 0; frames < 3000; frames++){
		/* Draw the background image. */
		src.x = 0;
		src.y = 0;
		src.w = background->w;
		src.h = background->h;
		dest = src;
		SDL_BlitSurface(background, &src, screen, &dest);
		/* Put the butterflies on the screen. */
		// butterflies = drawButterflies(butterflies, screen, butterfly);
		drawButterfly(&butt, screen, butterfly);
		/* Ask SDL to update the entire screen. */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		/* Move the butterflies for the next frame. */
		// butterflies = moveButterflies(butterflies, screen);
		moveButterfly(&butt, screen);
	}

	/* Free the memory that was allocated to the bitmap. */
	SDL_FreeSurface(background);
	SDL_FreeSurface(butterfly);

	return 0;
}

/*
 * This routine loop through the array of butterflies and sets each to a random
 * starting position and direction.
 */
std::vector<Butterfly> initButterflies(std::vector<Butterfly> butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		butterflies[i].setX( rand() % screen->w );
		butterflies[i].setY( rand() % screen->h );
		butterflies[i].setDx( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
		butterflies[i].setDy( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
	}
	return butterflies;
}

/* This routine draws each butterfly to the screen surface. */
std::vector<Butterfly> drawButterflies(std::vector<Butterfly> butterflies,
										SDL_Surface* screen, SDL_Surface* butterfly){
	SDL_Rect src, dest;
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		src.x = 0;
		src.y = 0;
		src.w = butterfly->w;
		src.h = butterfly->h;
		/*
		 * The butterfly’s position specifies its center.
		 * We subtract half of its width and height to get
		 * its upper left corner.
		*/
		dest.x = butterflies[i].getX() - butterfly->w / TWO;
		dest.y = butterflies[i].getY() - butterfly->h / TWO;
		dest.w = butterfly->w;
		dest.h = butterfly->h;
		SDL_BlitSurface(butterfly, &src, screen, &dest);
	}
	return butterflies;
}

/* This routine moves each butterfly by its motion vector. */
std::vector<Butterfly> moveButterflies(std::vector<Butterfly> butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		/* Move the butterfly by its motion vector. */
		butterflies[i].setX( butterflies[i].getX() + butterflies[i].getDx() );
		butterflies[i].setY( butterflies[i].getY() + butterflies[i].getDy() );
		/* Turn the butterfliesaround if it hits the edge of the screen. */
		if (butterflies[i].getX() < 0 || butterflies[i].getX() > screen->w - 1)
			butterflies[i].setDx( -butterflies[i].getDx() );
		if (butterflies[i].getY() < 0 || butterflies[i].getY() > screen->h - 1)
			butterflies[i].setDy( -butterflies[i].getDy() );
	}
	return butterflies;
}
/* ============================================================================= */
/* This routine set a random location to our Butterfly pointer */
void initButterfly(Butterfly *myButterfly, SDL_Surface* screen){
	myButterfly->setX( rand() % screen->w );
	myButterfly->setY( rand() % screen->h );
	myButterfly->setDx( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
	myButterfly->setDy( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
}

/* This routine draws our Butterfly pointer to the screen surface. */
void drawButterfly(Butterfly *myButterfly, SDL_Surface* screen, SDL_Surface* butterfly){
	SDL_Rect src, dest;
	src.x = 0;
	src.y = 0;
	src.w = butterfly->w;
	src.h = butterfly->h;
	/*
	 * The butterfly’s position specifies its center.
	 * We subtract half of its width and height to get
	 * its upper left corner.
	*/
	dest.x = myButterfly->getX() - butterfly->w / TWO;
	dest.y = myButterfly->getY() - butterfly->h / TWO;
	dest.w = butterfly->w;
	dest.h = butterfly->h;
	SDL_BlitSurface(butterfly, &src, screen, &dest);
}

/* This routine moves our Butterfly pointer by its motion vector. */
void moveButterfly(Butterfly *myButterfly, SDL_Surface* screen){
	/* Move the butterfly by its motion vector. */
	myButterfly->setX( myButterfly->getX() + myButterfly->getDx() );
	myButterfly->setY( myButterfly->getY() + myButterfly->getDy() );
	/* Turn the butterfliesaround if it hits the edge of the screen. */
	if (myButterfly->getX() < 0 || myButterfly->getX() > screen->w - 1)
		myButterfly->setDx( -myButterfly->getDx() );
	if (myButterfly->getY() < 0 || myButterfly->getY() > screen->h - 1)
		myButterfly->setDy( -myButterfly->getDy() );
}
