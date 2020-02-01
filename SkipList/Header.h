
#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <ctime> 
#pragma once

using namespace std;

class SkipList {
	// ���������� ����� ��� �������� ��������� ������
	class Element {
		//������ ������� ������ ����
		int key;
		//� ��������, ��������� � ������
		int data;
		//� ������ ���������� �� ��������� �������� �� ���������� �������
		Element **next;
		//����� ���� ����������
		int len;

	public:
		//����������� ��� �������� ��������
		//n - ����� ���������� � ��������
		//k - ����
		//d - ��������
		Element(int n, int k, int d) {
			//������� ��������� ������ ����������
			next = new Element*[n];
			//�������� �� �� ������ ������
			for (int i = 0; i < n; i++) {
				next[i] = nullptr;
			}
			//��������� ����� ����������, ���� � ��������
			len = n;
			key = k;
			data = d;
		}
		//����������. ������� ������� ��������� �������, ����� ������ ����������
		~Element() {
			delete next[0];
			delete[] next;
		}
		//���������� ��������� i-�� ������
		Element *nexti(int i) {
			return next[i];
		}
		//��������������� ��������� i-�� ������
		void setNexti(int i, Element *e) {
			next[i] = e;
		}
		//���������� ����� ����������
		int length() {
			return len;
		}
		//���������� ����
		int getKey() {
			return key;
		}
		//���������� ��������
		int getData() {
			return data;
		}
		//�������� �������� �� ������
		void setData(int d) {
			data = d;
		}
		//����� �� ����� ������ (������ ������), ������� � ����� ��������
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
	//�������� ������� ������
	Element *first;
	//������������ ������� ������
	int level = 0;

public:
	//����������� ������
	SkipList() {
		//�������������� ��������� ��������� �����
		srand((int)time(0));
		//������� �������� ������� ������
		first = new Element(16, INT_MIN, 0);
	};
	//���������� ������
	~SkipList() {
		delete first;
	}
	//������� ���������� �������� � ������
	//key - ����
	//data - ��������
	void add(int key, int data) {
		//������� ������� ������ ��� ���������� �������� ���������� ������ �������
		Element **upd = new Element*[first->length()];
		//�������� �� ������ ������
		for (int i = 0; i < first->length(); i++) {
			upd[i] = nullptr;
		}
		//������� � ������� ��������
		Element *n = first;
		//��� ������� ������ ���� �������, ������� ����� ���� ����� �� ����������� ���������
		for (int i = level; i >= 0; i--) {
			Element *ni = n->nexti(i);
			while (ni != nullptr && ni->getKey() < key) {
				n = ni;
				ni = n->nexti(i);
			}
			//���������� ����� ������� ��������, ���� �������� ������ ����� 
			//������������ �������� �� i-� ������
			upd[i] = n;
		}
		//���������, ����� ������� � ����� ������ ��� ����
		n = n->nexti(0);
		if (n != nullptr && n->getKey() == key) {
			//���� ����, �� ������ �������� �������� ��� ����� �����
			n->setData(data);
		}
		else {
			//���� �������� � ����� ������ ��� ���
			//���������� ��������� ������� ����� ���������� � ����� ��������
			int lvl = randomLevel();
			//���� �� ������ ��� ���� �����, �������� ������ ���������� ������������
			if (lvl > level) {
				for (int i = level; i < lvl; i++) {
					upd[i] = first;
				}
				level = lvl;
			}
			//������� ����� �������
			n = new Element(lvl, key, data);
			//��������� ��� � ������ �� ������ ������
			for (int i = 0; i < lvl; i++) {
				n->setNexti(i, upd[i]->nexti(i));
				upd[i]->setNexti(i, n);
			}
		}
	};
	//������� ����������, ������� ���������� ����� � ����� ��������
	int randomLevel() 
	{
		int lvl = 1;
		//� 40% ������� ���������� ����� ������ ��� 1 � �.�.
		while (rand() % 10 < 4 && lvl < first->length() - 1) {
			lvl++;
		}
		return lvl;
	};
	//����� �������� � ������ �� �����
	int search(int key) 
	{
		//�������� � ��������� ��������
		Element *n = first;
		//� � ������ �������� ������
		for (int i = level; i >= 0; i--) {
			//���� ����� ��������� � ������ i-�� ������ ������ ��������
			while (n->nexti(i) != nullptr && n->nexti(i)->getKey() < key) {
				//�������� ������ �� ������
				n = n->nexti(i);
			}
		}
		//n - ��� ��������� �������, ���� �������� ������ ��������
		//��������� � ����������. ��� ���� ������ ��� ����� ��������
		n = n->nexti(0);
		//���������, �� ����� ��
		if (n != nullptr && n->getKey() == key) {
			//���� �����, ���������� ������, ��������� � ������
			return n->getData();
		}
		//���� �� �����, �� ��� ������� ��������
		//� ����� ���������� ����������� ��������� ��������
		else return INT_MIN;
	};
	//�������� �������� �� �����
	void del(int key) {
		//��� ��, ��� ��� ���������� ������� ������ ����������
		Element **upd = new Element*[first->length()];
		//� ��� ��, ��� ��� ������ ���� �� ������ ������ ���������
		//�� ��������� �������, � ������� ��� ������ �������� ������
		Element *n = first;
		for (int i = level; i >= 0; i--) {
			while (n->nexti(i) != nullptr && n->nexti(i)->getKey() < key) {
				n = n->nexti(i);
			}
			upd[i] = n;
		}
		n = n->nexti(0);
		//���� ����� ������� � ������� ������
		if (n != nullptr && n->getKey() == key) {
			//�� ����� ������ ������� �� ������ ���� �������
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
	//����� ������
	void print() {
		//��� ����� ���� ���������, ������� � �������
		first->print1();
	}
};