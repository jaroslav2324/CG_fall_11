#include "ZBuffer.h"

ZBuffer::ZBuffer(){

    screenColorsArray = new Color ** [SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        screenColorsArray[i] = new Color * [SCREEN_WIDTH];
        for (int j = 0; j < SCREEN_WIDTH; j++)
            screenColorsArray[i][j] = new Color;
    }


    zBuffer = new double ** [SCREEN_HEIGHT];
    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        zBuffer[i] = new double * [SCREEN_WIDTH];
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            zBuffer[i][j] = new double;
        }
    }
    clearZBuffer();
}

ZBuffer::~ZBuffer() {

    // free screenColors and zBuffer
    for (int i = 0; i < SCREEN_HEIGHT; i++)
        for (int j = 0; j < SCREEN_WIDTH; j++) {
            delete screenColorsArray[i][j];
            delete zBuffer[i][j];
        }

    for (int i = 0; i < SCREEN_HEIGHT; i++) {
        delete screenColorsArray[i];
        delete zBuffer[i];
    }

    delete screenColorsArray;
    delete zBuffer;

}

void ZBuffer::placeParallelepiped(Parallelepiped* par) {

    Surface** arrayOfParSurfaces = par->createArrayOfSurfaces();
    int numSurfaces = par->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++) 
        placeSurfaceInZBuffer(arrayOfParSurfaces[i]);

    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfParSurfaces[i];
    delete[] arrayOfParSurfaces;
}

void ZBuffer::placePyramid(Pyramid* pyr){

    Surface** arrayOfParSurfaces = pyr->createArrayOfSurfaces();
    int numSurfaces = pyr->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++) 
        placeSurfaceInZBuffer(arrayOfParSurfaces[i]);
    
    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfParSurfaces[i];
    delete[] arrayOfParSurfaces;
}

void ZBuffer::placeSurfaceInZBuffer(Surface* surface){

    SDL_Rect rectAroundSurface = surface->getCoveringSurfaceRect();

    int startRectX = rectAroundSurface.x;
    int startRectY = rectAroundSurface.y;
    int endRectX = rectAroundSurface.x + rectAroundSurface.w;
    int endRectY = rectAroundSurface.y + rectAroundSurface.h;


    if (surface->isParallelToOZ())
        return;

    // if surface is not in the window on the screen
    if (endRectX < 0 || endRectY < 0 || SCREEN_WIDTH < startRectX || SCREEN_HEIGHT < startRectY)
        return;

    // copy surface to zBuffer

    // get surface Color
    Color surfaceColor = surface->getSurfaceColor();

    std::vector<std::pair<int, int>> pointsVector;

    // create border points

    surface->addBorderLinesPointsToVector(pointsVector);

    // find center
    Point center = surface->getCenter();

    // recursive filling
    recursiveFillVectorOfCoords(surface, pointsVector, center.x, center.y);

    // update zBuffer
    for (auto& point : pointsVector) {

        int x = point.first;
        int y = point.second;

        if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
            continue;

        double zCoord = surface->getZ(x, y);

        if (zCoord > *zBuffer[y][x]) {
            *zBuffer[y][x] = zCoord;
            screenColorsArray[y][x]->r = surfaceColor.r;
            screenColorsArray[y][x]->g = surfaceColor.g;
            screenColorsArray[y][x]->b = surfaceColor.b;
            screenColorsArray[y][x]->a = surfaceColor.a;
        }

    }
}

// clears array of colors and zBuffer
void ZBuffer::clearZBuffer(){

    for(int i = 0; i < SCREEN_HEIGHT; i++)
        for(int j = 0; j < SCREEN_WIDTH; j++){
            screenColorsArray[i][j]->r = 0;
            screenColorsArray[i][j]->g = 0;
            screenColorsArray[i][j]->b = 0;
            screenColorsArray[i][j]->a = 255;
            *zBuffer[i][j] = MINUS_INF;
        }

}

void ZBuffer::renderBuffer(SDL_Renderer* renderer, Parallelepiped* par, Pyramid* pyr, Point* lightSource){

    clearZBuffer();

    placeParallelepiped(par);
    placePyramid(pyr);

    placeShades(renderer, par, pyr, lightSource);

    for (int y = 0; y < SCREEN_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++){
            Color* color = screenColorsArray[y][x];
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            SDL_RenderDrawPoint(renderer, x, y);
        }

    SDL_RenderPresent(renderer);
}

