#include <vector>
#include <iostream>
#include"CustomRealMatrix.h"
#include"BufferedMatrix.h"
#include"SparseMatrix.h"
#include <libutils/io.h>
#include <memory>
#include <time.h>
#include <cmath>
#include <algorithm>

void menu(int& cycle, std::vector<std::unique_ptr<CustomRealMatrix>>& collection, size_t printElement);
void pasteElement(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index);
void creatingElements(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& count);
void equalElements(const std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index1, const int& index2);
void removeElement(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index);
void printCollection(const std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& printElement)noexcept;
int findMin(std::vector<double>& norms);
double findNorma(const std::vector<double>& vector);
std::vector<double> lineAmount(const std::unique_ptr<CustomRealMatrix>& matrix);
double findNormaStd(const std::vector<double>& vector);

int main() {
	setlocale(LC_ALL, "RUS");
	size_t printElement = 10;
	std::vector<std::unique_ptr<CustomRealMatrix>> collection;
	int cycle = 1;
	while (cycle) {
		try{
		menu(cycle, collection, printElement);
		}
		catch (char* s) {
			std::cout << s << std::endl;
		}
		catch (...) {
			std::cout << "Неизвестная ошибка" << std::endl;
		}
	}
}


void menu(int& cycle, std::vector<std::unique_ptr<CustomRealMatrix>>& collection, size_t printElement) {
	std::cout << "Вы находитесь в главном меню выберите одно из следующих действий:\n\t1) Создание объекта";
	std::cout << "и вставка его по индексу\n\t2) Вставка в конец коллекции";
	std::cout << "указанного числа случайно сгенерированных объектов";
	std::cout << "\n\t3) Удаление объекта из коллекции по индексу; \n\t4) Удаление всех объектов из коллекции";
	std::cout << "\n\t5) Сравнение двух объектов по указанным индексам ";
	std::cout << " \n\t6) Вывод контейнера на экран \n\t7) Oпределения матрицы с наименьшей нормой максимума модуля";
	std::cout << "\n\t8) Выход\n"<< std::endl;
	auto choice = utils::read_int("", 0, 11);
	switch (choice) {
	case 1: {
		unsigned int index = utils::read_int("Введите индекс вставки: ", 0, static_cast<int>(collection.size()));
		pasteElement(collection, index);
	}break;
	case 2: {
		unsigned int count = utils::read_int("Введите количество элементов для вставки: ", 0, 100);
		creatingElements(collection, count);
	}break;
	case 3: {
		if (collection.empty()) throw "Ошибка, коллекция пуста!";
		unsigned int index = utils::read_int("Введите индекс для удаления элемента: ", 0, static_cast<int>(collection.size() - 1));
		removeElement(collection, index);
	}break;
	case 4: {
		if (collection.empty()) throw "Ошибка, коллекция пуста!";
		collection.clear();

	}break;
	case 5: {
		if (collection.empty()) throw "Ошибка, коллекция пуста!";
		unsigned int index1 = utils::read_int("Введите первый индекс для сравнения: ", 0, static_cast<int>(collection.size() - 1));
		unsigned int index2 = utils::read_int("Введите второй индекс для сравнения: ", 0, static_cast<int>(collection.size() - 1));
		equalElements(collection, index1, index2);
	}break;
	case 6: {
		if (collection.empty()) throw "Ошибка, коллекция пуста!";
		printCollection(collection, static_cast<int>(printElement));
	}break;
	case 7: {
		if (collection.empty()) throw "Ошибка, коллекция пуста!";
		switch (rand() % 2)
		{
		case 0: {

			std::vector<double> norms;
			for (int i = 0; i < collection.size(); ++i) {
				norms.push_back(findNorma(lineAmount(collection.at(i))));
			}
			std::cout << "Матрица с наименьшей нормой максимума модуля находится под индексом:";
			std::cout << findMin(norms) << std::endl;
		}break;
		case 1: {
			std::vector<double> norms;
			for (int i = 0; i < collection.size(); ++i) {
				norms.push_back(findNormaStd(lineAmount(collection.at(i))));
			}
			std::cout << "Матрица с наименьшей нормой максимума модуля находится под индексом:";
			int ind = collection.size()-1;
			auto runner = norms.end();
			for (; ind < norms.size(); --ind) {
				if (runner == min_element(norms.begin(), norms.end())) break;
				--runner;
			}
			std::cout << ind << std::endl;
		}break;
		}break;
	case 8: {
		cycle = 0;
	}break;
	}
	}
}

