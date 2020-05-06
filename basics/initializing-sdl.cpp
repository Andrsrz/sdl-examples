/* Example of initializing SDL */

#include <SDL2/SDL.h>
#include <iostream>

/* Avoid magic numbers */
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const char* WINDOW_TITLE = "Initializing SDL";

int main(){
	SDL_Window *window;
	SDL_Surface *screenSurface;

	/* Initialize SDL's video system and check for erros */
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Make sure SDL_Quit gets called when the program exits! */
	atexit(SDL_Quit);

	window = SDL_CreateWindow(::WINDOW_TITLE,
								SDL_WINDOWPOS_CENTERED,
								SDL_WINDOWPOS_CENTERED,
								::SCREEN_WIDTH,
								::SCREEN_HEIGHT,
								0);

	/* Window created and check for erros */
	if(window == NULL){
		std::cout << "Unable to create window: " << SDL_GetError() << std::endl;
		return 1;
	}

	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

	/* If we got this far, everything worked! */
	std::cout << "Success!" << std::endl;

	SDL_DestroyWindow(window);

	return 0;
}
