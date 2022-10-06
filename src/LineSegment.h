
#include <vector>

// line segment on the screen
class LineSegment {

public:
	LineSegment(int x1, int y1, int x2, int y2);

	void addAllSegmentPointsToVector(std::vector<std::pair<int, int>>& vec);

protected:

	int x1, x2, y1, y2;
};