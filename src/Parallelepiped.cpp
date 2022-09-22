
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(){

    pointsCoords = new Matrix(numVertexes, 4);

    //TODO set coords of parall

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

void Parallelepiped::addToPointsCoordsMatrix(int numRow, int numCol, int addValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) + addValue;
    pointsCoords->setElm(numRow, numCol, coord);
}

void Parallelepiped::mulToPointsCoordsMatrix(int numRow, int numCol, int mulValue){

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

Surface* Parallelepiped::createArrayOfSurfaces(){

    //TODO refactor

    int numSurfaces = 6;
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

    Surface* surfaceArray = new Surface[numSurfaces];


    // create surfaces of parallelepiped from matrix of points
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

        int indexFourthPoint = (i + 3) % numSurfaces;

        p.x = pointsCoords->getElm(indexFourthPoint, 0);
        p.y = pointsCoords->getElm(indexFourthPoint, 1);
        p.z = pointsCoords->getElm(indexFourthPoint, 2);

        arrayOfSurfacePoints[3] = p;

        //create surface
        surfaceArray[i] = Surface(numPointsInSurface, arrayOfSurfacePoints, surfacesColors[i]);
    }

    delete surfacesColors;
    delete arrayOfSurfacePoints;

    return surfaceArray;
}

int Parallelepiped::getNumSurfaces(){
    return numSurfaces;
}
