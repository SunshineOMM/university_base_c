#pragma once
#include "CustomRealMatrix.h"
#include <vector>
#include <iostream>

class BufferedMatrix : public CustomRealMatrix {
	std::vector<double> _data;
	size_t _m;
	size_t _n;
public:
	 BufferedMatrix();
	 BufferedMatrix(size_t size);
	 BufferedMatrix(size_t size_m, size_t size_n);

	 size_t getSize()const override;
	 size_t getSizeM()const override;
	 size_t getSizeN()const override;

	 bool equals(CustomRealMatrix& matrix)const override;

	 double& at(const size_t ind);

	 void print(std::ostream& out)const override;
};