#include "SDL2/SDL.h"

#include "settings.h"
#include "Color.h"
#include "Point.h"

class Surface{
public:
    Surface(int numPoints, Point* array, Color color);
    Surface();
    ~Surface();

    SDL_Rect getCoveringSurfaceRect();

private:

    int numPoints;
    Color color;
    Point* pointsArray = nullptr;
};
