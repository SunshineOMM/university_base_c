#pragma once
#include "CustomRealMatrix.h"
#include <map>
#include <iostream>

class SparseMatrix : public CustomRealMatrix {
	std::map<size_t, double> _data;
	size_t _m;
	size_t _n;
public:
	SparseMatrix();
	SparseMatrix(size_t size);
	SparseMatrix(size_t size_m, size_t size_n);

	

	void check();

	size_t getSize()const override;
	size_t getSizeM()const override;
	size_t getSizeN()const override;

	bool equals(CustomRealMatrix& matrix)const override;

	double& at(const size_t ind);

	void print(std::ostream& out)const override;
};