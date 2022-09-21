#include "ZBuffer.h"

ZBuffer::ZBuffer(){

}

//TODO place parallelepiped
//TODO place Pyramid

// clears array of colors and zBuffer
void ZBuffer::clearZBuffer(){

    for(int i = 0; i < SCREEN_HEIGHT; i++)
        for(int j = 0; j < SCREEN_WIDTH; j++){
            screenColorsArray[i][j] = Color(0, 0, 0, 255);
            zBuffer[i][j] = MINUS_INFINITY;
        }

}