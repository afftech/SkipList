// SkipList.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include "Header.h"
#include <iostream>
#include <stdlib.h>
#include <ctime> 

using namespace std;


//������� �������. � ����� ��������� ������� ������������
int main()
{
	//����� ������� ����� ����������
	setlocale(LC_ALL, "Russian");
	cout << "������ � ���������� (������� ? ��� �������)\n";
	SkipList s;//�������� ������
	//����� �����
	char buf[128];
	//���� ������ ������
	do {
		cout << ">>";
		cin >> buf;
		//����������� �������
		switch (buf[0]) {
			//������� � ���������
		case '?': {
			cout << "��� ���������� � ������ ������� 'a 234 567', ��� 234-����, � 567-��������\n";
			cout << "��� �������� ������� 'd 234', ��� 234-����\n";
			cout << "��� ������ ������� 's 234', ��� 234-����\n";
			cout << "��� ������ ������ �� ����� ������� 'p'\n";
			cout << "��� ������ ������� 'q'\n";
			break;
		}
				  //���������� ��������
		case 'a': {
			int k;
			int d;
			cin >> k >> d;
			s.add(k, d);
			break;
		}
				  //�������� ��������
		case 'd': {
			int k;
			cin >> k;
			s.del(k);
			break;
		}

				  //����� �� �����
		case 's': {
			int k;
			cin >> k;
			int x = s.search(k);
			if (x == INT_MIN) {
				cout << "������ �� �������...\n";
			}
			else {
				cout << "�������: " << x << endl;
			}
			break;
		}
				  //����� ������ �� �����
		case 'p':
			s.print();
			break;
			//����� �� ���������
		case 'q':
			break;
		default:
			cout << "�������������� �������...\n";
		}
	} while (buf[0] != 'q');
	return 0;
}

