#include "EquationPlane.h"

EquationPlane::EquationPlane(Point* points3){

    Point p1 = points3[0];
    Point p2 = points3[1];
    Point p3 = points3[2];

    double x1 = p1.x, y1 = p1.y, z1 = p1.z;
    double x2 = p2.x, y2 = p2.y, z2 = p2.z;
    double x3 = p3.x, y3 = p3.y, z3 = p3.z;

    // to find equation of the plane use triangle rule for matrix determinant 3x3

    // first of six components of matrix determinant (x - x1)(y2 - y1)(z3 - z1)
    // second of six components of matrix determinant (y - y1)(z2 - z1)(x3 - x1)
    // third of six components of matrix determinant (z - z1)(x2 - x1)(y3 - y1)
    // fourth of six components of matrix determinant -(x - x1)(z2 - z1)(y3 - y1)
    // fifth of six components of matrix determinant -(y - y1)(x2 - x1)(z3 - z1)
    // sixth of six components of matrix determinant -(z - z1)(y2 - y1)(x3 - x1)

    // therefore
    // coeffA before x is equal to (y2 - y1)(z3 - z1) - (z2 - z1)(y3 - y1)
    // coeffB before y is equal to (z2 - z1)(x3 - x1) - (x2 - x1)(z3 - z1)
    // coeffC before z is equal to (x2 - x1)(y3 - y1) - (y2 - y1)(x3 - x1)
    // coeffD is equal to - x1(y2 - y1)(z3 - z1) - y1(z2 - z1)(x3 - x1) - z1(x2 - x1)(y3 - y1) 
    //                    + x1(z2 - z1)(y3 - y1) + y1(x2 - x1)(z3 - z1) + z1(y2 - y1)(x3 - x1)

    coeffA = multiplyTwoBrackets(y2, -y1, z3, -z1) - multiplyTwoBrackets(z2, -z1, y3, -y1);
    coeffB = multiplyTwoBrackets(z2, -z1, x3, -x1) - multiplyTwoBrackets(x2, -x1, z3, -z1);
    coeffC = multiplyTwoBrackets(x2, -x1, y3, -y1) - multiplyTwoBrackets(y2, -y1, x3, -x1);

    coeffD = - x1 * multiplyTwoBrackets(y2, -y1, z3, -z1) - y1 * multiplyTwoBrackets(z2, -z1, x3, -x1) - z1 * multiplyTwoBrackets(x2, -x1, y3, -y1) 
             + x1 * multiplyTwoBrackets(z2, -z1, y3, -y1) + y1 * multiplyTwoBrackets(x2, -x1, z3, -z1) + z1 * multiplyTwoBrackets(y2, -y1, x3, -x1); 
}

double EquationPlane::getCoeffA(){
    return coeffA;
}

double EquationPlane::getCoeffB(){
    return coeffB;
}

double EquationPlane::getCoeffC(){
    return coeffC;
}

double EquationPlane::getCoeffD(){
    return coeffD;
}

double EquationPlane::multiplyTwoBrackets(double x1, double x2, double y1, double y2){
    return x1 * y1 + x1 * y2 + x2 * y1 + x2 * y2;
}

double EquationPlane::findX(double y, double z){
    double x = - ((coeffB * y + coeffC * z + coeffD) / coeffA);
    return x;
}

double EquationPlane::findY(double x, double z){
    double y = - ((coeffA * x + coeffC * z + coeffD) / coeffB);
    return y;
}

double EquationPlane::findZ(double x, double y){
    double z = - ((coeffA * x + coeffB * y + coeffD) / coeffB);
    return z;
}
