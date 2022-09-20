#include "math.h"

#include "settings.h"
#include "Parallelepiped.h"

Parallelepiped::Parallelepiped(){

    pointsCoords = new Matrix(8, 4);
    basicPointsCoords = new Matrix(8, 4);

    //TODO findCenter
    //TODO set basic coords of parall
}

Parallelepiped::~Parallelepiped(){

    delete pointsCoords;
    delete basicPointsCoords;
}

void Parallelepiped::findCenter(){

    //sum all x from pointsCoords matrix
    double centerX = pointsCoords->getElm(0, 0) + pointsCoords->getElm(1, 0) + pointsCoords->getElm(2, 0) + pointsCoords->getElm(3, 0) +
                     pointsCoords->getElm(4, 0) + pointsCoords->getElm(5, 0) + pointsCoords->getElm(6, 0) + pointsCoords->getElm(7, 0);
    //find centerX
    centerX /= 8;

    //sum all y from pointsCoords matrix
    double centerY = pointsCoords->getElm(0, 1) + pointsCoords->getElm(1, 1) + pointsCoords->getElm(2, 1) + pointsCoords->getElm(3, 1) +
                     pointsCoords->getElm(4, 1) + pointsCoords->getElm(5, 1) + pointsCoords->getElm(6, 1) + pointsCoords->getElm(7, 1);
    //find centerY
    centerY /= 8;

    //sum all z from pointsCoords matrix
    double centerZ = pointsCoords->getElm(0, 2) + pointsCoords->getElm(1, 2) + pointsCoords->getElm(2, 2) + pointsCoords->getElm(3, 2) +
                     pointsCoords->getElm(4, 2) + pointsCoords->getElm(5, 2) + pointsCoords->getElm(6, 2) + pointsCoords->getElm(7, 2);
    //find centerZ
    centerZ /= 8;

    centerPoint.x = centerX;
    centerPoint.y = centerY;
    centerPoint.z = centerZ;
}

void Parallelepiped::moveToCenterCoords(){

    findCenter();

    //shift to center of the world along x axis
    addToPointsCoordsMatrix(0, 0, -centerPoint.x);
    addToPointsCoordsMatrix(0, 1, -centerPoint.x);
    addToPointsCoordsMatrix(0, 2, -centerPoint.x);
    addToPointsCoordsMatrix(0, 3, -centerPoint.x);
    addToPointsCoordsMatrix(0, 4, -centerPoint.x);
    addToPointsCoordsMatrix(0, 5, -centerPoint.x);
    addToPointsCoordsMatrix(0, 6, -centerPoint.x);
    addToPointsCoordsMatrix(0, 7, -centerPoint.x);

    //shift to center of the world along y axis
    addToPointsCoordsMatrix(1, 0, -centerPoint.y);
    addToPointsCoordsMatrix(1, 1, -centerPoint.y);
    addToPointsCoordsMatrix(1, 2, -centerPoint.y);
    addToPointsCoordsMatrix(1, 3, -centerPoint.y);
    addToPointsCoordsMatrix(1, 4, -centerPoint.y);
    addToPointsCoordsMatrix(1, 5, -centerPoint.y);
    addToPointsCoordsMatrix(1, 6, -centerPoint.y);
    addToPointsCoordsMatrix(1, 7, -centerPoint.y);

    //shift to center of the world along z axis
    addToPointsCoordsMatrix(2, 0, -centerPoint.z);
    addToPointsCoordsMatrix(2, 1, -centerPoint.z);
    addToPointsCoordsMatrix(2, 2, -centerPoint.z);
    addToPointsCoordsMatrix(2, 3, -centerPoint.z);
    addToPointsCoordsMatrix(2, 4, -centerPoint.z);
    addToPointsCoordsMatrix(2, 5, -centerPoint.z);
    addToPointsCoordsMatrix(2, 6, -centerPoint.z);
    addToPointsCoordsMatrix(2, 7, -centerPoint.z);
}

