#pragma once
namespace C {
	struct point {
		double _x;
		double _y;
	};
		void setX(point& p, const double x);
		void setY(point& p, const double y);
		double getX(const point& p);
		double getY(const point& p);
		void pointDefinition(point& p);
	
		struct straight {
			double _a;
			double _b;
			double _c;
		};
		void defOfLineTwoPoints(straight& s, const point& a, const point& b);
		void setA(straight& s, const double a);
		void setB(straight& s, const double b);
		void setC(straight& s, const double c);
		double getA(const straight& s);
		double getB(const straight& s);
		double getC(const straight& s);
		double LineSlope(const straight& s);
		double getCoefB(const straight& s);
		double angleBWLineAndAbsc(const straight& s);
		double angleBWLineAndLine(const straight& s, const straight& Line2);
		int oppositePointsFromTheLine(const straight& s, const point& first, const point& second);
		void LineIntersection(const straight& s, const straight& line, point& p1);
	
	void pointLineAssignment(straight& s1, point& p1, point& p2);
	void directDefinitionByTheFormula(straight& s1);
	void directTask(straight& s1, point& p1, point& p2);
}