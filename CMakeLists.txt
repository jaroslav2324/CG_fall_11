cmake_minimum_required(VERSION 3.22.1)

#include(CTest)
#enable_testing()

project(KG_kurs)

#set(SOURCE src/)

set(SDL2_INCLUDE_DIR "C:/Libs/SDL2-2.0.20/include")
set(SDL2_LIBRARY "C:/Libs/SDL2-2.0.20/lib/x64/SDL2.lib;C:/Libs/SDL2-2.0.20/lib/x64/SDL2main.lib")

include_directories(${SDL2_INCLUDE_DIR})
set(SOURCE_FILES src/main.cpp src/Matrix.cpp src/Color.cpp src/EquationPlane.cpp src/Parallelepiped.cpp src/Pyramid.cpp 
src/rotationMatrixes.cpp src/Surface.cpp src/ZBuffer.cpp src/Line2D.cpp src/LineSegment2D.cpp src/Application.cpp)

add_executable(main ${SOURCE_FILES})
target_link_libraries(main ${SDL2_LIBRARY} )

set_target_properties(main PROPERTIES LINK_FLAGS "/STACK:160000000")

# target_include_directories(main ${SDL2_INCLUDE_DIR})
# target_link_libraries(main ${SDL2_LIBRARY})



#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

#target_link_libraries(main SDL2main SDL2)