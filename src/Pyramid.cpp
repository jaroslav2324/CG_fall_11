
#include "Pyramid.h"

Pyramid::Pyramid(){

    pointsCoords = new Matrix(numVertexes, 4);

    // fill last row with 1(to multiply matrixes correctly)(4th dimension -_-)
    for (int i = 0; i < numVertexes; i++)
        pointsCoords->setElm(i, 3, 1);

    // set x coords
    pointsCoords->setElm(0, 0, 100);
    pointsCoords->setElm(1, 0, 130);
    pointsCoords->setElm(2, 0, 180);
    pointsCoords->setElm(3, 0, 200);

    // set y coords

    pointsCoords->setElm(0, 1, 60);
    pointsCoords->setElm(1, 1, 60);
    pointsCoords->setElm(2, 1, 160);
    pointsCoords->setElm(3, 1, 60);

    // set z coords

    pointsCoords->setElm(0, 2, 200);
    pointsCoords->setElm(1, 2, 80);
    pointsCoords->setElm(2, 2, 120);
    pointsCoords->setElm(3, 2, 200);

    findCenter();
}

Pyramid::~Pyramid(){

    delete pointsCoords;
}

void Pyramid::findCenter(){


    double centerX = 0;
    //sum all x from pointsCoords matrix
    for (int i = 0; i < numVertexes; i++)
        centerX += pointsCoords->getElm(i, 0);

    centerX /= numVertexes;

    double centerY = 0;
    //sum all y from pointsCoords matrix
    for (int i = 0; i < numVertexes; i++)
        centerY += pointsCoords->getElm(i, 1);

    centerY /= numVertexes;

    double centerZ = 0;
    //sum all z from pointsCoords matrix
    for (int i = 0; i < numVertexes; i++)
        centerZ += pointsCoords->getElm(i, 2);
        
    centerZ /= numVertexes;

    centerPoint.x = centerX;
    centerPoint.y = centerY;
    centerPoint.z = centerZ;
}

// moving center of parallelepiped to (0, 0, 0) point
void Pyramid::moveToCenterCoords(){

    //shift to center of the world along x axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 0, -centerPoint.x);

    //shift to center of the world along y axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 1, -centerPoint.y);

    //shift to center of the world along z axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 2, -centerPoint.z);
}

// return object to previous coords after moving to center.
// Do not change center coords before completing moving to and from world center
void Pyramid::moveFromCenterCoords(){

    //shift back from center of the world along x axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 0, centerPoint.x);

    //shift back from center of the world along y axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 1, centerPoint.y);

    //shift back from center of the world along z axis
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 2, centerPoint.z);

}

void Pyramid::addToPointsCoordsMatrix(int numRow, int numCol, int addValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) + addValue;
    pointsCoords->setElm(numRow, numCol, coord);
}

void Pyramid::mulToPointsCoordsMatrix(int numRow, int numCol, int mulValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) * mulValue;
    pointsCoords->setElm(numRow, numCol, coord);
}


void Pyramid::moveAlongX(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 0, moveDistance);
}

void Pyramid::moveAlongY(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 1, moveDistance);
}

void Pyramid::moveAlongZ(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 2, moveDistance);

}

void Pyramid::rotateAroundX(double rotationValue){

    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createXRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Pyramid::rotateAroundY(double rotationValue){
 
    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createYRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Pyramid::rotateAroundZ(double rotationValue){
    
    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createZRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}


void Pyramid::scale(double scaleCoefficient){

    findCenter();
    moveToCenterCoords();

    // scale x coord
    for (int i = 0; i < numVertexes; i++)
        mulToPointsCoordsMatrix(i, 0, scaleCoefficient);

    // scale y coord
    for (int i = 0; i < numVertexes; i++)
        mulToPointsCoordsMatrix(i, 1, scaleCoefficient);

    // scale z coord
    for (int i = 0; i < numVertexes; i++)
        mulToPointsCoordsMatrix(i, 2, scaleCoefficient);

    moveFromCenterCoords();
}

Surface** Pyramid::createArrayOfSurfaces(){

    //TODO refactor

    int numSurfaces = 4;
    int numPointsInSurface = 3;

    Color* surfacesColors = new Color[numSurfaces];
    // red
    surfacesColors[0] = Color(255, 0, 0, 255);
    // green
    surfacesColors[1] = Color(0, 255, 0, 255);
    // blue
    surfacesColors[2] = Color(0, 0, 255, 255);
    // yellow
    surfacesColors[3] = Color(255, 255, 0, 255);

    Point* arrayOfSurfacePoints = new Point[numPointsInSurface];
    Point p;

    Surface** surfaceArray = new Surface * [numSurfaces];

    int indexSurface = 0;


    // create surfaces of pyramid from matrix of points
    for (int i = 0; i < numSurfaces; i++){

        //fill array of surface points for every surface
        int indexFirstPoint = i % numSurfaces;

        p.x = pointsCoords->getElm(indexFirstPoint, 0);
        p.y = pointsCoords->getElm(indexFirstPoint, 1);
        p.z = pointsCoords->getElm(indexFirstPoint, 2);

        arrayOfSurfacePoints[0] = p;

        int indexSecondPoint = (i + 1) % numSurfaces;

        p.x = pointsCoords->getElm(indexSecondPoint, 0);
        p.y = pointsCoords->getElm(indexSecondPoint, 1);
        p.z = pointsCoords->getElm(indexSecondPoint, 2);

        arrayOfSurfacePoints[1] = p;

        int indexThirdPoint = (i + 2) % numSurfaces;

        p.x = pointsCoords->getElm(indexThirdPoint, 0);
        p.y = pointsCoords->getElm(indexThirdPoint, 1);
        p.z = pointsCoords->getElm(indexThirdPoint, 2);

        arrayOfSurfacePoints[2] = p;

        //create surface
        surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
        indexSurface++;
    }

    delete[] surfacesColors;
    delete[] arrayOfSurfacePoints;

    return surfaceArray;
}

int Pyramid::getNumSurfaces(){
    return numSurfaces;
}
