#include <SDL2/SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Virtual Pet",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        400, 300,
        SDL_WINDOW_SHOWN
    );
    SDL_Delay(10000);
    SDL_Quit();
    return 0;
}
