#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include <cmath>
#include <iostream>
#include <string.h>
#include <errno.h>
#include<libutils/io.h>
#include "Point.h"
#include "Lines.h"
#include "Polyline.h"


using namespace zigzag;
bool trace=0;
Polyline PolylineDefinition();
std::ostream& operator<< (std::ostream& out, const Polyline& line);
std::ostream& operator<< (std::ostream& out, const Point& point);
void printBreakLine(const Polyline& line);
Point pointDefinition();
void menu(int& cycle);


int main()
{

	setlocale(LC_ALL, "RUS");
	auto cycle = 1;
	
	while (cycle) {
		try {
			menu(cycle);
		}
		catch (char* s) {
			std::cout << s << std::endl;
		}
		catch (...) {
			std::cout << "Неизвестная ошибка" << std::endl;
		}

	}
}


Polyline PolylineDefinition() {
	const auto  amount = utils::read_int("Введите количество вершин ломаной:", 0, 100);
	Polyline lineRes(amount);
	return lineRes;
}
std::ostream& operator<< (std::ostream& out, const Polyline& line)
{
	for (int i = 0; i < line.getNumber(); ++i) {

		out << "[" << i << "]" << "     (" << line[i].getX() << "," << line[i].getY() << ")" << std::endl;
	}
	return out;
}
std::ostream& operator<< (std::ostream& out, const Point& point)
{
	out << "(" << point.getX() << "," << point.getY() << ")";
	return out;
}
void printBreakLine(const Polyline& line) {
	std::cout << "Количество точек: " << line.getNumber() << std::endl;
	std::cout << "Длина ломаной: " << line.getCache() << std::endl;
	std::cout << "Индекс  " << "Координаты (X,Y)" << std::endl;
	std::cout << line;
}
Point pointDefinition() {
	const auto x1 = utils::read_double("Введите значение координаты Х : ", -1000, 1000);
	const auto y1 = utils::read_double("Введите значение координаты У : ", -1000, 1000);
	return Point(x1, y1);
}
void menu(int& cycle) {

	std::cout << "Вы находитесь в главном меню выберите одно из следующих действий:\n\t1) Открыть вершину \n\t2) Редактировать вершину";
	std::cout << "\n\t3) Сложить две ломаные \n\t4) Добавление вершины в конец ломанной \n\t5) Добавление вершины в начало ";
	std::cout << "ломанной \n\t6) Вставка вершины по индексу \n\t7) Удаление вершины по индексу \n\t8) Определение самопересечений";
	std::cout << "\n\t9) Вычисление длины ломаной \n\t10) Выход\n" << std::endl;
	auto choice = utils::read_int("", 0, 11);
	switch (choice) {
	case 1: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto num = utils::read_int("Введите индекс точки для её открытия:", -1, line.getNumber());
		std::cout << line[num] << std::endl;
	}break;
	case 2: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto num = utils::read_int("Введите индекс точки для её редактирования:", -1, line.getNumber());
		std::cout << line[num] << std::endl;
		std::cout << "Введите новую точку:\n";
		Point point = pointDefinition();
		line[num].setX(point.getX());
		line[num].setY(point.getY());
		printBreakLine(line);
	}break;
	case 3: {
		trace = true;
		std::cout << "Определите первую ломаную\n";
		Polyline line1 = PolylineDefinition();
		printBreakLine(line1);
		std::cout << "Определите вторую ломаную\n";
		Polyline line2 = PolylineDefinition();
		printBreakLine(line2);
		Polyline lineRes =line1 + line2;
		std::cout << "Результат сложения:\n";
		printBreakLine(lineRes);
		trace = false;

	}break;
	case 4: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		Point point = pointDefinition();
		Polyline lineRes = line + point;
		printBreakLine(lineRes);
	}break;
	case 5: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		std::cout << "Введите координаты точки :\n";
		Point point = pointDefinition();
		Polyline lineRes = point + line;
		printBreakLine(lineRes);
	}break;
	case 6: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto num = utils::read_int("Введите индекс точки для её вставки:", -1, line.getNumber());
		Point point = pointDefinition();
		line.insertByIndex(num, point);
		printBreakLine(line);
	}break;
	case 7: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto num = utils::read_int("Введите индекс точки для её удаления:", -1, line.getNumber());
		line.deletByIndex(num);
		printBreakLine(line);
	}break;
	case 8: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto flag = line.selfIntersectionDefinition();
		if (flag) std::cout << "Самопересечения есть\n";
		else std::cout << "Самопересечений нет\n";

	}break;
	case 9: {
		Polyline line = PolylineDefinition();
		printBreakLine(line);
		const auto sum = line.calculateLenghtLine();
		std::cout << "Длина ломаной равна:" << sum << std::endl;
	}break;
	case 10: {
		cycle = 0; }break;
	}
}
