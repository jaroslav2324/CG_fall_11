#include "Color.h"
#include "Point.h"

class Surface{
public:
    Surface(int numPoints, Point* array, Color color);
    Surface();
    ~Surface();

private:

    int numPoints;
    Color color;
    Point* pointsArray = nullptr;
};
