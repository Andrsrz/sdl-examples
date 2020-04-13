/*
 * Animation with SDL - First Attempt!
 */

#include <SDL/SDL.h>
#include <iostream>

const int NUM_BUTTERFLIES = 15;
const int MAX_SPEED = 6;

/* This structure stores the information for one on-screen butterfly. */
typedef struct butterfly {
    int x, y; // Screen position
    int dx, dy; // Movement vector
} butterfly_t, *butterfly_p;

/* Array of butterflies */
static butterfly_t butterflies[NUM_BUTTERFLIES];

/* These are no global variables, for convenience */
static SDL_Surface *screen;
static SDL_Surface *butterfly;

/*
 * This routine loop through the array of butterflies and sets each to a random
 * starting position and direction.
 */
static void init_butterflies(){
    int i;
    for(i = 0; i < NUM_BUTTERFLIES; i++){
        butterflies[i].x = rand() % screen->w;
        butterflies[i].y = rand() % screen->h;
        butterflies[i].dx = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
        butterflies[i].dy = (rand() % (MAX_SPEED * 2)) - MAX_SPEED;
    }
}

/* This routine moves each butterfly by its motion vector. */
static void move_butterflies(){
    int i;
    for(i = 0; i < NUM_BUTTERFLIES; i++){
        /* Move the butterfly by its motion vector. */
        butterflies[i].x += butterflies[i].dx;
        butterflies[i].y += butterflies[i].dy;
        /* Turn the butterfliesaround if it hits the edge of the screen. */
        if (butterflies[i].x < 0 || butterflies[i].x > screen->w - 1)
            butterflies[i].dx = -butterflies[i].dx;
        if (butterflies[i].y < 0 || butterflies[i].y > screen->h - 1)
            butterflies[i].dy = -butterflies[i].dy;
    }
}

/* This routine draws each butterfly to the screen surface. */
static void draw_butterflies() {
    int i;
    SDL_Rect src, dest;
    for (i = 0; i < NUM_BUTTERFLIES; i++) {
        src.x = 0;
        src.y = 0;
        src.w = butterfly->w;
        src.h = butterfly->h;
        /*
         * The butterfly’s position specifies its center.
         * We subtract half of its width and height to get
         * its upper left corner.
        */
        dest.x = butterflies[i].x - butterfly->w / 2;
        dest.y = butterflies[i].y - butterfly->h / 2;
        dest.w = butterfly->w;
        dest.h = butterfly->h;
        SDL_BlitSurface(butterfly, &src, screen, &dest);
    }
}

int main(){
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
    /* Initialize the butterfly position data. */
    init_butterflies();

    /* Animate 300 frames (approximately 10 seconds). */
    for(frames = 0; frames < 10000; frames++){
        /* Draw the background image. */
        src.x = 0;
        src.y = 0;
        src.w = background->w;
        src.h = background->h;
        dest = src;
        SDL_BlitSurface(background, &src, screen, &dest);
        /* Put the butterflies on the screen. */
        draw_butterflies();
        /* Ask SDL to update the entire screen. */
        SDL_UpdateRect(screen, 0, 0, 0, 0);
        /* Move the butterflies for the next frame. */
        move_butterflies();
    }

    /* Free the memory that was allocated to the bitmap. */
    SDL_FreeSurface(background);
    SDL_FreeSurface(butterfly);

    return 0;
}
