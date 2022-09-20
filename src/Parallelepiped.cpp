
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
