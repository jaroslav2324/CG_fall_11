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

    for (int i = 0; i < numSurfaces; i++) {

        SDL_Rect rectAroundSurface = arrayOfParSurfaces[i]->getCoveringSurfaceRect();

        int startRectX = rectAroundSurface.x;
        int startRectY = rectAroundSurface.y;
        int endRectX = rectAroundSurface.x + rectAroundSurface.w;
        int endRectY = rectAroundSurface.y + rectAroundSurface.h;

        // if surface is not in the window on the screen
        if (endRectX < 0 || endRectY < 0 || SCREEN_WIDTH < startRectX || SCREEN_HEIGHT < startRectY)
            continue;

        // copy surface to zBuffer

        // get surface Color
        Color surfaceColor = arrayOfParSurfaces[i]->getSurfaceColor();

        std::vector<std::pair<int, int>> pointsVector;

        // create border points

        arrayOfParSurfaces[i]->addBorderLinesPointsToVector(pointsVector);

        // find center
        Point center = arrayOfParSurfaces[i]->getCenter();

        // recursive filling
        recursiveFillVectorOfCoords(arrayOfParSurfaces[i], pointsVector, center.x, center.y);

        // update zBuffer
        for (auto& point : pointsVector) {

            int x = point.first;
            int y = point.second;

            if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
                continue;

            double zCoord = arrayOfParSurfaces[i]->getZ(x, y);

            if (zCoord > *zBuffer[y][x]) {
                *zBuffer[y][x] = zCoord;
                screenColorsArray[y][x]->r = surfaceColor.r;
                screenColorsArray[y][x]->g = surfaceColor.g;
                screenColorsArray[y][x]->b = surfaceColor.b;
                screenColorsArray[y][x]->a = surfaceColor.a;
            }

        }     

    }
    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfParSurfaces[i];
    delete arrayOfParSurfaces;
}

void ZBuffer::placePyramid(Pyramid* pyr){

    Surface** arrayOfParSurfaces = pyr->createArrayOfSurfaces();
    int numSurfaces = pyr->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++) {

        SDL_Rect rectAroundSurface = arrayOfParSurfaces[i]->getCoveringSurfaceRect();

        int startRectX = rectAroundSurface.x;
        int startRectY = rectAroundSurface.y;
        int endRectX = rectAroundSurface.x + rectAroundSurface.w;
        int endRectY = rectAroundSurface.y + rectAroundSurface.h;

        // if surface is not in the window on the screen
        if (endRectX < 0 || endRectY < 0 || SCREEN_WIDTH < startRectX || SCREEN_HEIGHT < startRectY)
            continue;

        // copy surface to zBuffer

        // get surface Color
        Color surfaceColor = arrayOfParSurfaces[i]->getSurfaceColor();

        std::vector<std::pair<int, int>> pointsVector;

        // create border points

        arrayOfParSurfaces[i]->addBorderLinesPointsToVector(pointsVector);

        // find center
        Point center = arrayOfParSurfaces[i]->getCenter();

        // recursive filling
        recursiveFillVectorOfCoords(arrayOfParSurfaces[i], pointsVector, center.x, center.y);

        // update zBuffer
        for (auto& point : pointsVector) {

            int x = point.first;
            int y = point.second;

            if (x < 0 || y < 0 || x >= SCREEN_WIDTH || y >= SCREEN_HEIGHT)
                continue;

            double zCoord = arrayOfParSurfaces[i]->getZ(x, y);

            if (zCoord > *zBuffer[y][x]) {
                *zBuffer[y][x] = zCoord;
                screenColorsArray[y][x]->r = surfaceColor.r;
                screenColorsArray[y][x]->g = surfaceColor.g;
                screenColorsArray[y][x]->b = surfaceColor.b;
                screenColorsArray[y][x]->a = surfaceColor.a;
            }
        }
    }

    for (int i = 0; i < numSurfaces; i++)
        delete arrayOfParSurfaces[i];
    delete arrayOfParSurfaces;
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

void ZBuffer::renderBuffer(SDL_Renderer* renderer, Parallelepiped* par, Pyramid* pyr){

    clearZBuffer();

    placeParallelepiped(par);
    placePyramid(pyr);

    for (int y = 0; y < SCREEN_HEIGHT; y++)
        for (int x = 0; x < SCREEN_WIDTH; x++){
            Color* color = screenColorsArray[y][x];
            SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
            SDL_RenderDrawPoint(renderer, x, y);
        }

    SDL_RenderPresent(renderer);
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
