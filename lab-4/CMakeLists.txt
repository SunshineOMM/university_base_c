cmake_minimum_required(VERSION 3.5)
add_executable(lab-4 main.cpp CustomRealMatrix.h SparseMatrix.cpp SparseMatrix.h BufferedMatrix.cpp BufferedMatrix.h )
target_link_libraries(lab-4 utils)
