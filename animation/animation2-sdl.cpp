/* Animation with SDL - First Attempt! */

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include "butterfly.hpp"

const int TWO = 2;
const int NUM_BUTTERFLIES = 5;
const int MAX_SPEED = 6;

void initButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen);
void drawButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen, SDL_Surface* butterfly);
void moveButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen);

int main(){
	SDL_Surface *temp;
	SDL_Surface *background;
	SDL_Surface *screen;
	SDL_Surface *butterfly;
	SDL_Rect src, dest;
	int frames;

	/* Initialize SDL's video system and check for erros. */
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Make sure SDL_Quit gets called then the program exits! */
	atexit(SDL_Quit);

	/* Attempt to set a 500x500 hicolor (16-bit) video mode.
	 * With a double buffer. */
	screen = SDL_SetVideoMode(500, 500, 16, SDL_DOUBLEBUF);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Load the background image and convert it to the display's
	 * pixel format. This convertion will drastically improve the
	 * performance os SDL_BlitSurface, as it will not have to
	 * convert the surface on the fly. */
	temp = SDL_LoadBMP("../media/background.bmp");
	background = SDL_DisplayFormat(temp);
	if(background == NULL){
		std::cout << "Unable to load bitmap!." << std::endl;
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

	/* Is needed that the objects are created explicitly before
	 * stored them in the a vector. If we don't do this, our object
	 * are not created by default, so we get a Segmentation fault. */
	std::vector<Butterfly *> butterflies {};
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		Butterfly *butt = new Butterfly();
		butterflies.push_back(butt);
	}
	/* Initialize the butterfly position data. */
	initButterflies(butterflies, screen);

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
		drawButterflies(butterflies, screen, butterfly);
		/* Ask SDL to swap the back buffer to the screen. */
		SDL_Flip(screen);
		/* Move the butterflies for the next frame. */
		moveButterflies(butterflies, screen);
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
void initButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		butterflies[i]->setX( rand() % screen->w );
		butterflies[i]->setY( rand() % screen->h );
		butterflies[i]->setDx( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
		butterflies[i]->setDy( (rand() % (::MAX_SPEED * ::TWO)) - ::MAX_SPEED );
	}
}

/* This routine draws each butterfly to the screen surface. */
void drawButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen, SDL_Surface* butterfly){
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
		dest.x = butterflies[i]->getX() - butterfly->w / TWO;
		dest.y = butterflies[i]->getY() - butterfly->h / TWO;
		dest.w = butterfly->w;
		dest.h = butterfly->h;
		SDL_BlitSurface(butterfly, &src, screen, &dest);
	}
}

/* This routine moves each butterfly by its motion vector. */
void moveButterflies(std::vector<Butterfly *> butterflies, SDL_Surface* screen){
	for(int i = 0; i < ::NUM_BUTTERFLIES; i++){
		/* Move the butterfly by its motion vector. */
		butterflies[i]->setX( butterflies[i]->getX() + butterflies[i]->getDx() );
		butterflies[i]->setY( butterflies[i]->getY() + butterflies[i]->getDy() );
		/* Turn the butterfliesaround if it hits the edge of the screen. */
		if (butterflies[i]->getX() < 0 || butterflies[i]->getX() > screen->w - 1)
			butterflies[i]->setDx( -butterflies[i]->getDx() );
		if (butterflies[i]->getY() < 0 || butterflies[i]->getY() > screen->h - 1)
			butterflies[i]->setDy( -butterflies[i]->getDy() );
	}
}
