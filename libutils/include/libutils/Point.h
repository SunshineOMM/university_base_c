#pragma once
#include <iostream>


namespace zigzag {

	class Point {
		double _x;
		double _y;
	public:
		Point();
		Point(double x, double  y);
		//~Point();

		void setX(double x);
		void setY(double y);
		double getX()const;
		double getY()const;
	};
	bool operator==(const Point& point1, const Point& point2);
	bool operator!=(const Point& point1, const Point& point2);
}