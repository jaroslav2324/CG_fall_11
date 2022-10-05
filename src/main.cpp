#include "SDL.h"

#include <iostream>

using std::cout;
using std::endl;

#include "settings.h"
#include "ZBuffer.h"
#include "Surface.h"

int main(int, char**){

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        cout << "Error with SDL_Init" << endl;

    SDL_Window* window = SDL_CreateWindow("KG_Curs", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);


    ZBuffer buffer;
    Parallelepiped* parallelepiped = new Parallelepiped();
    Pyramid* pyramid = new Pyramid();


    buffer.renderBuffer(renderer, parallelepiped, pyramid);

    SDL_Delay(20000);

    delete parallelepiped;
    delete pyramid;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
