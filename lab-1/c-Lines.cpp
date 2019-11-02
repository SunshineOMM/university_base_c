#define _CRT_SECURE_NO_WARNINGS
#include <math.h>
#include <iostream>
#include <cstdio>
#include "c-Lines.h"
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdio.h>
#include<libutils/io.h>

namespace C {
	void setX(point& p,const double x) {
		p._x = x;
	}
	void setY(point& p, const double y) {
		p._y = y;
	}
	double getX(const point& p) {
		return p._x;
	}
	double getY(const point& p) {
		return p._y;
	}
	void pointDefinition(point& p) {
		double x1 = 0;
		double y1 = 0;
		x1 = utils::read_double("Введите значение координаты Х : ", -1000, 1000);
		setX(p,x1);
		y1 = utils::read_double("Введите значение координаты У : ", -1000, 1000);
		setY(p,y1);
	}
	void defOfLineTwoPoints(straight& s,const point& a, const point& b) {
		double a1 = 0; double b1 = 0; double c1 = 0;
		a1 = getY(b) - getY(a);
		setA(s,a1);
		b1 = getX(b) - getX(a);
		setB(s,b1);
		c1 = -(getX(a)*getY(b) - getX(b)*getY(a));
		setC(s,c1);
	}
	void setA(straight& s,const double a) {
		s._a = a;
	}
	void setB(straight& s,const double b) {
		s._b = b;
	}
	void setC(straight& s,const double c) {
		s._c = c;
	}
	double getA(const straight& s) {
		return s._a;
	}
	double getB(const straight& s)  {
		return s._b;
	}
	double getC(const straight& s)  {
		return s._c;
	}
	double LineSlope(const straight& s) 
	{
		if (getB(s)) return getA(s) / getB(s);
		else return 0;
	}
	double getCoefB(const straight& s) 
	{
		if (getB(s) == 0) return 0;
		else return (getC(s)) / getB(s);
	}
	double angleBWLineAndAbsc(const straight& s)  {
		if (LineSlope(s) != 0) return (LineSlope(s) >= 0 ? 57.2956*atan(LineSlope(s)) : 57.2956 * (90 - atan(LineSlope(s))));
		else {
			if ((LineSlope(s) == 0) && (s._a != 0))return 90.00;
			else return 0;
		}
	}
	double angleBWLineAndLine(const straight& s,const straight& Line2)  {
		if (LineSlope(s) == LineSlope(Line2))return 0;
		else {

			if (LineSlope(s) == -1 / LineSlope(Line2))return 90.00;
			else return 57.2956*atan(tan((LineSlope(Line2) - LineSlope(s)) / (1 + LineSlope(s)*LineSlope(Line2))));
		}

	}
	int oppositePointsFromTheLine(const straight& s,const point& first, const point& second)  {
		if ((getA(s)*getX(first) + getB(s)*getY(first) + getC(s))*(getA(s)*getX(second) + getB(s)*getY(second) + getC(s)) > 0) return 1;
		if ((getA(s)*getX(first) + getB(s)*getY(first) + getC(s))*(getA(s)*getX(second) + getB(s)*getY(second) + getC(s)) < 0) return 0;
		if ((getA(s)*getX(first) + getB(s)*getY(first) + getC(s) == 0) && (getA(s)*getX(second) + getB(s)*getY(second) + getC(s) == 0)) return 4;
		if ((getA(s)*getX(first) + getB(s)*getY(first) + getC(s) == 0) || (getA(s)*getX(second) + getB(s)*getY(second) + getC(s) == 0)) return 3;
		else return 5;
	}
	void LineIntersection(const straight& s,const straight& line, point& p1) {
		if (LineSlope(s) == LineSlope(line)) {
			setX(p1,NAN);
			setY(p1,NAN);
		}
		double x = (getCoefB(line) - getCoefB(s)) / (LineSlope(s) - LineSlope(line));
		setX(p1,x);
		setY(p1,(LineSlope(s)*x + getCoefB(s)));
	}
	void pointLineAssignment(straight& s1, point& p1, point& p2) {

		printf("Введите значение координат первой точки: \n");
		pointDefinition(p1);
		printf("Введите значение координат  второй точки: \n");
		pointDefinition(p2);
		defOfLineTwoPoints(s1,p1, p2);
	}
	void directDefinitionByTheFormula(straight& s1) {
		double a = 0;
		a = utils::read_double("Для задания прямой используется её общая формула:Ax+By+C=0\n\t Введите значение A: \n", -1000, 1000);
		setA(s1,a);
		double b = 0;
		b = utils::read_double("\tВведите значение B: \n", -1000, 1000);
		setB(s1,b);
		double c = 0;
		c = utils::read_double("\tВведите значение C: \n", -1000, 1000);
		setC(s1,c);
	}
	void directTask(straight& s1, point& p1, point& p2) {

		int choice1 = 3;
		while (choice1 == 3) {
			choice1 = utils::read_int("Выберите способ задания прямой:\n\t1) Через общую формулу\t2) Через 2 точки\n", 0, 3);
			if (choice1 == 1) {

				directDefinitionByTheFormula(s1);

			}
			else {
				if (choice1 == 2) {
					pointLineAssignment(s1, p1, p2);
				}
				else {
					printf("Ошибка, повторите ввод\n");
					choice1 = 3;
				}
			}
		}
	}
}