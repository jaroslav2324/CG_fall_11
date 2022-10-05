#pragma once

#include <cmath>

#include "SDL.h"

#include "settings.h"
#include "Color.h"
#include "Point.h"
#include "EquationPlane.h"
#include "Line.h"

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

    Point getCenter();

private:

    double findMaxZ();
    double findMaxX();
    double findMaxY();

    int numPoints;
    Color color;
    Point* pointsArray = nullptr;

    EquationPlane* equationPlane = nullptr;
};
