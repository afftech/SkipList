#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\SkipList\Header.h" //подключаем файл, содержащий тестируемую программу из папки skiplist.

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(AddAndSearch)
		{
			SkipList skip;
			int r = 13, k = 15;	
			skip.add(r, k);			//Передаем некоторые данные для добавления в список.
			Assert::AreEqual(k, skip.search(r));	//Вызываем метод поиска в списке по ключу, нам должны вернуть то же самое значение данных.
													//Метод AreEqual сравнивает значение из переменной и возвращаемое функцией, если совпадают - тест пройден.
		}

		TEST_METHOD(AddAndDelete)
		{
			SkipList skip;
			int k = 13, d = 15;
			skip.add(k, d);		//Снова добавляем данные в список
			skip.del(k);		//И удаляем их
			Assert::AreEqual(INT_MIN, skip.search(k));	//В случае отсутствия данных  метод поиска вернет минимальное целочисленное значение, снова сравниваем.
		}

		TEST_METHOD(TestMultiple)
		{
			SkipList skip;
			int imax = 200, i = 0;
			while (i < imax)		//Вносим 200 разных случайных данных
			{
				skip.add(i, rand());
				i++;
			}
			Assert::AreNotEqual(INT_MIN, skip.search(rand() % imax));		//Ищем рандомное значение в пределах внесенных данных, и сравниваем - должно не совпасть, то есть данные должны быть
		}

		TEST_METHOD(CallEmpty)
		{
			SkipList skip;
			Assert::AreEqual(INT_MIN, skip.search(0));	//Ищем нулевой элемент в пустом спике (да, это уже тест из серии лишь бы что-нибудь)
		}

		TEST_METHOD(RandomTest)
		{
			SkipList skip;
			Assert::IsTrue(0 < skip.randomLevel());		//Вызываем функцию генерации случайного числа, и сравнием, чтобы она была больше 0
		}
		TEST_METHOD(RandomTestWithEntries)
		{
			SkipList skip;
			int imax = 200, i = 0;
			while (i < imax)
			{
				skip.add(i, rand());
				i++;
			}
			Assert::IsTrue(0 < skip.randomLevel());		//Тот же тест, только с предварительной записью двухсот пар данных 											
		}
				TEST_METHOD(dataSearch)
		{
			SkipList skip;
			int r = 13, k = 15;	
			skip.add(r, k);	
			

			Assert::IsTrue(true == skip.data_search());		//Тот же тест, только с предварительной записью двухсот пар данных 											
		}

	};
}
