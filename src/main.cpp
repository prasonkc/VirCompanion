#include <SDL2/SDL.h>
#include <iostream>

const int windowWidth = 300;
const int windowHeight = 400;

bool init();
void kill();

// Pointers to window and surface
SDL_Window* window;
SDL_Surface* surface;

int main() {
    if(!init()) return 1;

    // Draw a rectangle and update window surface
    SDL_FillRect(surface, NULL,SDL_MapRGB(surface->format, 255, 90, 120));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    // Draw a rectangle and update window surface again after 5 seconds
    SDL_FillRect(surface, NULL,SDL_MapRGB(surface->format, 200, 200, 200));
    SDL_UpdateWindowSurface(window);
    SDL_Delay(5000);

    kill();
    return 0;
}

bool init(){
    // Initialize SDL2 and draw a window
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Virtual Pet",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowHeight, windowWidth,
        SDL_WINDOW_SHOWN
    );

    // Initialize a surface for software rendering
    surface = SDL_GetWindowSurface( window );
    if (!surface || !window)
    {
        std::cout << "" << "Failed to initialize SDL2" << SDL_GetError();
        system("exit");
        return false;
    }

    return true;
}

void kill(){
    // Destroy the window
    SDL_DestroyWindow( window );

    // Clear the memory and quit program
    window = NULL;
    surface = NULL;
    SDL_Quit();
}
