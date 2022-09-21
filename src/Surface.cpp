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