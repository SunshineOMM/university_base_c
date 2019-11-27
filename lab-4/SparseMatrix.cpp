#include"SparseMatrix.h"
#include "CustomRealMatrix.h"
#include <iostream>
#include <map>

SparseMatrix::SparseMatrix() :_data(), _m(0), _n(0) {}
SparseMatrix::SparseMatrix(size_t size) {
	for (int i = 0; i < size; ++i) {
		_data[i] = rand() % 100;
	}
	_m = 0;
	_n = size;
	this->check();
}
SparseMatrix::SparseMatrix(size_t size_m, size_t size_n) {
	for (int i = 0; i < size_m*size_n; ++i) {
		_data[i] = rand() % 100;
	}
	_m = size_m;
	_n = size_n;
	this->check();
}



void SparseMatrix::check() {
	auto tmp = 0;
	auto runner = _data.begin();
	while (runner != _data.end()) {
		if (runner->second == 0) {
			_data.at(tmp) = (rand() % 50) + 1;
			++runner;
			++tmp;
		}
		else	++runner;
	}
}

size_t SparseMatrix::getSize()const  {
	auto realNum = 0;
	if (static_cast<int>(_m) == 0) realNum = static_cast<int>(_n);
	else {
		if (static_cast<int>(_n) == 0) realNum = static_cast<int>(_m);
		else	realNum = static_cast<int>(_n * _m);
	}
	return realNum;
}
size_t SparseMatrix::getSizeM()const  {
	return _m;
}
size_t SparseMatrix::getSizeN()const  {
	return  _n;
}

bool SparseMatrix::equals(CustomRealMatrix& matrix)const  {
	auto p = dynamic_cast<SparseMatrix*>(&matrix);
	if (!p) throw"Ошибка сравнения";
	if (_n == p->getSizeN()) {
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

double& SparseMatrix::at(const size_t ind) {
	return _data.at(ind);
}

void SparseMatrix::print(std::ostream& out)const  {
	auto i = 1;
	auto j = 1;
	out << "Печать SparseMatrix" << std::endl;
	for (auto elem : _data) {


		out << "[" << i << "]" << "[" << j << "]" << "=" << elem.second << std::endl;
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