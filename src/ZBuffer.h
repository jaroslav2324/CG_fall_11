#pragma once

#include "settings.h"
#include "Color.h"
#include "Parallelepiped.h"
#include "Pyramid.h"


class ZBuffer{

public:
    ZBuffer();

    void renderBuffer(SDL_Renderer* renderer, Parallelepiped* par, Pyramid* pyr);

private:
    void clearZBuffer();
    void placeParallelepiped(Parallelepiped* par);
    void placePyramid(Pyramid* pyr);

    Color screenColorsArray[SCREEN_HEIGHT][SCREEN_WIDTH];
    double zBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
};