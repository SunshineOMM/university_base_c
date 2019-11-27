#include "BufferedMatrix.h"
#include "CustomRealMatrix.h"
#include <iostream>
#include <vector>


BufferedMatrix::BufferedMatrix() :_data(), _m(0), _n(0) {}

BufferedMatrix::BufferedMatrix(size_t size) :_data(), _m(0), _n(size) {
	for (int i = 0; i < size; ++i) {
		_data[i] = rand() % 100;
	}
}
BufferedMatrix::BufferedMatrix(size_t size_m, size_t size_n) :_data(), _m(size_m), _n(size_n) {
	for (int i = 0; i < size_m*size_n; ++i) {
		_data[i] = rand() % 100;
	}
}

size_t BufferedMatrix::getSize()const  {
	auto realNum = 0;
	if (static_cast<int>(_m) == 0) realNum = static_cast<int>(_n);
	else {
		if (static_cast<int>(_n) == 0) realNum = static_cast<int>(_m);
		else	realNum = static_cast<int>(_n * _m);
	}
	return realNum;
}

size_t BufferedMatrix::getSizeM()const  {
	return _m;
}

size_t BufferedMatrix::getSizeN()const  {
	return  _n;
}

bool BufferedMatrix::equals(CustomRealMatrix& matrix)const  {
	auto p = dynamic_cast<BufferedMatrix*>(&matrix);
	if (_n == p->getSizeN()) {
		if (!p) throw"Ошибка сравнения";
		if (_m == p->getSizeM()) {
			auto realNum = getSize();
			for (int i = 0; i < realNum; ++i) {
				if (_data.at(i) != matrix.at(i)) return false;
			}
			return true;
		}
	}
	return false;
}

double& BufferedMatrix::at(const size_t ind) {
	return _data.at(ind);
}

void BufferedMatrix::print(std::ostream& out)const  {
	auto i = 1;
	auto j = 1;
	out << "Печать BufferedMatrix" << std::endl;
	for (auto elem : _data) {


		out << "[" << i << "]" << "[" << j << "]" << "=" << elem << std::endl;
		if (j == _n) {
			++i;
			j = 1;
			std::cout << std::endl;
		}
		else {
			++j;
		}
	}
}