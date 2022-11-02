
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(){

    pointsCoords = new Matrix(numVertexes, 4);

    // fill last row with 1(to multiply matrixes correctly)(4th dimension -_-)
    for (int i = 0; i < numVertexes; i++)
        pointsCoords->setElm(i, 3, 1);

    // set x coords
    pointsCoords->setElm(0, 0, 50);
    pointsCoords->setElm(1, 0, 50);
    pointsCoords->setElm(4, 0, 50);
    pointsCoords->setElm(5, 0, 50);

    pointsCoords->setElm(2, 0, 150);
    pointsCoords->setElm(3, 0, 150);
    pointsCoords->setElm(6, 0, 150);
    pointsCoords->setElm(7, 0, 150);

    // set y coords

    pointsCoords->setElm(0, 1, 250);
    pointsCoords->setElm(1, 1, 250);
    pointsCoords->setElm(2, 1, 250);
    pointsCoords->setElm(3, 1, 250);

    pointsCoords->setElm(4, 1, 50);
    pointsCoords->setElm(5, 1, 50);
    pointsCoords->setElm(6, 1, 50);
    pointsCoords->setElm(7, 1, 50);

    // set z coords

    pointsCoords->setElm(0, 2, 150);
    pointsCoords->setElm(3, 2, 150);
    pointsCoords->setElm(4, 2, 150);
    pointsCoords->setElm(7, 2, 150);

    pointsCoords->setElm(5, 2, 50);
    pointsCoords->setElm(1, 2, 50);
    pointsCoords->setElm(2, 2, 50);
    pointsCoords->setElm(6, 2, 50);

    findCenter();
}

Parallelepiped::~Parallelepiped(){

    delete pointsCoords;
}

void Parallelepiped::findCenter(){


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
void Parallelepiped::moveToCenterCoords(){

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
void Parallelepiped::moveFromCenterCoords(){

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

void Parallelepiped::addToPointsCoordsMatrix(int numRow, int numCol, double addValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) + addValue;
    pointsCoords->setElm(numRow, numCol, coord);
}

void Parallelepiped::mulToPointsCoordsMatrix(int numRow, int numCol, double mulValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) * mulValue;
    pointsCoords->setElm(numRow, numCol, coord);
}


void Parallelepiped::moveAlongX(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 0, moveDistance);
}

void Parallelepiped::moveAlongY(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 1, moveDistance);
}

void Parallelepiped::moveAlongZ(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    for (int i = 0; i < numVertexes; i++)
        addToPointsCoordsMatrix(i, 2, moveDistance);

}

void Parallelepiped::rotateAroundX(double rotationValue){

    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createXRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Parallelepiped::rotateAroundY(double rotationValue){
 
    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createYRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Parallelepiped::rotateAroundZ(double rotationValue){
    
    findCenter();
    moveToCenterCoords();
	
    Matrix rotationMatrix = createZRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}


void Parallelepiped::scale(double scaleCoefficient){

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

Surface** Parallelepiped::createArrayOfSurfaces(){

    int numSurfaces = 6;
    int numSideSurfaces = 4;
    int numPointsInSurface = 4;

    Color* surfacesColors = new Color[numSurfaces];
    // dark red
    surfacesColors[0] = Color(180, 0, 0, 255);
    // dark green
    surfacesColors[1] = Color(0, 180, 0, 255);
    // dark blue
    surfacesColors[2] = Color(0, 0, 180, 255);
    // dark yellow
    surfacesColors[3] = Color(180, 180, 0, 255);
    // dark magenta
    surfacesColors[4] = Color(180, 0, 180, 255);
    // dark cyan
    surfacesColors[5] = Color(0, 180, 180, 255);

    Point* arrayOfSurfacePoints = new Point[numPointsInSurface];
    Point p;

    Surface** surfaceArray = new Surface*[numSurfaces];

    int indexSurface = 0;

    // create surfaces of parallelepiped from matrix of points
    // 
    // create top and bottom surfaces
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 0, 1, 2, 3);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 4, 5, 6, 7);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;

    // create side surfaces
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 0, 1, 5, 4);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 1, 2, 6, 5);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 2, 3, 7, 6);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;
    fillArrayOfSurfacePoints(arrayOfSurfacePoints, 3, 0, 4, 7);
    surfaceArray[indexSurface] = new Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[indexSurface]);
    indexSurface++;


    delete[] surfacesColors;
    delete[] arrayOfSurfacePoints;

    return surfaceArray;
}

int Parallelepiped::getNumSurfaces(){
    return numSurfaces;
}

void Parallelepiped::fillArrayOfSurfacePoints(Point* pointArr, int index1, int index2, int index3, int index4) {

    const int numPointsInSurface = 4;
    int indexesArr[numPointsInSurface] = { index1, index2, index3, index4 };
    Point p;

    for (int i = 0; i < numPointsInSurface; i++) {
        int index = indexesArr[i];

        p.x = pointsCoords->getElm(index, 0);
        p.y = pointsCoords->getElm(index, 1);
        p.z = pointsCoords->getElm(index, 2);

        pointArr[i] = p;
    }
}
