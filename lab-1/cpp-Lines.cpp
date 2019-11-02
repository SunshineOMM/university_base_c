#define _CRT_SECURE_NO_WARNINGS
#include "point.h"
#include <cmath>
#include <iostream>
#include <cstdio>
#include "cpp-Lines.h"
#include <cstring>
#include <cerrno>
#include <cstdio>
#include<libutils/io.h>


namespace Cpp {
	
	straight::straight() : _a(0), _b(0), _c(0) {}
	straight::straight(double a, double b, double c) : _a(a), _b(b), _c(c) {}
	straight::straight(const point& a, const point& b) {
		double a1 = 0; double b1 = 0; double c1 = 0;
		a1 = b.getY() - a.getY();
		setA(a1);
		b1 = b.getX() - a.getX();
		setB(b1);
		c1 = -(a.getX()*b.getY() - b.getX()*a.getY());
		setC(c1);
	}

	void straight::defOfLineTwoPoints(const point& a, const point& b) {
		double a1 = 0; double b1 = 0; double c1 = 0;
		a1 = b.getY() - a.getY();
		setA(a1);
		b1 = b.getX() - a.getX();
		setB(b1);
		c1 = -(a.getX()*b.getY() - b.getX()*a.getY());
		setC(c1);
	}
	void straight::setA(double a) {
		_a = a;
	}
	void straight::setB(double b) {
		_b = b;
	}
	void straight::setC(double c) {
		_c = c;
	}
	double straight::getA() const {
		return _a;
	}
	double straight::getB() const {
		return _b;
	}
	double straight::getC() const {
		return _c;
	}
	double straight::LineSlope() const
	{
		if (getB()) return getA() / getB();
		else return 0;
	}
	double straight::getCoefB() const//
	{
		if (getB() == 0) return 0;
		else return (getC()) / getB();
	}
	double straight::angleBWLineAndAbsc() const {
		if (LineSlope() != 0) return (LineSlope() >= 0 ? 57.2956*atan(LineSlope()) : 57.2956 * (90 - atan(LineSlope())));
		else {
			if ((LineSlope() == 0) && (getA() != 0))return 90.00;
			else return 0;
		}
	}
	double straight::angleBWLineAndAbsc(const straight & Line)//static
	{
		if (Line.LineSlope() != 0) return (Line.LineSlope() >= 0 ? 57.2956*atan(Line.LineSlope()) : 57.2956 * (90 - atan(Line.LineSlope())));
		else {
			if ((Line.LineSlope() == 0) && (Line.getA() != 0))return 90.00;
			else return 0;
		}
	}
	 
	double straight::angleBWLineAndLine(const straight& Line2) const {
		if (LineSlope() == Line2.LineSlope())return 0;
		else {

			if (LineSlope() == -1 / Line2.LineSlope())return 90.00;
			else return 57.2956*atan(tan((Line2.LineSlope() - LineSlope()) / (1 + LineSlope()*Line2.LineSlope())));
		}

	}
	int straight::oppositePointsFromTheLine(const point& first, const point& second) const {
		if ((getA()*first.getX() + getB()*first.getY() + getC())*(getA()*second.getX() + getB()*second.getY() + getC()) > 0) return 1;
		if ((getA()*first.getX() + getB()*first.getY() + getC())*(getA()*second.getX() + getB()*second.getY() + getC()) < 0) return 0;
		if ((getA()*first.getX() + getB()*first.getY() + getC() == 0) && (getA()*second.getX() + getB()*second.getY() + getC() == 0)) return 4;
		if ((getA()*first.getX() + getB()*first.getY() + getC() == 0) || (getA()*second.getX() + getB()*second.getY() + getC() == 0)) return 3;
		else return 5;
	}
	point straight::LineIntersection(const straight& line) {
		if (LineSlope() == line.LineSlope()) {
			return point(NAN, NAN);
		}
		
		return point(-(line.getCoefB() - getCoefB()) / (LineSlope() - line.LineSlope()), -(LineSlope()*(line.getCoefB() - getCoefB()) / (LineSlope() - line.LineSlope()) + getCoefB()));//
	}
	void pointLineAssignment(straight& s1, point& p1, point& p2) {

		printf("Введите значение координат первой точки: \n");
		p1.pointDefinition();
		printf("Введите значение координат  второй точки: \n");
		p2.pointDefinition();
		s1.defOfLineTwoPoints(p1, p2);
	}
	void directDefinitionByTheFormula(straight& s1) {
		double a = 0;
		a = utils::read_double("Для задания прямой используется её общая формула:Ax+By+C=0\n\t Введите значение A: \n", -10000, 10000);//
		s1.setA(a);
		double b = 0;
		b = utils::read_double("\tВведите значение B: \n", -10000, 10000);//
		s1.setB(b);
		double c = 0;
		c = utils::read_double("\tВведите значение C: \n", -10000, 10000);//
		s1.setC(c);
	}
	void directTask(straight& s1, point& p1, point& p2) {

		int choice = 3;
		while (choice == 3) {
			choice = utils::read_int("Выберите способ задания прямой:\n\t1) Через общую формулу\t2) Через 2 точки\n", 0, 3);
			if (choice == 1) {

				directDefinitionByTheFormula(s1);

			}
			else {
				if (choice == 2) {
					pointLineAssignment(s1, p1, p2);
				}
				else {
					printf("Ошибка, повторите ввод\n");
					choice = 3;
				}
			}
		}
	}
	
}