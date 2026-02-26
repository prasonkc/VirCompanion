#include "App.h"
#include <iostream>

bool App::init() {
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

    // Initialize each animation
        animationMap.emplace(AnimationState::Idle, Animation(32, 32, 8, 150));
        animationMap.emplace(AnimationState::Happy, Animation(32, 32, 8, 150));
        animationMap.emplace(AnimationState::Headpat, Animation(32, 32, 8, 150));
        animationMap.emplace(AnimationState::Sad, Animation(32, 32, 8, 150));

    return true;
}

void App::shutdown(){
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

bool App::loadBMP(const char* filePath){
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

void App::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect src = animationMap[currentState].getSourceRect();
    SDL_RenderCopy(renderer, texture, &src, nullptr);
    
    SDL_RenderPresent(renderer);
}

void App::run(){
    while (running){
        handleEvents();
        render();
        SDL_Delay(10);
        animationMap[currentState].update();    }
}

void App::handleEvents() {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false;

        if (e.type == SDL_MOUSEBUTTONDOWN &&
            e.button.button == SDL_BUTTON_RIGHT) {

            borderless = !borderless;
            SDL_SetWindowBordered(window, borderless ? SDL_FALSE : SDL_TRUE);
        }
    }
}

void App::setAnimationState(AnimationState state){
    if (state == currentState)
        return;

    currentState = state;

    switch (currentState) {
        case AnimationState::Idle:
            currentAnim = &idleAnim;
            break;
        case AnimationState::Headpat:
            currentAnim = &headpatAnim;
            break;
        case AnimationState::Happy:
            currentAnim = &happyAnim;
            break;
        case AnimationState::Sad:
            currentAnim = &sadAnim;
            break;
        case AnimationState::Drag:
            currentAnim = &dragAnim;
            break;
    }

    currentAnim->reset();
}
