#include "Animation.h"

Animation::Animation(int fw, int fh, int tf, uint32_t delay)
    : frameWidth(fw),
      frameHeight(fh),
      totalFrames(tf),
      frameDelay(delay)
{
}

void Animation::update() {
    uint32_t now = SDL_GetTicks();

    if (now > lastFrameTime + frameDelay) {
        currentFrame = (currentFrame + 1) % totalFrames;
        lastFrameTime = now;
    }
}

SDL_Rect Animation::getSourceRect() const {
    SDL_Rect rect;
    rect.x = currentFrame * frameWidth;
    rect.y = 0;
    rect.w = frameWidth;
    rect.h = frameHeight;
    return rect;
}
