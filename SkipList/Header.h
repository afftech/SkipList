
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <ctime> 
#pragma once

using namespace std;

class SkipList {
	//for new test
	bool DS= false;
	// внутренний класс для хранения элементов списка
	class Element {
		//каждый элемент хранит ключ
		int key;
		//и значение, связанное с ключом
		int data;
		//и массив указателей на следующие элементы на нескольких уровнях
		Element **next;
		//число этих указателей
		int len;


	public:
		//конструктор для создания элемента
		//n - число указателей в элементе
		//k - ключ
		//d - значение
		Element(int n, int k, int d) {
			//сначала создается массив указателей
			next = new Element*[n];
			//обнуляем их на всякий случай
			for (int i = 0; i < n; i++) {
				next[i] = nullptr;
			}
			//сохраняем число указателей, ключ и значение
			len = n;
			key = k;
			data = d;
		}
		//деструктор. сначала удаляет следующий элемент, потом массив указателей
		~Element() {
			delete next[0];
			delete[] next;
		}
		//возвращает указатель i-го уровня
		Element *nexti(int i) {
			return next[i];
		}
		//переприсваивает указатель i-го уровня
		void setNexti(int i, Element *e) {
			next[i] = e;
		}
		//возвращает число указателей
		int length() {
			return len;
		}
		//возвращает ключ
		int getKey() {
			return key;
		}
		//возвращает значение
		int getData() {
			return data;
		}
		//заменяет значение на другое
		void setData(int d) {
			data = d;
		}
		//вывод на экран списка (только ключей), начиная с этого элемента
		int print1() 
		{
			Element *n = nexti(0);
			if (n == nullptr) {
				return INT_MIN;
			}
			while (n != nullptr) {
				Element **nn = n->next;
				for (int i = 0; i < n->length(); i++) {
					cout.width(5);
					cout << n->key;
				}
				cout << endl;
				n = nn[0];
			}
			cout << "--------------------\n";
		};
	};
	//корневой элемент списка
	Element *first;
	//максимальный уровень списка
	int level = 0;

public:
	//конструктор списка
	SkipList() {
		//инициализируем генератор случайных чисел
		srand((int)time(0));
		//создаем корневой элемент списка
		first = new Element(16, INT_MIN, 0);
	};
	//деструктор списка
	~SkipList() {
		delete first;
	}
	//функция добавления элемента в список
	//key - ключ
	//data - значение
	void add(int key, int data) {
		//сначала создаем массив для временного хранения указателей разных уровней
		Element **upd = new Element*[first->length()];
		//обнуляем на всякий случай
		for (int i = 0; i < first->length(); i++) {
			upd[i] = nullptr;
		}
		//начиная с первого элемента
		Element *n = first;
		//для каждого уровня ищем элемент, который будет идти сразу за вставляемым элементом
		for (int i = level; i >= 0; i--) {
			Element *ni = n->nexti(i);
			while (ni != nullptr && ni->getKey() < key) {
				n = ni;
				ni = n->nexti(i);
			}
			//запоминаем адрес первого элемента, ключ которого больше ключа 
			//вставляемого элемента на i-м уровне
			upd[i] = n;
		}
		//проверяем, может элемент с таким ключом уже есть
		n = n->nexti(0);
		if (n != nullptr && n->getKey() == key) {
			//если есть, то просто заменяем значение для этого ключа
			n->setData(data);
		}
		else {
			//если элемента с таким ключом еще нет
			//определеем случайным образом число указателей в новом элементе
			int lvl = randomLevel();
			//если их больше чем было ранее, головной массив указателей корректируем
			if (lvl > level) {
				for (int i = level; i < lvl; i++) {
					upd[i] = first;
				}
				level = lvl;
			}
			//создаем новый элемент
			n = new Element(lvl, key, data);
			//вставляем его в список на каждом уровне
			for (int i = 0; i < lvl; i++) {
				n->setNexti(i, upd[i]->nexti(i));
				upd[i]->setNexti(i, n);
			}
		}
	};
	//функция вычисления, сколько указателей будет в новом элементе
	int randomLevel() 
	{
		int lvl = 1;
		//в 40% случаев указателей будет больше чем 1 и т.д.
		while (rand() % 10 < 4 && lvl < first->length() - 1) {
			lvl++;
		}
		return lvl;
	};
	//поиск элемента в списке по ключу
	int search(int key) 
	{
		//начинаем с головного элемента
		Element *n = first;
		//и с самого верхнего уровня
		for (int i = level; i >= 0; i--) {
			//пока ключи элементов в списке i-го уровня меньше искомого
			while (n->nexti(i) != nullptr && n->nexti(i)->getKey() < key) {
				//движемся дальше по уровню
				n = n->nexti(i);
			}
		}
		//n - это последний элемент, ключ которого меньше искомого
		//переходим к следующему. его ключ больше или равен искомому
		n = n->nexti(0);
		//проверяем, не равен ли
		if (n != nullptr && n->getKey() == key) {
			//если равен, возвращаем данные, связанные с ключом
			DS=true;
			return n->getData();
		}
		//если не равен, то нет таккого элемента
		//и тогда возвращаем минимальное возможное значение
		
		else {
		DS=false;
		return INT_MIN;
		}
	};
	bool data_search(){
		bool ds=DS;
		return ds;
	};
	//удаление элемента по ключу
	void del(int key) {
		//так же, как при добавлении создаем массив указателей
		Element **upd = new Element*[first->length()];
		//и так же, как при поиске ищем на каждом уровне указатель
		//на последний элемент, с большим или равным искомому ключом
		Element *n = first;
		for (int i = level; i >= 0; i--) {
			while (n->nexti(i) != nullptr && n->nexti(i)->getKey() < key) {
				n = n->nexti(i);
			}
			upd[i] = n;
		}
		n = n->nexti(0);
		//если нашли элемент с искомым ключом
		if (n != nullptr && n->getKey() == key) {
			//на кажом уровне удаляем из списка этот элемент
			for (int i = 0; i < level; i++) {
				if (upd[i]->nexti(i) != n) {
					break;
				}
				upd[i]->setNexti(i, n->nexti(i));
			}
			while (level > 1 && first->nexti(level) == nullptr) {
				level--;
			}
		}
	};
	//вывод списка
	void print() {
		//это вывод всех элементов, начиная с первого
		first->print1();
	}
};
