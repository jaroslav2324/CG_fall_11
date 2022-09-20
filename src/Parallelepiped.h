#include "Point.h"
#include "Matrix.h"


class Parallelepiped{

public:
    Parallelepiped();
    ~Parallelepiped();

    void moveAlongX(double moveDistance);
    void moveAlongY(double moveDistance);
    void moveAlongZ(double moveDistance);

    void rotateAroundX(double rotationAngle);
    void rotateAroundY(double rotationAngle);
    void rotateAroundZ(double rotationAngle);

    // coefficient from basic points coords
    void scale(double scaleCoefficient);

protected:
    Matrix* pointsCoords;
    // basic points coords
    Matrix* basicPointsCoords;

    //TODO 
    Point centerPoint;
    void findCenter();
	void moveToCenterCoords();
	void moveFromCenterCoords();

    Matrix createXRotationMatrix(double rotationValue);
    Matrix createYRotationMatrix(double rotationValue);
    Matrix createZRotationMatrix(double rotationValue);

    void addToPointsCoordsMatrix(int numRow, int numCol, int addValue);
};
