#include "settings.h"
#include "Color.h"
#include "Parallelepiped.h"
#include "Pyramid.h"


class ZBuffer{

public:
    ZBuffer();

private:
    void clearZBuffer();
    void placeParallelepiped(Parallelepiped* par);
    void placePyramid(Pyramid* pyr);

    Color screenColorsArray[SCREEN_HEIGHT][SCREEN_WIDTH];
    double zBuffer[SCREEN_HEIGHT][SCREEN_WIDTH];
};