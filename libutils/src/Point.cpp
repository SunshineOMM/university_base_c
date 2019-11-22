#include <libutils/Point.h>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdio.h>
#include<libutils/io.h>
#include <iostream>
namespace zigzag {
	Point::Point() : _x(0.0), _y(0.0) {}
	Point::Point(double x, double  y) : _x(x), _y(y) {}
	/*Point::~Point() {
		delete _x;
		delete _y;
	}*/
	void Point::setX(double x) {
		_x = x;
	}
	void Point::setY(double y) {
		_y = y;
	}
	double Point::getX() const {
		return _x;
	}
	double Point::getY() const {
		return _y;
	}
	bool operator==(const Point& point1, const Point& point2) {
		if (point1.getX() == point2.getX() && point1.getY() == point2.getY()) return true;
		else return false;
	}
	bool operator!=(const Point& point1, const Point& point2) {
		return !(point1 == point2);
	}
}