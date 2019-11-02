cmake_minimum_required(VERSION 3.5)
add_executable(lab-2 main.cpp Lines.cpp Lines.h  Point.cpp Point.h Polyline.cpp Polyline.h )
target_link_libraries(lab-2 utils)
