#include "Line2D.h"

Line2D::Line2D(double x1, double y1, double x2, double y2) {

	//find coefficients of the line
	coeffA = y1 - y2;
	coeffB = -(x1 - x2);
	coeffC = -(y1 - y2) * x2 + (x1 - x2) * y2;
}

bool Line2D::isPointRightFromLine(double x, double y) {

	double lineX;

	// vertical line
	if (coeffB == 0)
		lineX = - coeffC / coeffA;
	else
		lineX = findX(y);

	if (lineX < x)
		return true;
	return false;
}

// returns MINUS_INF if vertical line
double Line2D::findY(double x) {

	//be carefull with MINUS_INF
	if (coeffB == 0)
		return MINUS_INF;
	else
		return (-coeffA * x - coeffC) / coeffB;
}

// returns MINUS_INF if horizontal line
double Line2D::findX(double y) {

	//be carefull with MINUS_INF
	if (coeffA == 0)
		return MINUS_INF;
	else
		return (-coeffB * y - coeffC) / coeffA;
}