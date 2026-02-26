#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <memory>
#include <unordered_map>

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

        // Define animation states for each animations
        enum class AnimationState{Idle, Headpat, Happy, Sad, Drag};

        // Map every animation to its state and set the default to idle animation
        std::unordered_map<AnimationState, Animation> animationMap;

        // Store the current animation state
        Animation* currentAnim = nullptr;
        AnimationState currentState = AnimationState::Idle;

        // Animation state initialization
        Animation idleAnim;
        Animation headpatAnim;
        Animation happyAnim;
        Animation sadAnim;
        Animation dragAnim;

        void setAnimationState(AnimationState state);

};


#endif
