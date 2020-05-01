/* Example of simple mouse input with SDL */

#include <iostream>
#include <SDL/SDL.h>

int main(){
	SDL_Surface *screen;
	SDL_Event event;

	/* Initialize SDL's video system and check for erros */
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

	/* Start the event loop. Keep reading events until there
	 * is an error, or the user presses a mouse button. */
	while(SDL_WaitEvent(&event) != 0){
		/* SDL_WaitEvent has filled in our event structure
		 * with the next event. We check its type field to
		 * find out what happend. */
		switch(event.type){
			/* The next two events types deal with mouse activity. */
			case SDL_MOUSEMOTION:
				std::cout << "Mouse motion" << std::endl;
				/* SDL provides the current position. */
				std::cout << "Mouse X: " << event.motion.x
						  << ". Mouse Y: " << event.motion.y << std::endl;
				/* We can also get relative motion. */
				std::cout << "That is a " << event.motion.xrel
						  << ", " << event.motion.yrel << std::endl;
				break;
			case SDL_MOUSEBUTTONDOWN:
				std::cout << "Mouse button pressed." << std::endl;
				std::cout << "Button " << event.button.button << " at "
						  << event.button.x << ", " << event.button.y << std::endl;
				break;
			/* The SDL_QUIT event indicates that the window "Close"
			 * button has been pressed. We can ignore this if we
			 * need to, but that tends to make user rather impatient. */
			case SDL_QUIT:
				std::cout << "Quit event. Bye bye!" << std::endl;
				exit(0);
		}
	}

	return 0;
}