double findNormaStd(const std::vector<double>& vector) {
	auto max = max_element(vector.begin(), vector.end());
	return *max;
}

int findMin(std::vector<double>& norms){
	double min = norms.at(0);
	int index = -1;
	for (int i = 0; i < norms.size();++i) {
		if (norms.at(i) <= min) {
			min = norms.at(i);
			index = i;
		}
	}
	return index;
}

double findNorma(const std::vector<double>& vector) {
	double max = 0;	
	for (int j = 0; j < vector.size(); ++j) {
		if (vector.at(j) > max) max = vector.at(j);
	}
	return max;
}

std::vector<double> lineAmount(const std::unique_ptr<CustomRealMatrix>& matrix) {
	std::vector<double> res;
	double max = 0;
	for (int i = 0; i < matrix->getSize();i+= static_cast<int>(matrix->getSizeN())) {
		for (int j = 0; j < matrix->getSizeN(); ++j) {
			 max = max+abs(matrix->at(j+i));
		}
		res.push_back(max);
		max = 0;
	}
	return res;
}

void pasteElement(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index) {
	 int i = 0;
	switch (utils::read_int("Какой объект вы хотите создать?\n1)  BufferedMatrix\n2)  SparseMatrix\n", 0, 3))
	{
	case 1: {
		auto it = collection.begin();
		do {
			if (i == index) {
				collection.insert(it, std::make_unique<BufferedMatrix>(BufferedMatrix((rand()%10)+1, (rand() % 10)+1)));
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
	}break;
	case 2: {
		auto it = collection.begin();
		do {
			if (i == index) {
				collection.insert(it, std::make_unique<SparseMatrix>(SparseMatrix((rand() % 10)+1, (rand() % 10)+1)));
				break;
			}
			++i;
			++it;
		} while (it != collection.end());
	}break;

	}

}

void creatingElements(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& count) {
	for (auto i = 0; i < count; ++i) {
		auto run = rand() % 2;
		switch (run)
		{
		case 0: {
			collection.push_back(std::make_unique<BufferedMatrix>(BufferedMatrix((rand()%10)+1, (rand() % 10)+1)));
		}break;
		case 1: {
				collection.push_back(std::make_unique<SparseMatrix>(SparseMatrix((rand() % 10) + 1, (rand() % 10) + 1)));
		}break;
		}
	}
}

void equalElements(const std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index1, const int& index2) {

	
	if (collection.at(index1).get()->equals(*(collection.at(index2).get())))
		std::cout << "Объекты равны" << std::endl;
	else
		std::cout << "Объекты не равны" << std::endl;
}

void removeElement(std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& index) {
	 int i = 0;

	for (auto it = collection.begin(); it != collection.end(); ++it, ++i)
	{
		if (i == static_cast<int>(index)) {
			collection.erase(it);
			break;
		}
	}
}

void printCollection(const std::vector<std::unique_ptr<CustomRealMatrix>>& collection, const int& printElement) noexcept {

	bool usingDots = false;

	size_t printCount = collection.size();

	if (collection.size() > printElement)
	{
		printCount = printElement;
		usingDots = true;
	}


	for (size_t i = 0; i < printCount; ++i) {
		std::cout << "[" << i << "] ";
		std::cout << std::endl;
		std::cout << std::endl;
		collection[i].get()->print(std::cout);
		std::cout << std::endl;
	}

	if (usingDots)
		std::cout << "..." << std::endl;
}