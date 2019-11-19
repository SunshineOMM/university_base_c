cmake_minimum_required(VERSION 3.5)

SET(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_library(utils STATIC 
include/libutils/io.h 
src/io.cpp)

add_library(utils1 STATIC 
include/libutils/Lines.h 
src/Lines.cpp)

add_library(utils2 STATIC 
include/libutils/Point.h 
src/Point.cpp)

add_library(utils3 STATIC 
include/libutils/Polyline.h 
src/Polyline.cpp)


target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(utils1 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(utils2 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(utils3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
