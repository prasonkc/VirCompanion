#include <SDL2/SDL.h>
#include <iostream>

const int windowHeight = 400;
const int windowWidth = 400;

bool init();
void kill();
bool loadBMP(const char* filePath);

// Pointers to window and surface
SDL_Window* window;
SDL_Surface* surface;
SDL_Surface* image;

int main() {
    if(!init()) return 0;
    if(!loadBMP("image.bmp")) return 0;

    SDL_BlitSurface( image, NULL, surface, NULL );
    SDL_UpdateWindowSurface(window);


    // // Draw a rectangle and update window surface
    // SDL_FillRect(surface, NULL,SDL_MapRGB(surface->format, 255, 90, 120));
    // SDL_UpdateWindowSurface(window);
    // SDL_Delay(5000);

    // // Draw a rectangle and update window surface again after 5 seconds
    // SDL_FillRect(surface, NULL,SDL_MapRGB(surface->format, 200, 200, 200));
    // SDL_UpdateWindowSurface(window);
    // SDL_Delay(5000);

    SDL_Delay(10000);

    kill();
    return 0;
}

bool init(){
    // Initialize SDL2 and draw a window
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Virtual Pet",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN
    );

    if (!window)
    {
        std::cout << "" << "Failed to initialize window" << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize a surface for software rendering
    surface = SDL_GetWindowSurface( window );
    if (!surface)
    {
        std::cout << "" << "Failed to initialize surface" << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

void kill(){
    SDL_FreeSurface(image);
    // Destroy the window
    SDL_DestroyWindow( window );

    // Clear the memory and quit program
    window = NULL;
    surface = NULL;
    image = NULL;

    SDL_Quit();
}

bool loadBMP(const char* filePath){
    SDL_Surface *temp;
    temp = SDL_LoadBMP(filePath);

    if(!temp){
        std::cout<<"Failed to Load image" << SDL_GetError() << std::endl;
        return false;
    }

    image = SDL_ConvertSurface( temp, surface->format, 0 );
    SDL_FreeSurface(temp);
    return true;
}