#pragma once

struct Point{
    Point() {
        x = 0;
        y = 0;
        z = 0;
    }
    Point(double x, double y, double z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
    double x;
    double y;
    double z;
};
