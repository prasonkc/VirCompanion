#ifndef ANIMATION_H
#define ANIMATION_H

#include <SDL2/SDL.h>
#include <cstdint>

class Animation {
public:
    Animation(int frameWidth, int frameHeight, int totalFrames, uint32_t frameDelay);

    void update();
    SDL_Rect getSourceRect() const;

private:
    int frameWidth;
    int frameHeight;
    int totalFrames;

    int currentFrame = 0;

    uint32_t frameDelay;
    uint32_t lastFrameTime = 0;
};

#endif
