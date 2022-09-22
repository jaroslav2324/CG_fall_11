#include "ZBuffer.h"

ZBuffer::ZBuffer(){

}

//TODO place parallelepiped
void ZBuffer::placeParallelepiped(Parallelepiped* par){
    
    Surface* arrayOfParSurfaces = par->createArrayOfSurfaces();
    int numSurfaces = par->getNumSurfaces();

    for (int i = 0; i < numSurfaces; i++){

        SDL_Rect rectAroundSurface = arrayOfParSurfaces[i].getCoveringSurfaceRect();

        int startRectX = rectAroundSurface.x;
        int startRectY = rectAroundSurface.y;
        int endRectX = rectAroundSurface.x + rectAroundSurface.w;
        int endRectY = rectAroundSurface.y + rectAroundSurface.h;

        // if surface is not in the window on the screen
        if (endRectX < 0 || endRectY < 0 || SCREEN_WIDTH < startRectX || SCREEN_HEIGHT < startRectY)
            continue;

        // copy surface to zBuffer

        //TODO change comment
        // find starting positions to change part of zBuffer instead of replacing all values in zBuffer
        int startX, startY;
        
        if (startRectX < 0)
            startRectX = 0;

        if (startRectY < 0)
            startRectY = 0;

        if (SCREEN_WIDTH < endRectX)
            endRectX = SCREEN_WIDTH;

        if (SCREEN_HEIGHT < endRectY)
            endRectY = SCREEN_HEIGHT;

        // get surface Color
        Color surfaceColor = arrayOfParSurfaces[i].getSurfaceColor();

        

        // fill surface with color
        
    }



    delete arrayOfParSurfaces;
}

//TODO place Pyramid
void ZBuffer::placePyramid(Pyramid* pyr){

}

// clears array of colors and zBuffer
void ZBuffer::clearZBuffer(){

    for(int i = 0; i < SCREEN_HEIGHT; i++)
        for(int j = 0; j < SCREEN_WIDTH; j++){
            screenColorsArray[i][j] = Color(0, 0, 0, 255);
            zBuffer[i][j] = MINUS_INFINITY;
        }

}