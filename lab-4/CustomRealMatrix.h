#pragma once
#include <iostream>

class CustomRealMatrix {
public:

	virtual size_t getSize()const = 0;
	virtual size_t getSizeM()const = 0;
	virtual size_t getSizeN()const = 0;

	virtual bool equals(CustomRealMatrix& fun)const = 0;

	virtual double& at(const size_t ind) = 0;

	virtual void print(std::ostream& out)const = 0;
};
