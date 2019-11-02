#pragma once
#include "Point.h"
#include <iostream>
namespace zigzag {

	struct Straight {
	private:
		double _a;
		double _b;
		double _c;
	public:
		Straight();
		Straight(double a, double b, double c);
		Straight(const Point& point1, const Point& point2);

		void defOfLineTwoPoints(const Point& point1, const Point& point2);
		void setA(double a);
		void setB(double b);
		void setC(double c);
		double getA()const;
		double getB()const;
		double getC()const;
		double getLineSlope()const;
		double getCoefB()const;
		Point LineIntersection(const Straight& line);
	};
}