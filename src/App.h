#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include "Animation.h"


class App{
    public:
        bool init();
        void shutdown();
        bool loadBMP(const char* filePath);
        void run();

    private:
        void handleEvents();
        void render();

        // Pointers to window, texture and renderer
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Texture* texture;

        // Toogle window borders
        bool borderless = true;
        // Toogle event loop
        bool running = true;

        //Window ratios
        int windowHeight = 400;
        int windowWidth = 400;

        Animation idleAnim{32, 32, 4, 200};

};


#endif
