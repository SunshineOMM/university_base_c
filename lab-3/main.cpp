
#include"UniquePtr.h"
#include"SharedPtr.h"
#include"Vector.h"
#include"List.h"
#include<cstdio>
#include <iostream>
#include <libutils/io.h>
#include <libutils/Lines.h>
#include <libutils/Point.h>
#include <libutils/Polyline.h>
#include <vector>
#include <list>
#include <memory>

template<class T> using UniquePtrType = UniquePtr<T>;
template<class T> using SharedPtrType = SharedPtr<T>;
template<class T> using CollectionType = Vector<T>;

template <typename T>
void menu(int&,CollectionType<T>& collection, CollectionType<SharedPtrType<zigzag::Polyline>>& collectionShPtr, SharedPtrType<zigzag::Polyline>& shPtr);

template <typename T>
void addElement(CollectionType<T>& c, const int index,const T&  value);

template <typename T>
void removeElement(CollectionType<T>& c, const int index);

template <typename T>
void printCollection(const CollectionType<T>& c);


int main() {
	setlocale(LC_ALL, "RUS");	
	CollectionType<int> collection(3);

	//CollectionType<SharedPtrType<zigzag::Polyline>> collectionShPtr(2);
	zigzag::Polyline polyline(5);
	SharedPtrType<zigzag::Polyline> shPtr(&polyline);
	CollectionType<SharedPtrType<zigzag::Polyline>> collectionShPtr;

	auto cycle = 1;
	while (cycle) {
		try {
			menu(cycle,collection,collectionShPtr,shPtr);
		}
		catch (char* s) {
			std::cout << s << std::endl;
		}
		catch (...) {
			std::cout << "Неизвестная ошибка" << std::endl;
		}
	}
}

template <typename T>
void menu(int& cycle, CollectionType<T>& collection, CollectionType<SharedPtrType<zigzag::Polyline>>& collectionShPtr, SharedPtrType<zigzag::Polyline>& shPtr) {
	std::cout << "Вы находитесь в главном меню выберите одно из следующих действий:\n\t1) Печать коллекции \n\t2) Печать размера коллекции";
	std::cout << "\n\t3) Печать первого элемента \n\t4) Печать последнего элемента \n\t5) Редактирование ";
	std::cout << " \n\t6) Вставка элемента \n\t7) Удаление элемента \n\t8) Удаление коллекции";
	std::cout << "\n\t9) Добавление элемента в конец коллекции SharedPtrType<zigzag::Polyline> \n\t10) Выход\n" << std::endl;
	auto choice = utils::read_int("", 0, 11);
	switch (choice) {
	case 1: {
		printCollection(collection);
	}break;
	case 2: {
		std::cout << "Размер коллекции: " << collection.size() << std::endl;
	}break;
	case 3: {
		if (!(collection.empty()))
			std::cout << "Первый элемент коллекции: " << collection.front() << std::endl;
		else
			throw "Ошибка, коллекция пуста";
	}break;
	case 4: {
		if(!(collection.empty()))
			std::cout << "Последний элемент коллекции: " << collection.back() << std::endl;
				else
				throw "Ошибка, коллекция пуста";
	}break;
	case 5: {
		if (!(collection.empty())) {
			int index = (size_t)utils::read_int("Введите индекс элемента для редактирования: ", 0, (int)collection.size() - 1);

			auto iterator = collection.begin();
			for (auto i = 0; i < index; ++i)
				++iterator;

			*iterator = utils::read_int("Введите значение элемента: ", -1000, 1000);

		}
		else
			throw "Ошибка, коллекция пуста";
	}break;
	case 6: {
		// Убрать -1
		addElement(collection, (size_t)utils::read_int("Введите индекс вставки: ", 0, (int)collection.size()), utils::read_int("Введите значение для вставки: ", -1000, 1000));
	}break;
	case 7: {
		if (!collection.empty())
			removeElement(collection, (size_t)utils::read_int("Введите индекс для удаления элемента: ", 0, (int)collection.size() - 1));
		else
			throw "Ошибка, коллекция пуста";
	}break;
	case 8: {
		collection.clear();
	}break;
	case 9: {
		// Убрать -1
		addElement(collectionShPtr, (int)collectionShPtr.size(), shPtr);
		
	}break;
	case 10: {
		cycle = 0;

	}break;
	}
}

template <typename T>
void addElement(CollectionType<T>& c, const int index, const T&  value) {

	auto iterator(c.begin());

	if (c.empty()) {
		c.insert(iterator, value);
	}
	else {
		for (int i = 0; i < index; ++i) {
			++iterator;
		}
		c.insert(iterator, value);
	}
}

template <typename T>
void printCollection(const CollectionType<T>& c) {
	std::cout << "Элементы коллекции: ";
	int i = 0;
	for( auto it : c) {
		std::cout << "[" << i << "]" << " " << it << " ";
		++it;
		++i;
	}
	std::cout << std::endl;
}

template <typename T>
void removeElement(CollectionType<T>& c, const int index) {
	auto iterator = c.begin();
	for (auto i = 0; i < index; ++i) {
		++iterator;
	}
	c.erase(iterator);
}