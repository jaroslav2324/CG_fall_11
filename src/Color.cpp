#include "Color.h"

Color::Color(){
    r = 255;
    g = 255;
    b = 255;
    a = 255;
}

Color::Color(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
}
