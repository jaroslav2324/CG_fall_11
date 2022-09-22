#include "settings.h"
#include "Color.h"
#include "Parallelepiped.h"
#include "Pyramid.h"


class ZBuffer{

public:
    ZBuffer();
    //TODO 
    void renderBuffer(SDL_Renderer* renderer);

private:
    void clearZBuffer();
    void placeParallelepiped(Parallelepiped* par);
    //TODO
    void placePyramid(Pyramid* pyr);

    Color screenColorsArray[SCREEN_HEIGHT][SCREEN_WIDTH];
    double zBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
};