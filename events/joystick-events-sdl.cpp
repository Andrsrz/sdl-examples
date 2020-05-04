/* Example of simple joystick input with SDL. */

#include <iostream>
#include <SDL/SDL.h>

int getNumJoysticks();
void printJoystickInfo(int numJoysticks, SDL_Joystick *joystick);

int main(){
	SDL_Surface *screen;
	SDL_Surface *background;
	SDL_Surface *butterfly;
	SDL_Rect src, dest;
	SDL_Event event;
	SDL_Joystick *joystick;
	int quitFlag;

	/* Initialize SDL's video and Joystick subsystems. */
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) != 0){
		std::cout << "Error : " << SDL_GetError() << std::endl;
		return 1;
	}

	/* Make sure that SDL_Quit gets called on exit. */
	atexit(SDL_Quit);

	/* Attemp to create a 500x500 hicolor (16-bit) window. */
	if(SDL_SetVideoMode(500, 500, 16, 0) == NULL){
		std::cout << "Error : " << SDL_GetError() << std::endl;
		return 1;
	}

	printJoystickInfo(getNumJoysticks(), joystick);
	/* Use first joystick */
	joystick = SDL_JoystickOpen(0);
	if(joystick == NULL){
		std::cout << "Unable to open joystick : " << SDL_GetError() << std::endl;
	}

	/* Game loop until user Quits */
	quitFlag = 0;
	while(SDL_WaitEvent(&event) != 0 && quitFlag == 0){
		switch(event.type){
			case SDL_KEYDOWN:
				if(event.key.keysym.sym == SDLK_q){
					std::cout << "Q pressed. Exiting." << std::endl;
					quitFlag = 1;
				}
				break;
			/* This event is generated when an axis on an open
			 * joystick is moved. Most joysticks have two axes,
			 * X and Y (which will be reported as axes 0 and 1). */
			case SDL_JOYAXISMOTION:
				std::cout << "Joystick " << event.jaxis.which
							<< ", axis " << event.jaxis.axis
							<< ", movement to " << event.jaxis.value
							<< std::endl;
				break;
			/* These events are generated when the
			 * state of a joystick button changes. */
			case SDL_JOYBUTTONUP:
				break;
			case SDL_JOYBUTTONDOWN:
				std::cout << "Joystick " << event.jbutton.which
							<< " button " << event.jbutton.button << " : "
							<< event.jbutton.state << std::endl;
				break;
		}
	}

	/* Close joystick */
	SDL_JoystickClose(joystick);

	return 0;
}

int getNumJoysticks(){
	/* Find out how many joysticks are available */
	return SDL_NumJoysticks();
}

void printJoystickInfo(int numJoysticks, SDL_Joystick *joystick){
	for(int i = 0; i < numJoysticks; i++){
		joystick = SDL_JoystickOpen(i);

		if(joystick == NULL){
			std::cout << "Unable to open joystick " << i << std::endl;
		}else{
			std::cout << "Joystick " << i << std::endl;
			std::cout << "\tName: " << SDL_JoystickName(i)
						<< std::endl;
			std::cout << "\tAxes: " << SDL_JoystickNumAxes(joystick)
						<< std::endl;
			std::cout << "\tTrackballs: " << SDL_JoystickNumBalls(joystick)
						<< std::endl;
			std::cout << "\tButtons: " << SDL_JoystickNumButtons(joystick)
						<< std::endl;
			SDL_JoystickClose(joystick);
		}
	}
}