// return object to previous coords after moving to center.
// Do not change center coords before completing moving to and from world center
void Parallelepiped::moveFromCenterCoords(){

    //shift back from center of the world along x axis
    addToPointsCoordsMatrix(0, 0, centerPoint.x);
    addToPointsCoordsMatrix(0, 1, centerPoint.x);
    addToPointsCoordsMatrix(0, 2, centerPoint.x);
    addToPointsCoordsMatrix(0, 3, centerPoint.x);
    addToPointsCoordsMatrix(0, 4, centerPoint.x);
    addToPointsCoordsMatrix(0, 5, centerPoint.x);
    addToPointsCoordsMatrix(0, 6, centerPoint.x);
    addToPointsCoordsMatrix(0, 7, centerPoint.x);

    //shift back from center of the world along y axis
    addToPointsCoordsMatrix(1, 0, centerPoint.y);
    addToPointsCoordsMatrix(1, 1, centerPoint.y);
    addToPointsCoordsMatrix(1, 2, centerPoint.y);
    addToPointsCoordsMatrix(1, 3, centerPoint.y);
    addToPointsCoordsMatrix(1, 4, centerPoint.y);
    addToPointsCoordsMatrix(1, 5, centerPoint.y);
    addToPointsCoordsMatrix(1, 6, centerPoint.y);
    addToPointsCoordsMatrix(1, 7, centerPoint.y);

    //shift back from center of the world along z axis
    addToPointsCoordsMatrix(2, 0, centerPoint.z);
    addToPointsCoordsMatrix(2, 1, centerPoint.z);
    addToPointsCoordsMatrix(2, 2, centerPoint.z);
    addToPointsCoordsMatrix(2, 3, centerPoint.z);
    addToPointsCoordsMatrix(2, 4, centerPoint.z);
    addToPointsCoordsMatrix(2, 5, centerPoint.z);
    addToPointsCoordsMatrix(2, 6, centerPoint.z);
    addToPointsCoordsMatrix(2, 7, centerPoint.z);
}

void Parallelepiped::addToPointsCoordsMatrix(int numRow, int numCol, int addValue){

    //TODO check numRow, numCol

    double coord;
    coord = pointsCoords->getElm(numRow, numCol) + addValue;
    pointsCoords->setElm(numRow, numCol, coord);
}

void Parallelepiped::moveAlongX(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    addToPointsCoordsMatrix(0, 0, moveDistance);
    addToPointsCoordsMatrix(1, 0, moveDistance);
    addToPointsCoordsMatrix(2, 0, moveDistance);
    addToPointsCoordsMatrix(3, 0, moveDistance);
    addToPointsCoordsMatrix(4, 0, moveDistance);
    addToPointsCoordsMatrix(5, 0, moveDistance);
    addToPointsCoordsMatrix(6, 0, moveDistance);
    addToPointsCoordsMatrix(7, 0, moveDistance);
}

void Parallelepiped::moveAlongY(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    addToPointsCoordsMatrix(0, 1, moveDistance);
    addToPointsCoordsMatrix(1, 1, moveDistance);
    addToPointsCoordsMatrix(2, 1, moveDistance);
    addToPointsCoordsMatrix(3, 1, moveDistance);
    addToPointsCoordsMatrix(4, 1, moveDistance);
    addToPointsCoordsMatrix(5, 1, moveDistance);
    addToPointsCoordsMatrix(6, 1, moveDistance);
    addToPointsCoordsMatrix(7, 1, moveDistance);
}

void Parallelepiped::moveAlongZ(double moveDistance){

    //get previous value of coord, sum with moveDistance, set new value of coord.
    addToPointsCoordsMatrix(0, 2, moveDistance);
    addToPointsCoordsMatrix(1, 2, moveDistance);
    addToPointsCoordsMatrix(2, 2, moveDistance);
    addToPointsCoordsMatrix(3, 2, moveDistance);
    addToPointsCoordsMatrix(4, 2, moveDistance);
    addToPointsCoordsMatrix(5, 2, moveDistance);
    addToPointsCoordsMatrix(6, 2, moveDistance);
    addToPointsCoordsMatrix(7, 2, moveDistance);
}

