
#include "point.h"
#include <math.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdio.h>
#include<libutils/io.h>
namespace Cpp {
	point::point() : _x(0.0), _y(0.0) {}
	point::point(double x, double  y) : _x(x), _y(y) {}
	void point::setX(double x) {
		_x = x;
	}
	void point::setY(double y) {
		_y = y;
	}
	double point::getX() const {
		return _x;
	}
	double point::getY() const {
		return _y;
	}
	void point::pointDefinition() {
		double x1 = 0;
		double y1 = 0;
		x1 = utils::read_double("Введите значение координату Х : ", -1000, 1000);
		setX(x1);
		y1 = utils::read_double("Введите значение координату У : ", -1000, 1000);
		setY(y1);
	}
}