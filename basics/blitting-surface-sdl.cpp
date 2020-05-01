/*
 * Example of simple blitting with SDL
 */

#include <SDL/SDL.h>
#include <iostream>

int main(){
	SDL_Surface *screen;
	SDL_Surface *image; // Red
	SDL_Surface *image2; // Blue
	SDL_Surface *image3; // Green
	SDL_Rect src, dest, src2, dest2, src3, dest3;

	// Initialize SDL's video system and check for errors.
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Make sure SDL_Quit gets called when the program exits!
	atexit(SDL_Quit);

	/*
	 * Attempt to set a 256x256 hicolor (16-bit) video mode.
	 * Since 256x256 is rarely a valid video mode, SDL will
	 * most likely to emulate this resolution with a different
	 * video mode.
	 */
	screen = SDL_SetVideoMode(256, 256, 16, 0);
	if(screen == NULL){
		std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
		return 1;
	}

	/*
	 * Load the bitmap file. SDL_LoadBM returns a pointer to a
	 * new surface containing the loaded image.
	 */
	image = SDL_LoadBMP("../media/test-image-red.bmp");
	image2 = SDL_LoadBMP("../media/test-image-blue.bmp");
	image3 = SDL_LoadBMP("../media/test-image-green.bmp");
	if((image == NULL) && (image2 == NULL) && (image3 == NULL)){
		std::cout << "Unable to load bitmap." << std::endl;
		return 1;
	}

	/*
	 * The SDL blitting function needs to know how much data
	 * to copy. We provide this with SDL_Rect structures, which
	 * define the source and destination rectangles. The areas
	 * should be the same; SDL doesn not currently handle image
	 * stretching.
	 */
	/* Red image */
	src.x = 0;
	src.y = 0;
	src.w = image->w; // Copy the entire image.
	src.h = image->h / 2;
	dest.x = 0;
	dest.y = 0;
	dest.w = image->w;
	dest.h = image->h;
	/* Blue image */
	src2.x = 0;
	src2.y = 0;
	src2.w = image2->w;
	src2.h = image2->h;
	dest2.x = image2->w / 2;
	dest2.y = image2->h / 2;
	dest2.w = image2->w / 2;
	dest2.h = image2->h / 2;
	/* Green image */
	src3.x = 0;
	src3.y = 0;
	src3.w = image3->w / 2;
	src3.h = image3->h / 2;
	dest3.x = 0;
	dest3.y = image3->h / 2;
	dest3.w = image3->w;
	dest3.h = image3->h;

	/*
	 * Draw the bitmap to the screen. We are using a hicolor video
	 * mode, so we don't have to worry about colormap silliness.
	 * It is not necessary to lock surfaces before blitting; SDL
	 * will handle that.
	 */
	SDL_BlitSurface(image, &src, screen, &dest); // Red
	SDL_BlitSurface(image2, &src2, screen, &dest2); // Blue
	SDL_BlitSurface(image3, &src3, screen, &dest3); // Green

	// Ask SDL to update the entire screen
	SDL_UpdateRect(screen, 0, 0, 0, 0);

	// Pause for a few seconds as the viewer gasps in awe
	SDL_Delay(3000);

	// Free the memory that was allocated to the bitmap
	SDL_FreeSurface(image);
	SDL_FreeSurface(image2);
	SDL_FreeSurface(image3);

	return 0;
}