Matrix Parallelepiped::createXRotationMatrix(double rotationValue){

    Matrix rotationMatrixX(4, 4);

    //TODO refactor add matrix = array

    // first row
    rotationMatrixX.setElm(0, 0, 1); rotationMatrixX.setElm(0, 1, 0); rotationMatrixX.setElm(0, 2, 0); rotationMatrixX.setElm(0, 3, 0);
    // second row 
    rotationMatrixX.setElm(1, 0, 0); rotationMatrixX.setElm(1, 1, cos(rotationValue)); rotationMatrixX.setElm(1, 2, sin(rotationValue));
    rotationMatrixX.setElm(1, 3, 0);
    // third row
    rotationMatrixX.setElm(2, 0, 0); rotationMatrixX.setElm(2, 1, -sin(rotationValue)); rotationMatrixX.setElm(2, 2, cos(rotationValue));
    rotationMatrixX.setElm(2, 3, 0);
    // fourth row
    rotationMatrixX.setElm(0, 0, 0); rotationMatrixX.setElm(0, 1, 0); rotationMatrixX.setElm(0, 2, 0); rotationMatrixX.setElm(0, 3, 1);

    return rotationMatrixX;
}

Matrix Parallelepiped::createYRotationMatrix(double rotationValue){
    
    Matrix rotationMatrixY(4, 4);

    //TODO refactor

    // first row
    rotationMatrixY.setElm(0, 0, cos(rotationValue)); rotationMatrixY.setElm(0, 1, 0); rotationMatrixY.setElm(0, 2, sin(rotationValue));
    rotationMatrixY.setElm(0, 3, 0);
    // second row 
    rotationMatrixY.setElm(1, 0, 0); rotationMatrixY.setElm(1, 1, 1); rotationMatrixY.setElm(1, 2, 0); rotationMatrixY.setElm(1, 3, 0);
    // third row
    rotationMatrixY.setElm(2, 0, -sin(rotationValue)); rotationMatrixY.setElm(2, 1, 0); rotationMatrixY.setElm(2, 2, cos(rotationValue));
    rotationMatrixY.setElm(2, 3, 0);
    // fourth row
    rotationMatrixY.setElm(0, 0, 0); rotationMatrixY.setElm(0, 1, 0); rotationMatrixY.setElm(0, 2, 0); rotationMatrixY.setElm(0, 3, 1);

    return rotationMatrixY;
}

Matrix Parallelepiped::createZRotationMatrix(double rotationValue){
    
    Matrix rotationMatrixY(4, 4);

    //TODO refactor

    // first row
    rotationMatrixY.setElm(0, 0, cos(rotationValue)); rotationMatrixY.setElm(0, 1, sin(rotationValue)); rotationMatrixY.setElm(0, 2, 0);
    rotationMatrixY.setElm(0, 3, 0);
    // second row 
    rotationMatrixY.setElm(1, 0, -sin(rotationValue)); rotationMatrixY.setElm(1, 1, cos(rotationValue)); rotationMatrixY.setElm(1, 2, 0); 
    rotationMatrixY.setElm(1, 3, 0);
    // third row
    rotationMatrixY.setElm(2, 0, 0); rotationMatrixY.setElm(2, 1, 0); rotationMatrixY.setElm(2, 2, 1); rotationMatrixY.setElm(2, 3, 0);
    // fourth row
    rotationMatrixY.setElm(0, 0, 0); rotationMatrixY.setElm(0, 1, 0); rotationMatrixY.setElm(0, 2, 0); rotationMatrixY.setElm(0, 3, 1);

    return rotationMatrixY;
}

void Parallelepiped::rotateAroundX(double rotationValue){

    moveToCenterCoords();
	
    Matrix rotationMatrix = createXRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Parallelepiped::rotateAroundY(double rotationValue){
 
    moveToCenterCoords();
	
    Matrix rotationMatrix = createYRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}

void Parallelepiped::rotateAroundZ(double rotationValue){
    
    moveToCenterCoords();
	
    Matrix rotationMatrix = createZRotationMatrix(rotationValue);

    *pointsCoords = *pointsCoords * rotationMatrix;

	moveFromCenterCoords();
}


void Parallelepiped::scale(double scaleCoefficient){
    //TODO
}
