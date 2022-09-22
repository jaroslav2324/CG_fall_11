#pragma once

#include "Point.h"

/*equation plane defined py 3 points*/
class EquationPlane{

public:
    //only 3 points
    EquationPlane(Point* points3);
    
    double getCoeffA();
    double getCoeffB();
    double getCoeffC();
    double getCoeffD();

    double findX(double y, double z);
    double findY(double x, double z);
    double findZ(double x, double y);

private:

    double coeffA;
    double coeffB;
    double coeffC;
    double coeffD;

    //multiply brackets (x1 + x2)(y1 + y2)
    double multiplyTwoBrackets(double x1, double x2, double y1, double y2);

};
