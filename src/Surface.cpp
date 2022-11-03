#include "Surface.h"

Surface::Surface(int numPoints, Point* array, Color color){

    Surface::numPoints = numPoints;
    Surface::color = color;

    pointsArray = new Point[numPoints];
    for (int i = 0; i < numPoints; i++)
        pointsArray[i] = array[i];

    equationPlane = new EquationPlane(pointsArray); 

}

Surface::Surface(){

    numPoints = 0;
    color = Color(255, 255, 255, 255);
    pointsArray = nullptr;
    equationPlane = nullptr;
}

Surface::~Surface(){

    if (pointsArray != nullptr)
        delete pointsArray;

    if (equationPlane != nullptr)
        delete equationPlane;
}

SDL_Rect Surface::getCoveringSurfaceRect(){

    double minX = INF, minY = INF, maxX = MINUS_INF, maxY = MINUS_INF;

    for (int i = 0; i < numPoints; i++){

        if (pointsArray[i].x < minX)
            minX = pointsArray[i].x;
        if (pointsArray[i].x > maxX)
            maxX = pointsArray[i].x;

        if (pointsArray[i].y < minY)
            minY = pointsArray[i].y;
        if (pointsArray[i].y > maxY)
            maxY = pointsArray[i].y;
    }

    SDL_Rect rect = {0, 0, 0, 0};
    rect.x = round(minX);
    rect.y = round(minY);
    rect.w = round(maxX - minX);
    rect.h = round(maxY - minY);

    return rect;
}


//only for convex polygons
bool Surface::isPointInsideSurface(int x, int y){

    int numLinesFromLeft = 0;
    int numLinesFromRight = 0;
 
    for (int indexFirstP = 0, indexSecondP = 1; indexFirstP < numPoints; indexFirstP++, indexSecondP = (indexFirstP + 1) % numPoints) {

        // if horizontal beam do not pass through line
        if ((pointsArray[indexFirstP].y < y && pointsArray[indexSecondP].y < y) ||
            (pointsArray[indexFirstP].y > y && pointsArray[indexSecondP].y > y))
            continue;

        Line2D line(pointsArray[indexFirstP].x, pointsArray[indexFirstP].y, pointsArray[indexSecondP].x, pointsArray[indexSecondP].y);

        if (line.isPointRightFromLine(x, y))
            numLinesFromRight++;
        else
            numLinesFromLeft++;
    }

    if (0 < numLinesFromLeft && 0 < numLinesFromRight && numLinesFromLeft == numLinesFromRight)
        return true;
    return false;
    
}

Color Surface::getSurfaceColor(){
    return color;
}

double Surface::getX(double y, double z){

    if (equationPlane->isParallelToOX())
        return findMaxX();

    return equationPlane->findX(y, z);
}

double Surface::getY(double x, double z){

    if (equationPlane->isParallelToOY())
        return findMaxY();

    return equationPlane->findY(x, z);
}

double Surface::getZ(double x, double y){

    if (equationPlane->isParallelToOZ())
        return findMaxZ();

    return equationPlane->findZ(x, y);
}

double Surface::findMaxZ() {

    double maxZ = pointsArray[0].z;
    for (int i = 0; i < numPoints; i++)
        if (pointsArray[i].z > maxZ)
            maxZ = pointsArray[i].z;

    return maxZ;
}

double Surface::findMaxX() {

    double maxX = pointsArray[0].x;
    for (int i = 0; i < numPoints; i++)
        if (pointsArray[i].x > maxX)
            maxX = pointsArray[i].x;

    return maxX;
}

double Surface::findMaxY() {

    double maxY = pointsArray[0].y;
    for (int i = 0; i < numPoints; i++)
        if (pointsArray[i].y > maxY)
            maxY = pointsArray[i].y;

    return maxY;
}

Point Surface::getCenter() {

    double x = 0, y = 0, z = 0;
    for (int i = 0; i < numPoints; i++) {
        x += pointsArray[i].x;
        y += pointsArray[i].y;
        z += pointsArray[i].z;
    }

    x /= numPoints;
    y /= numPoints;
    z /= numPoints;

    return Point(x, y, z);
}

void Surface::addBorderLinesPointsToVector(std::vector<std::pair<int, int>>& vec) {

    int numSegments = numPoints;

    for (int i = 0, j = 1; i < numSegments; i++, j = (i + 1) % numSegments) {

        int x1 = pointsArray[i].x;
        int y1 = pointsArray[i].y;
        int x2 = pointsArray[j].x;
        int y2 = pointsArray[j].y;

        LineSegment2D seg(x1, y1, x2, y2);
        seg.addAllSegmentPointsToVector(vec);
    }
}
