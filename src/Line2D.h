#include "settings.h"

// geometrical line
class Line2D {

public:
	Line2D(double x1, double y1, double x2, double y2);

	bool isPointRightFromLine(double x, double y);

	double findY(double x);
	double findX(double y);

protected:
	double coeffA = 0;
	double coeffB = 0;
	double coeffC = 0;
};