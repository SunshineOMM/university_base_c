#define _CRT_SECURE_NO_WARNINGS
#include <cmath>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cerrno>
#include<libutils/io.h>
#include <libutils/Lines.h>
#include <libutils/Point.h>


namespace zigzag {

	Straight::Straight() : _a(0), _b(0), _c(0) {}
	Straight::Straight(double a, double b, double c) : _a(a), _b(b), _c(c) {}
	Straight::Straight(const Point& point1, const Point& point2) {
		this->defOfLineTwoPoints(point1, point2);
	}

	void Straight::defOfLineTwoPoints(const Point& point1, const Point& point2) {
		const auto a1 = point2.getY() - point1.getY();
		setA(a1);
		const auto b1 = point2.getX() - point1.getX();
		setB(b1);
		const auto c1 = -(point1.getX()*point2.getY() - point2.getX()*point1.getY());
		setC(c1);
	}
	void Straight::setA(double a) {
		_a = a;
	}
	void Straight::setB(double b) {
		_b = b;
	}
	void Straight::setC(double c) {
		_c = c;
	}
	double Straight::getA() const {
		return _a;
	}
	double Straight::getB() const {
		return _b;
	}
	double Straight::getC() const {
		return _c;
	}
	double Straight::getLineSlope() const
	{
		if (_b) return _a / _b;
		else return 0;
	}
	double Straight::getCoefB() const
	{
		if (_b == 0) return 0;
		else return (_c) / _b;
	}
	Point Straight::LineIntersection(const Straight& line) {
		if (getLineSlope() == line.getLineSlope()) {
			return Point(NAN, NAN);
		}

		return Point(-(line.getCoefB() - getCoefB()) / (getLineSlope() - line.getLineSlope()), -(getLineSlope()*(line.getCoefB() - getCoefB()) / (getLineSlope() - line.getLineSlope()) + getCoefB()));//
	}
}