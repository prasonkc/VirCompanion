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
    animationMap.emplace(AnimationState::Drag, Animation(32, 32, 8, 150));

    // Asset paths
    animationPaths[AnimationState::Idle] = "assets/idle.bmp";
    animationPaths[AnimationState::Happy] = "assets/happy.bmp";
    animationPaths[AnimationState::Headpat] = "assets/headpat.bmp";
    animationPaths[AnimationState::Sad] = "assets/sad.bmp";
    animationPaths[AnimationState::Drag] = "assets/drag.bmp";

    // Load the texture from each path
    for (const auto& entry : animationPaths) {
        SDL_Texture* tex = loadBMPTexture(entry.second.c_str());
        animationTextures[entry.first] = tex;
    }
    animationMap[currentState].reset();

    return true;
}

void App::shutdown(){
    // Destroy the window
    SDL_DestroyWindow( window );

    for (auto& entry : animationTextures) {
        if (entry.second) {
            SDL_DestroyTexture(entry.second);
        }
    }
    SDL_DestroyRenderer(renderer);

    // Clear the memory and quit program
    renderer = NULL;
    window = NULL;
    animationTextures.clear();

    SDL_Quit();
}

SDL_Texture* App::loadBMPTexture(const char* filePath){
    // Load the image to temporary variable
    SDL_Surface *temp;
    temp = SDL_LoadBMP(filePath);

    if(!temp){
        std::cout<<"Failed to Load image " << filePath << ": " << SDL_GetError() << std::endl;
        return nullptr;
    }

    // Create a texture from the temporary variable
    SDL_Texture* created = SDL_CreateTextureFromSurface( renderer, temp );

    // Cleanup and return
    SDL_FreeSurface(temp);
    temp = NULL;
    return created;
}

void App::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_Rect src = animationMap[currentState].getSourceRect();
    SDL_Texture* tex = animationTextures[currentState];
    if (tex) {
        SDL_RenderCopy(renderer, tex, &src, nullptr);
    }

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
        if (e.type == SDL_QUIT) {
            running = false;
            continue;
        }

        if (e.type == SDL_KEYDOWN) {
            switch (e.key.keysym.sym) {
                case SDLK_ESCAPE:
                    running = false;
                    break;
                case SDLK_1:
                    setAnimationState(AnimationState::Idle);
                    break;
                case SDLK_2:
                    setAnimationState(AnimationState::Happy);
                    break;
                case SDLK_3:
                    setAnimationState(AnimationState::Headpat);
                    break;
                case SDLK_4:
                    setAnimationState(AnimationState::Sad);
                    break;
                case SDLK_5:
                    setAnimationState(AnimationState::Drag);
                    break;
                default:
                    break;
            }
        }

        if (e.type == SDL_WINDOWEVENT) {
            if (e.window.event == SDL_WINDOWEVENT_ENTER) {
                setAnimationState(AnimationState::Happy);
            } else if (e.window.event == SDL_WINDOWEVENT_LEAVE) {
                setAnimationState(AnimationState::Sad);
            }
        }

        if (e.type == SDL_MOUSEBUTTONDOWN &&
            e.button.button == SDL_BUTTON_RIGHT) {

            borderless = !borderless;
            SDL_SetWindowBordered(window, borderless ? SDL_FALSE : SDL_TRUE);
        }

        if (e.type == SDL_MOUSEBUTTONDOWN &&
            e.button.button == SDL_BUTTON_LEFT) {
            setAnimationState(AnimationState::Headpat);
        }

        if (e.type == SDL_MOUSEMOTION &&
            (e.motion.state & SDL_BUTTON_LMASK)) {
            setAnimationState(AnimationState::Drag);
        }

        if (e.type == SDL_MOUSEBUTTONUP &&
            e.button.button == SDL_BUTTON_LEFT) {
            setAnimationState(AnimationState::Idle);
        }

    }
}

void App::setAnimationState(AnimationState state){
    if (state == currentState)
        return;

    currentState = state;
    animationMap[currentState].reset();
}
