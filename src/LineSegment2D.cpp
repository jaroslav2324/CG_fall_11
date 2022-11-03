#include "LineSegment2D.h"

LineSegment2D::LineSegment2D(int x1, int y1, int x2, int y2) {
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;
}

void LineSegment2D::addAllSegmentPointsToVector(std::vector<std::pair<int, int>>& vec) {

    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY;
    vec.push_back(std::make_pair(x2, y2));
    while (x1 != x2 || y1 != y2)
    {
        vec.push_back(std::make_pair(x1, y1));
        int error2 = error * 2;
        if (error2 > -deltaY)
        {
            error -= deltaY;
            x1 += signX;
        }
        if (error2 < deltaX)
        {
            error += deltaX;
            y1 += signY;
        }
    }
}