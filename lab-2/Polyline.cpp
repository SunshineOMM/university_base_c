#include<libutils/io.h>
#include "Point.h"
#include "Polyline.h"
#include "Lines.h"
#include <Cstdlib>
#include <cstdio>
#include <cmath>
#include <string.h>
#include <iostream>
namespace  zigzag{
	Polyline::Polyline() :_head(nullptr), _number(0), _lenghtCache(-1) {
		extern bool trace;
		if (trace) std::cout<<"\tКонструктор по умолчанию\n";
	}
	Polyline::Polyline(const int num) : _head(new Point[num]), _number(num), _lenghtCache(-1) {
		if (num <= 0) throw "Ошибка, некорректное количество вершин";
		extern bool trace;
		for (int i = 0; i < num; ++i) {
			_head[i] = Point(rand() % 100, rand() % 100);
		}
		if (trace) std::cout << "\tКонструктор с параметром\n";
	}
	Polyline::~Polyline() {
		extern bool trace;
		delete[] _head;
		_head=nullptr;
		if (trace) std::cout << "\tДеструктор\n";
	}
	Polyline& Polyline::operator =(const Polyline& line) {
		extern bool trace;
		delete[] _head;
		_head = new Point[line._number];
		_number = line._number;
		for (int i = 0; i < line._number; ++i) {
			_head[i] = line[i];
		}
		_lenghtCache = line._lenghtCache;
		if (trace) std::cout << "\tОператор присваивания копированием\n";
		return *this;
	}
	Polyline::Polyline(const Polyline& line) :_head(new Point[line._number]), _number(line._number), _lenghtCache(line._lenghtCache) {
		extern bool trace;
		for (int i = 0; i < line._number; ++i) {
			_head[i] = line._head[i];
		}
		if (trace) std::cout << "\tКонструктор копирования\n";
	}
	Polyline::Polyline(Polyline&& tLine) noexcept :_head(tLine._head), _number(tLine._number), _lenghtCache(-1) {
		extern bool trace;
		tLine._head = nullptr;
		tLine._number = 0;
		if (trace) std::cout << "\tКонструктор перемещения\n";
	}
	Polyline& Polyline::operator=(Polyline&& tLine)noexcept {
		extern bool trace;
		delete[] _head;
		_head = tLine._head;
		_number = tLine._number;
		_lenghtCache = -1;
		tLine._head = nullptr;
		tLine._number = 0;
		if (trace) std::cout << "\tОператор присваивания перемещением\n";
		return *this;
	}
	
	double Polyline::getCache()const {
		return _lenghtCache;
	} 
	
	int Polyline::getNumber()const {
		return _number;
	}
	Point& Polyline::operator[](const int ind){	
		if (ind >=_number || ind < 0) throw "Невозможно получить доступ к точке";
		return _head[ind];
	}
	const Point& Polyline::operator[](const int ind)const {
		if (ind >= _number || ind < 0) throw "Невозможно получить доступ к точке";
		return _head[ind];
	}
	void Polyline::insertByIndex(const int ind, const Point& point){
		if (ind < 0 || ind >_number+1) throw"Ошибка вставки, укажите верный индекс либо убедитесь,что указатель не нулевой";
		Polyline lineRes(_number + 1);
		if (ind == _number) {
			for (int i = 0; i < _number; ++i) {
				lineRes._head[i] = _head[i];
			}
			lineRes[_number] = point;
		}
		else {
			for (int i = 0; i < ind; ++i) {
				lineRes._head[i] = _head[i];
			}
			lineRes._head[ind] = point;
			for (int i = ind + 1; i < lineRes.getNumber(); ++i) {
				lineRes._head[i] = _head[i - 1];
			}
		}
		resetCache();
		*this = lineRes;
	}
	void Polyline::deletByIndex(const int ind) {
		if (ind<0 || ind >=_number) throw"Ошибка удаления, укажите верный индекс либо убедитесь,что указатель не нулевой";
		for (int i = ind; i < _number - 1; ++i) {
			_head[i] = _head[i + 1];
		}
		_number--;
	}
	bool Polyline::selfIntersectionDefinition()const {
		if ( _number < 2) throw"Ошибка определения самопересечений";
		auto* lines = new Straight[getNumber() - 1];
		Point point(0, 0);
		auto flag = false;
		for (int i = 0; i < getNumber() - 1; ++i) {
			lines[i] = Straight(_head[i], _head[i + 1]);
		}
		for (int i = 0; i < getNumber() - 2; ++i) {
			for (int j = i; j < getNumber() - 2 - i; ++j) {
				point = lines[i].LineIntersection(lines[j]);
				if (point.getX() == NAN && point.getY() == NAN) continue;
				if ((_head[i].getX() > _head[i + 1].getX() && _head[i].getX() > point.getX() && _head[i + 1].getX() < point.getX()) || (_head[i + 1].getX() > _head[i].getX() && _head[i + 1].getX() > point.getX() && _head[i].getX() < point.getX())) flag = true;
				if (((_head[j].getX() > _head[j + 1].getX() && _head[j].getX() > point.getX() && _head[j + 1].getX() < point.getX()) || (_head[j + 1].getX() > _head[j].getX() && _head[j + 1].getX() > point.getX() && _head[j].getX() < point.getX())) && flag == true) return true;
			}
		}
		delete[] lines;
		return false;
	}
	double Polyline::calculateLenghtLine()const {
		if ( _number <= 1) throw"Ошибка подсчёта длины";
		if (_lenghtCache != -1) return _lenghtCache;
		auto sum = 0.000;
		for (int i = 1; i < getNumber(); ++i) {
			sum = sum + sqrt(pow(_head[i].getX() - _head[i - 1].getX(), 2) + pow(_head[i].getY() - _head[i - 1].getY(), 2));
		}
		_lenghtCache=sum;
		return sum;
	}
	bool operator==(const Polyline& line1, const Polyline& line2) {
		if (line1.getNumber() != line2.getNumber()) return false;
		for (int i = 0; i < line1.getNumber(); ++i) {
			if (line1[i] != line2[i]) return false;
		}
		return true;
	}
	bool operator!=(const Polyline& line1, const Polyline& line2) {
		return(!(line1 == line2));
	}
	Polyline& operator+=( Polyline& line1, const Polyline& line2) {
		const auto num = line1.getNumber();
		for (int i = 0; i < line2.getNumber(); ++i) {
			line1.insertByIndex(i+ num, line2[i]);
		}
		 return line1;
	}
	Polyline& operator+=(Polyline& line, const Point& point) {
		line.insertByIndex(line.getNumber(),point);
		return line;
	}
	Polyline operator+(const Polyline& line1,const Polyline& line2) {
		Polyline lineRes = line1;
		lineRes += line2;
		return lineRes;
	}
	Polyline operator+(Polyline& line, const Point& point) {
		line += point;
		return line;
	}
	Polyline operator+(const Point& point, Polyline& line) {
		line.insertByIndex(0, point);
		return line;
	}
}