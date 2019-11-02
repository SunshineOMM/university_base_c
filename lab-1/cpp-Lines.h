#pragma once
#include "point.h"
namespace Cpp {
	
	struct straight {
	private:
		double _a;
		double _b;
		double _c;
	public:
		straight();
		straight(double a, double b, double c);
		straight(const point& a, const point& b);

		void defOfLineTwoPoints(const point& a, const point& b);
		void setA(double a);
		void setB(double b);
		void setC(double c);
		double getA()const;
		double getB()const;
		double getC()const;
		double LineSlope()const;
		double getCoefB()const;
		double angleBWLineAndAbsc()const;
		static double angleBWLineAndAbsc(const straight& Line);
		double angleBWLineAndLine(const straight& Line2)const;
		int oppositePointsFromTheLine(const point& first, const point& second)const;
		point LineIntersection(const straight& line);
	};
	void pointLineAssignment(straight& s1, point& p1, point& p2);
	void directDefinitionByTheFormula(straight& s1);
	void directTask(straight& s1, point& p1, point& p2);
}