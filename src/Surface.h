#pragma once

#include "SDL2/SDL.h"

#include "settings.h"
#include "Color.h"
#include "Point.h"
#include "EquationPlane.h"

class Surface{
public:
    Surface(int numPoints, Point* array, Color color);
    Surface();
    ~Surface();

    bool isPointInsideSurface(int x, int y);

    SDL_Rect getCoveringSurfaceRect();
    Color getSurfaceColor();

    double getX(double y, double z);
    double getY(double x, double z);
    double getZ(double x, double y);

private:

    int numPoints;
    Color color;
    Point* pointsArray = nullptr;

    EquationPlane* equationPlane = nullptr;
};
