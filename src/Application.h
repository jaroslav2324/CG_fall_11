#include <iostream>

#include "SDL.h"

#include "settings.h"
#include "ZBuffer.h"
#include "Parallelepiped.h"
#include "Pyramid.h"

class Application {
public:
	Application();

protected:

	void handleKeys();

	Parallelepiped* par = nullptr;
	Pyramid* pyr = nullptr;
};