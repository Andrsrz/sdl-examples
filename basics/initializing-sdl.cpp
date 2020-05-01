/*
 * Example of initializing SDL
 */

#include <SDL/SDL.h>
#include <iostream>

int main(){
    SDL_Surface *screen;

    // Initialize SDL's video system and check for erros
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        std::cout << "Unable to initialize SDL: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Make sure SDL_Quit gets called when the program exits!
    atexit(SDL_Quit);

    // Attemp to set a 640x480 hicolor video mode
    screen = SDL_SetVideoMode(640, 480, 16, SDL_FULLSCREEN);
    if(screen == NULL){
        std::cout << "Unable to set video mode: " << SDL_GetError() << std::endl;
        return 1;
    }

    // If we got this far, everything worked!
    std::cout << "Success!" << std::endl;
    return 0;
}
