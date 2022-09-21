#include "Surface.h"

Surface::Surface(int numPoints, Point* array, Color color){

    Surface::numPoints = numPoints;
    Surface::color = color;

    pointsArray = new Point[numPoints];
    for (int i = 0; i < numPoints; i++)
        pointsArray[i] = array[i];

}

Surface::Surface(){

    numPoints = 0;
    color = Color(255, 255, 255, 255);
    pointsArray = nullptr;
}

Surface::~Surface(){

    if (pointsArray != nullptr)
        delete pointsArray;
}

SDL_Rect Surface::getCoveringSurfaceRect(){

    double minX = INFINITY, minY = INFINITY, maxX = MINUS_INFINITY, maxY = MINUS_INFINITY;

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

    SDL_Rect rect;
    rect.x = round(minX);
    rect.y = round(minY);
    rect.w = rect.x + round(maxX - minX);
    rect.h = rect.y + round(maxY - minY);

    return rect;
}
