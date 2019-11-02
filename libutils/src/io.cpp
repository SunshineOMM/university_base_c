#include <libutils/io.h>
#include <math.h>
#include <iostream>
#include <cstdio>
#include <string.h>
#include <conio.h>
#include <errno.h>
#include <stdio.h>

int utils::read_int(const char*prompt, int min, int max)
	{
		while (true)
		{
			std::cout << prompt << std::endl;
			char str[16];
			fgets(str, sizeof(str), stdin);
			if (strchr(str, '\n') == NULL)
			{
				int c;
				bool f = true;
				while ((c = fgetc(stdin)) != '\n' && c != EOF)
				{
					if (!isspace(c))
					{
						f = false;
					}
				}
				if (f == false)
				{
					std::cout << "������� ������ ������� �������.\n";
					continue;
				}
			}
			char* endptr = NULL;
			errno = 0;
			long n = strtol(str, &endptr, 10);
			if (errno == ERANGE)
			{
				std::cout << "�������� ����� ������� �������.\n";
				continue;
			}
			if (str == endptr)
			{
				std::cout << "�� ������� ������������� ������ � �����.\n";
				continue;
			}
			bool flag = true;
			for (char*p = endptr; *p != 0; ++p)
			{
				if (!isspace(*p))
				{
					flag = false;
					break;
				}
			}
			if (flag == false) {
				std::cout << "������ �������� ������������ �������.\n";
				continue;
			}
			if (n<min || n>max)
			{
				std::cout << "���������� ��������:"<<"("<< min<<","<< max<<")"<<std::endl;
				continue;
			}
			return (int)n;
		}
	}
double utils::read_double(const char* prompt, double min, double max) {
	while (true) {
		std::cout << prompt << std::endl;
		char str[16];
		fgets(str, sizeof(str), stdin);
		if (strchr(str, '\n') == NULL) {
			bool f = true;
			int c;
			while ((c = fgetc(stdin)) != '\n' && c != EOF) {
				if (!isspace(c)) {
					f = false;
				}
			}
			if (f == false) {
				std::cout << "��������� ������ ������� �������\n";
				continue;
			}
		}
		char* endptr = NULL;
		errno = 0;
		double n = strtod(str, &endptr);
		if (errno == ERANGE) {
			std::cout << "�������� ����� ������� �������\n";
			continue;
		}
		if (endptr == str) {
			std::cout << "� ������ �� ������� �����\n";
			continue;
		}
		bool correct = true;
		for (char* p = endptr; *p != 0; ++p) {
			if (!isspace(*p) && *p != '.') {
				correct = false;
				break;
			}
		}
		if (correct == false) {
			std::cout << "�� ���������� �������\n";
			continue;
		}
		if (n < min || n > max) {
			std::cout << "����� ��� ���������. ���������� �������� : ("<< min<<","<< max<<")"<<std::endl;
			continue;
		}
		return (double)n;
	}
}
