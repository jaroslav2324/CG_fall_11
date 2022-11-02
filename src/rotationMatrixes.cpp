
#include "rotationMatrixes.h"

Matrix createXRotationMatrix(double rotationValue){

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
    rotationMatrixX.setElm(3, 0, 0); rotationMatrixX.setElm(3, 1, 0); rotationMatrixX.setElm(3, 2, 0); rotationMatrixX.setElm(3, 3, 1);

    return rotationMatrixX;
}

Matrix createYRotationMatrix(double rotationValue){
    
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
    rotationMatrixY.setElm(3, 0, 0); rotationMatrixY.setElm(3, 1, 0); rotationMatrixY.setElm(3, 2, 0); rotationMatrixY.setElm(3, 3, 1);

    return rotationMatrixY;
}

Matrix createZRotationMatrix(double rotationValue){
    
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
    rotationMatrixY.setElm(3, 0, 0); rotationMatrixY.setElm(3, 1, 0); rotationMatrixY.setElm(3, 2, 0); rotationMatrixY.setElm(3, 3, 1);

    return rotationMatrixY;
}
