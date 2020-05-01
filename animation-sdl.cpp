/* Animation with SDL - First Attempt! */

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include "butterfly.hpp"

const int TWO = 2;
const int NUM_BUTTERFLIES = 5;
const int MAX_SPEED = 6;

void initButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen);
void drawButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen, SDL_Surface* butterfly);
void moveButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen);
void initButterfly(Butterfly *myButterfly, SDL_Surface* screen);
void drawButterfly(Butterfly *myButterfly, SDL_Surface* screen, SDL_Surface* butterfly);
void moveButterfly(Butterfly *myButterfly, SDL_Surface* screen);

int main(){
	SDL_Surface *screen;
	SDL_Surface *butterfly;
	SDL_Surface *background;
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

	std::vector<Butterfly *> butterflies {::NUM_BUTTERFLIES};
	// Butterfly butt;
	/* Initialize the butterfly position data. */
	initButterflies(&butterflies, screen);
	// initButterfly(&butt, screen);

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
		drawButterflies(&butterflies, screen, butterfly);
		// drawButterfly(&butt, screen, butterfly);
		/* Ask SDL to update the entire screen. */
		SDL_UpdateRect(screen, 0, 0, 0, 0);
		/* Move the butterflies for the next frame. */
		moveButterflies(&butterflies, screen);
		// moveButterfly(&butt, screen);
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
void initButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		butterflies->at(i)->setX( rand() % screen->w );
		butterflies->at(i)->setY( rand() % screen->h );
		butterflies->at(i)->setDx( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
		butterflies->at(i)->setDy( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
	}
}

/* This routine draws each butterfly to the screen surface. */
void drawButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen, SDL_Surface* butterfly){
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
		dest.x = butterflies->at(i)->getX() - butterfly->w / TWO;
		dest.y = butterflies->at(i)->getY() - butterfly->h / TWO;
		dest.w = butterfly->w;
		dest.h = butterfly->h;
		SDL_BlitSurface(butterfly, &src, screen, &dest);
	}
}

/* This routine moves each butterfly by its motion vector. */
void moveButterflies(std::vector<Butterfly *> *butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		/* Move the butterfly by its motion vector. */
		butterflies->at(i)->setX( butterflies->at(i)->getX() + butterflies->at(i)->getDx() );
		butterflies->at(i)->setY( butterflies->at(i)->getY() + butterflies->at(i)->getDy() );
		/* Turn the butterflies round if it hits the edge of the screen. */
		if (butterflies->at(i)->getX() < 0 || butterflies->at(i)->getX() > screen->w - 1)
			butterflies->at(i)->setDx( -butterflies->at(i)->getDx() );
		if (butterflies->at(i)->getY() < 0 || butterflies->at(i)->getY() > screen->h - 1)
			butterflies->at(i)->setDy( -butterflies->at(i)->getDy() );
	}
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
