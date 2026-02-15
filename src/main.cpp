#include <SDL2/SDL.h>
#include <iostream>

#include "App.h"

int main() {
    App app;

    if (!app.init()) return 1;
    if (!app.loadBMP("image.bmp")) return 1;

    app.run();
    app.shutdown();

    return 0;
}