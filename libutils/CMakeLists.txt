cmake_minimum_required(VERSION 3.5)

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(utils STATIC 
include/libutils/io.h 
src/io.cpp
include/libutils/Lines.h 
src/Lines.cpp
include/libutils/Point.h 
src/Point.cpp
include/libutils/Polyline.h 
src/Polyline.cpp)



target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

