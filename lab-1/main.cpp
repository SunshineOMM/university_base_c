#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<libutils/io.h>
#include "point.h"
#include <math.h>
#include <iostream>
#include <cstdio>
#include "c-Lines.h"
#include "cpp-Lines.h"
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdio.h>
namespace C {
	void menu(int& cycle, C::point& p1, C::point& p2, straight& s1, straight& s2, C::point& p3, C::point& p4) {
		printf("�� ���������� � ������� ����, �������� ���� �� ��������� ��������:\n\t");
		printf(" 1) ���������� ���� ����� ������ � ���� �������\n\t 2) ���������� ���� ����� ����� �������\n\t 3) ");
		printf("����������� ����� �� ����� �� ������ ������� �� ������\n\t 4) ����������� ����� ����������� ������\n\t 5) �����\n");
		int choice = 0;
		choice = utils::read_int("", 0, 6);
		switch (choice) {
		case 1: {
			directTask(s1, p1, p2);
			printf("���� ����� �������� ������ � ���� ������� �����: %f\n\n", angleBWLineAndAbsc(s1));
		}break;
		case 2: {
			printf("������� ������ ������: \n");
			directTask(s1, p1, p2);
			printf("������� ������ ������: \n");
			directTask(s2, p3, p4);
			printf("���� ����� ������� �����: %f\n", angleBWLineAndLine(s1,s2));


		}break;
		case 3: {

			printf("������� �������� ��������� ������ �����: \n");
			pointDefinition(p1);
			printf("������� �������� ���������  ������ �����: \n");
			pointDefinition(p2);
			directTask(s1, p3, p4);
			int result = oppositePointsFromTheLine(s1,p1, p2);
			if (result == 1) printf("�������� ����� ����� �� ���� ������� �� �������� ������\n");
			else {
				if (result == 0) printf("�������� ����� ����� �� ������ ������� �� �������� ������\n");
				else {
					if (result == 3) printf("���� �� ����� ����� �� ������\n");
					else {
						if (result == 4) printf("��� ����� ����� �� ������\n");
						else printf("������, ���������� ��� ���");
					}
				}
			}
		}break;
		case 4: {
			printf("������� ������ ������: \n");
			directTask(s1, p1, p2);
			printf("������� ������ ������: \n");
			directTask(s2, p3, p4);
			if (getA(s1) == getB(s2) && getB(s1) == getA(s2) && getC(s1) == getC(s2)) printf("�������� ������ ������������� ���� �� ����� � ���� ����������� ���������� ����� �����������\n");
			LineIntersection(s1, s2,p1);
			LineIntersection(s1, s2,p1);
			printf("���������� ����� �����������: (%f;%f)\n", getX(p1), getY(p1));
		}break;
		case 5: {
			cycle = 0; }break;
		}
	}
}
namespace Cpp {
	void menu(int& cycle, Cpp::point& p1, Cpp::point& p2, straight& s1, straight& s2, Cpp::point& p3, Cpp::point& p4) {
		printf("�� ���������� � ������� ����, �������� ���� �� ��������� ��������:\n\t");
		printf(" 1) ���������� ���� ����� ������ � ���� �������\n\t 2) ���������� ���� ����� ����� �������\n\t 3) ");
		printf("����������� ����� �� ����� �� ������ ������� �� ������\n\t 4) ����������� ����� ����������� ������\n\t 5) �����\n");
		int choice = 0;
		choice = utils::read_int("", 0, 6);
		switch (choice) {
		case 1: {
			directTask(s1, p1, p2);
			printf("���� ����� �������� ������ � ���� ������� �����: %f\n\n", s1.angleBWLineAndAbsc());
		}break;
		case 2: {
			printf("������� ������ ������: \n");
			directTask(s1, p1, p2);
			printf("������� ������ ������: \n");
			directTask(s2, p3, p4);
			printf("���� ����� ������� �����: %f\n", s1.angleBWLineAndLine(s2));


		}break;
		case 3: {

			printf("������� �������� ��������� ������ �����: \n");
			p1.pointDefinition();
			printf("������� �������� ���������  ������ �����: \n");
			p2.pointDefinition();
			directTask(s1, p3, p4);
			int result = s1.oppositePointsFromTheLine(p1, p2);
			if (result == 1) printf("�������� ����� ����� �� ���� ������� �� �������� ������\n");
			else {
				if (result == 0) printf("�������� ����� ����� �� ������ ������� �� �������� ������\n");
				else {
					if (result == 3) printf("���� �� ����� ����� �� ������\n");
					else {
						if (result == 4) printf("��� ����� ����� �� ������\n");
						else printf("������, ���������� ��� ���");
					}
				}
			}
		}break;
		case 4: {
			printf("������� ������ ������: \n");
			directTask(s1, p1, p2);
			printf("������� ������ ������: \n");
			directTask(s2, p3, p4);
			if (s1.getA() == s2.getB() && s1.getB() == s2.getA() && s1.getC() == s2.getC()) printf("�������� ������ ������������� ���� �� ����� � ���� ����������� ���������� ����� �����������\n");
			printf("���������� ����� �����������: (%f;%f)\n", s1.LineIntersection(s2).getX(), s1.LineIntersection(s2).getY());
		}break;
		case 5: {
			cycle = 0; }break;
		}
	}

}
int main()
{

	setlocale(LC_ALL, "RUS");
	using namespace Cpp;
	int cycle = 1;
	point p1;
	point p2;
	point p3;
	point p4;
	straight s1;
	straight s2;
	while (cycle) {
		menu(cycle, p1, p2, s1, s2, p3, p4);
	}
}