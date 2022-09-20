cmake_minimum_required(VERSION 3.22.1)

#include(CTest)
#enable_testing()

project(KG_kurs)

#set(SOURCE src/)

add_executable(main src/main.cpp src/Matrix.cpp)

#set(CPACK_PROJECT_NAME ${PROJECT_NAME})
#set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
#include(CPack)

target_link_libraries(main SDL2main SDL2) 