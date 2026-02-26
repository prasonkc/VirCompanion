#include "Animation.h"

// Animation construictor
Animation::Animation(int fw, int fh, int tf, uint32_t delay, bool loopAni)
{
    frameWidth = fw;
    frameHeight = fh;
    totalFrames = tf;
    frameDelay = delay;
    loop = loopAni;
}

// Update thhe animation each tick
void Animation::update() {
    // Get the number of milliseconds since the library was initialized
    uint32_t now = SDL_GetTicks();

    // If time elapsed is greater than the lastFrameTime + frameDelay
    if (now > lastFrameTime + frameDelay) {
        // Update the current frame to next frame in the animation
        currentFrame = (currentFrame + 1) % totalFrames;
        lastFrameTime = now;
    }
}

// Returns the rect object where animation is rendered
SDL_Rect Animation::getSourceRect() const {
    SDL_Rect rect;
    rect.x = currentFrame * frameWidth;
    rect.y = 0;
    rect.w = frameWidth;
    rect.h = frameHeight;
    return rect;
}

// Reset the animation
void Animation::reset() {
    currentFrame = 0;
    finished = false;
    lastFrameTime = SDL_GetTicks();
}