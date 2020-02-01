// SkipList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "Header.h"
#include <iostream>
#include <stdlib.h>
#include <ctime> 

using namespace std;


//главная функция. в цикле принимает команды пользователя
int main()
{
	//чтобы русские буквы выводились
	setlocale(LC_ALL, "Russian");
	cout << "Список с пропусками (введите ? для справки)\n";
	SkipList s;//создание списка
	//буфер ввода
	char buf[128];
	//цикл приема команд
	do {
		cout << ">>";
		cin >> buf;
		//угадываение команды
		switch (buf[0]) {
			//справка о программе
		case '?': {
			cout << "Для добавления в список введите 'a 234 567', где 234-ключ, а 567-значение\n";
			cout << "Для удаления введите 'd 234', где 234-ключ\n";
			cout << "Для поиска введите 's 234', где 234-ключ\n";
			cout << "Для вывода списка на экран введите 'p'\n";
			cout << "Для выхода введите 'q'\n";
			break;
		}
				  //добавление элемента
		case 'a': {
			int k;
			int d;
			cin >> k >> d;
			s.add(k, d);
			break;
		}
				  //удаление элемента
		case 'd': {
			int k;
			cin >> k;
			s.del(k);
			break;
		}

				  //поиск по ключу
		case 's': {
			int k;
			cin >> k;
			int x = s.search(k);
			if (x == INT_MIN) {
				cout << "Ничего не найдено...\n";
			}
			else {
				cout << "Найдено: " << x << endl;
			}
			break;
		}
				  //вывод списка на экран
		case 'p':
			s.print();
			break;
			//выход из программы
		case 'q':
			break;
		default:
			cout << "Нераспознанная команда...\n";
		}
	} while (buf[0] != 'q');
	return 0;
}

