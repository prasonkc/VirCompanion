#include <SDL2/SDL.h>
#include <iostream>

const int windowHeight = 400;
const int windowWidth = 400;

bool init();
void kill();
bool loadBMP(const char* filePath);
bool loop();

// Pointers to window, texture and renderer
SDL_Window* window;
SDL_Renderer* renderer;
SDL_Texture* texture;

// Toogle window borders
bool isBorderless = true;

int main() {
    if(!init()) return 0;
    if(!loadBMP("image.bmp")) return 0;

    // Render the texture (GPU rendering)
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);

    while ( loop() ) {
		// wait before processing the next frame
		SDL_Delay(10);
	}


    return 0;
}
//test

bool init(){
    // Initialize SDL2 and window
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "SDL Init Failed: " << SDL_GetError() << std::endl;
        return false;
    }

    window = SDL_CreateWindow(
        "Virtual Pet",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        windowWidth, windowHeight,
        SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS
    );

    if (!window)
    {
        std::cout << "" << "Failed to initialize window" << SDL_GetError() << std::endl;
        return false;
    }

    // Initialize renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        std::cout << "" << "Failed to initialize renderer" << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void kill(){
    // Destroy the window
    SDL_DestroyWindow( window );

    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);

    // Clear the memory and quit program
    texture = NULL;
    renderer = NULL;
    window = NULL;

    SDL_Quit();
}

bool loadBMP(const char* filePath){

    // Load the image to temporary variable
    SDL_Surface *temp;
    temp = SDL_LoadBMP(filePath);

    if(!temp){
        std::cout<<"Failed to Load image" << SDL_GetError() << std::endl;
        return false;
    }

    // Create a texture from the temporary variable
    texture = SDL_CreateTextureFromSurface( renderer, temp );

    // Cleanup and return
    SDL_FreeSurface(temp);
    temp = NULL;
    return true;
}

bool loop(){
    SDL_Event e;

    while( SDL_PollEvent( &e ) != 0 ) {
		switch (e.type) {
			case SDL_QUIT:
				return false;
                break;

			case SDL_MOUSEBUTTONDOWN:
            // Toggle the broder on right click
				if(e.button.button == SDL_BUTTON_RIGHT){
                    isBorderless = !isBorderless;
                    SDL_SetWindowBordered(window, isBorderless ? SDL_FALSE : SDL_TRUE);
                }
				break;
		}
	}
    return true;
}