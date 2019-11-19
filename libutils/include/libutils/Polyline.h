#pragma once
#include <libutils/Point.h>
#include <iostream>
namespace zigzag {
	class Polyline {
		Point* _head;
		int _number;
		mutable double _lenghtCache;
		void Polyline::resetCache()const;

	public:
		Polyline();
		Polyline(int num);
		~Polyline();
		Polyline& operator =(const Polyline& line);
		Polyline(const Polyline& line);
		Polyline(Polyline&& tLine)noexcept;
		Polyline& operator=(Polyline&& tLine)noexcept;

		double getCache()const;
		int getNumber()const;
		Point& operator[](int ind);
		const Point& operator[](int ind)const;
		void insertByIndex(int ind, const Point& point);
		void deletByIndex(int ind);
		bool selfIntersectionDefinition()const;
		double calculateLenghtLine()const;

	};
	bool operator==(const Polyline& line1, const Polyline& line2);
	bool operator!=(const Polyline& line1, const Polyline& line2);
	Polyline& operator+=(Polyline& line1, const Polyline& line2);
	Polyline& operator+=(Polyline& line, const Point& point);
	Polyline operator+(const Polyline& line1, const Polyline& line2);
	Polyline operator+(Polyline& line, const Point& point);
	Polyline operator+(const Point& point, Polyline& line);
}