void ZBuffer::placeShades(SDL_Renderer* renderer, Parallelepiped* par, Pyramid* pyr, Point* lightSource){

    Color shadowColor(60, 60, 60, 255);

    // create shadows for parallelepiped
    Surface** arrayOfParSurfaces = par->createArrayOfSurfaces();
    int numSurfaces = par->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++) {
        
        int numVertexesInSurface = arrayOfParSurfaces[i]->getNumPoints();
        Point* shadowSurfacePointsArray = new Point[numVertexesInSurface];
        // for every surface in parallelepiped create shadow surface

        for (int j = 0; j < numVertexesInSurface; j++) {

            double zs = 0; // z shadow; on plane z = 0

            // coords of vertex of parallelepiped surface
            Point vertex = arrayOfParSurfaces[i]->getPoint(j);
            double xv = vertex.x;
            double yv = vertex.y;
            double zv = vertex.z;

            double xs = (-(zv / (lightSource->z - zv)) * (lightSource->x - xv)) + xv; // x shadow
            double ys = (-(zv / (lightSource->z - zv)) * (lightSource->y - yv)) + yv; // y shadow

            shadowSurfacePointsArray[j] = Point(xs, ys, zs);
        }

        Surface* shadowSurface = new Surface(numVertexesInSurface, shadowSurfacePointsArray, shadowColor);
        placeSurfaceInZBuffer(shadowSurface);

        delete shadowSurface;
        delete[] shadowSurfacePointsArray;
    }

    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfParSurfaces[i];
    delete[] arrayOfParSurfaces;


    // create shadows for pyramid
    Surface** arrayOfPyrSurfaces = pyr->createArrayOfSurfaces();
    numSurfaces = pyr->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++) {

        int numVertexesInSurface = arrayOfPyrSurfaces[i]->getNumPoints();
        Point* shadowSurfacePointsArray = new Point[numVertexesInSurface];
        // for every surface in pyramid create shadow surface

        for (int j = 0; j < numVertexesInSurface; j++) {

            double zs = 0; // z shadow; on plane z = 0

            // coords of vertex of pyramid surface
            Point vertex = arrayOfPyrSurfaces[i]->getPoint(j);
            double xv = vertex.x;
            double yv = vertex.y;
            double zv = vertex.z;

            double xs = (-(zv / (lightSource->z - zv)) * (lightSource->x - xv)) + xv; // x shadow
            double ys = (-(zv / (lightSource->z - zv)) * (lightSource->y - yv)) + yv; // y shadow

            shadowSurfacePointsArray[j] = Point(xs, ys, zs);
        }

        Surface* shadowSurface = new Surface(numVertexesInSurface, shadowSurfacePointsArray, shadowColor);
        placeSurfaceInZBuffer(shadowSurface);

        delete shadowSurface;
        delete[] shadowSurfacePointsArray;
    }

    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfPyrSurfaces[i];
    delete[] arrayOfPyrSurfaces;
}

void ZBuffer::recursiveFillVectorOfCoords(Surface* surface, std::vector<std::pair<int, int>>& pointsVector, int startX, int startY) {

    if (! surface->isPointInsideSurface(startX, startY))
        return;

    pointsVector.push_back(std::make_pair(startX, startY));

    if (! (std::find(pointsVector.begin(), pointsVector.end(), std::make_pair(startX, startY + 1)) != pointsVector.end()))
        recursiveFillVectorOfCoords(surface, pointsVector, startX, startY + 1);

    if (! (std::find(pointsVector.begin(), pointsVector.end(), std::make_pair(startX, startY - 1)) != pointsVector.end()))
        recursiveFillVectorOfCoords(surface, pointsVector, startX, startY - 1);

    if (! (std::find(pointsVector.begin(), pointsVector.end(), std::make_pair(startX + 1, startY)) != pointsVector.end()))
        recursiveFillVectorOfCoords(surface, pointsVector, startX + 1, startY);

    if (! (std::find(pointsVector.begin(), pointsVector.end(), std::make_pair(startX - 1, startY)) != pointsVector.end()))
        recursiveFillVectorOfCoords(surface, pointsVector, startX - 1, startY);

    return;
}
