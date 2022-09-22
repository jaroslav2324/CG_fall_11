#include "Surface.h"

Surface::Surface(int numPoints, Point* array, Color color){

    Surface::numPoints = numPoints;
    Surface::color = color;

    pointsArray = new Point[numPoints];
    for (int i = 0; i < numPoints; i++)
        pointsArray[i] = array[i];

    equationPlane = new EquationPlane(pointsArray); 

}

Surface::Surface(){

    numPoints = 0;
    color = Color(255, 255, 255, 255);
    pointsArray = nullptr;
    equationPlane = nullptr;
}

Surface::~Surface(){

    if (pointsArray != nullptr)
        delete pointsArray;

    if (equationPlane != nullptr)
        delete equationPlane;
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


bool Surface::isPointInsideSurface(int x, int y){
/*
int pnpoly(int npol, float * xp, float * yp, float x, float y)
 {
   int c = 0;
   for (int i = 0, j = npol - 1; i < npol; j = i++) 
   {
     if ((((yp[i]<=y) && (y<yp[j])) || ((yp[j]<=y) && (y<yp[i]))) &&
       (x > (xp[j] - xp[i]) * (y - yp[i]) / (yp[j] - yp[i]) + xp[i]))
         c = !c;
   }
   return c;
 }
 */
    //TODO check correctness

 int i1, i2, n, N, S, S1, S2, S3;
bool flag;

 N = numPoints;
 for (n=0; n<N; n++){

    flag = false;
    i1 = n < N-1 ? n + 1 : 0;
    while (flag == false)
    {
        i2 = i1 + 1;
        if (i2 >= N)
            i2 = 0;
        if (i2 == (n < N-1 ? n + 1 : 0))
            break;
        S = abs (pointsArray[i1].x * (pointsArray[i2].y - pointsArray[n ].y) +
                    pointsArray[i2].x * (pointsArray[n ].y - pointsArray[i1].y) +
                    pointsArray[n].x  * (pointsArray[i1].y - pointsArray[i2].y));

        S1 = abs (pointsArray[i1].x * (pointsArray[i2].y - y) +
                    pointsArray[i2].x * (y       - pointsArray[i1].y) +
                    x       * (pointsArray[i1].y - pointsArray[i2].y));

        S2 = abs (pointsArray[n ].x * (pointsArray[i2].y - y) +
                    pointsArray[i2].x * (y       - pointsArray[n ].y) +
                    x       * (pointsArray[n ].y - pointsArray[i2].y));

        S3 = abs (pointsArray[i1].x * (pointsArray[n ].y - y) +
                    pointsArray[n ].x * (y       - pointsArray[i1].y) +
                    x       * (pointsArray[i1].y - pointsArray[n ].y));

        if (S == S1 + S2 + S3)
        {
            flag = true;
            break;
        }
        i1 = i1 + 1;
        if (i1 >= N)
            i1 = 0;
    }
    if (flag == false)
        break;
}
 return flag;

}

Color Surface::getSurfaceColor(){
    return color;
}

double Surface::getX(double y, double z){
    equationPlane->findX(y, z);
}

double Surface::getY(double x, double z){
    equationPlane->findY(x, z);
}

double Surface::getZ(double x, double y){
    equationPlane->findZ(x, y);
}
