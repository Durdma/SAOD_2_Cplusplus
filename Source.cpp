#define NOMINMAX

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "List.h"

//Функция для генерации случайных чисел
int GetRandomNumber(int min, int max)
{

	static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);

	return static_cast<int>(rand() * fraction * (max - min + 1) + min);

}

void CheckInput(int &input_buff)
{

	while ((!std::cin.good() || std::cin.peek() != '\n') || (input_buff <= 0))		//Проверка на то, что int
	{

		std::cerr << "Некорректный ввод данных!!!" << std::endl;
		std::cout << "Вводимое поле должно быть целым положительным числом!!!" << std::endl;
		std::cout << "Повторите ввод!!!" << std::endl;

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		std::cin	>> input_buff;
		std::cout	<< std::endl;

	}

}

//Функция ввода размера списка
void InputWidth(int &out_width)
{

	std::cout	<< "Введите длину списка: ";

	std::cin	>> out_width;

	CheckInput(out_width);

	std::cout	<< std::endl;

}

void InputList(List &input_list, const int &length)
{

	int numb{};

	for (int i = 0; i < length; i++)
	{

		/*std::cout << std::endl;

		std::cin >> numb;

		std::cout << std::endl;

		input_list.pushBack(numb);*/

		input_list.pushBack(GetRandomNumber(-(length / 2), (length / 2) - 1));

	}

}

//Не дает использовать костант ссылку на лист почему??? не дает вызвать при константе getLength

void ShowList(List &list)
{

	int length = list.getLength();

	for (int i = 0; i < length; i++)
	{

		if (i % 5 == 0)
		{

			std::cout << std::endl;

		}

		std::cout << std::setw(3) << std::right << i << " эл." << std::setw(3) << std::right << list[i] << "   ";

	}

}

void commandFunction(List &list)
{

	int flag{};
	int index{};
	int numb{};

	while (flag != 7)
	{

		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << "Введите цифру для выполнения необходимой команды: " << std::endl;
		std::cout << std::endl;
		std::cout << "1 - Добавление эл. в конец списка" << std::endl;
		std::cout << "2 - Добавление эл. в начало списка" << std::endl;
		std::cout << "3 - Удаление первого эл. списка" << std::endl;
		std::cout << "4 - Удаление последнего эл. списка" << std::endl;
		std::cout << "5 - Вставка нового элемента по индексу" << std::endl;
		std::cout << "6 - Удаление элемента по индексу" << std::endl;
		std::cout << "7 - Продолжить выполнение программы" << std::endl;
		std::cout << std::endl;
		std::cout << "Ввод: ";
		std::cin >> flag;

		CheckInput(flag);

		switch (flag)
		{

		case 1:

			std::cout << "Введите число, которое хотите внести в конец списка: ";
			std::cin >> numb;
			std::cout << std::endl;
			std::cout << std::endl;

			list.pushBack(numb);
			ShowList(list);
			break;

		case 2:

			std::cout << "Введите число, которое хотите внести в начало списка: ";
			std::cin >> numb;
			std::cout << std::endl;
			std::cout << std::endl;

			list.pushFront(numb);
			ShowList(list);
			break;

		case 3:

			std::cout << "Удалено первое число.";
			std::cout << std::endl;
			std::cout << std::endl;

			list.popFront();
			ShowList(list);
			break;

		case 4:

			std::cout << "Удалено последнее число.";
			std::cout << std::endl;
			std::cout << std::endl;

			list.popBack();
			ShowList(list);
			break;

		case 5:

			std::cout << "Введите индекс, в который вы хотите добавить элемент: ";
			std::cin >> index;
			std::cout << std::endl;
			std::cout << "Введите число: ";
			std::cin >> numb;
			std::cout << std::endl;
			std::cout << std::endl;

			list.insert(numb, index);
			ShowList(list);
			break;

		case 6:

			std::cout << "Введите индекс эл., который необходимо удалить: ";
			std::cin >> index;
			std::cout << std::endl;
			std::cout << std::endl;

			list.remove(index);
			ShowList(list);
			break;

		default:
			break;

		}

	}

	ShowList(list);

}

void GetFrequency(List &input_list)
{

	List frequency;

	int length{};

	for (int i = 0; i < input_list.getLength(); i++)
	{
		
		int count{};

		for (int j = 0; j < input_list.getLength(); j++)
		{

			if (input_list[i] == input_list[j])
			{

				count++;

				if (i != j)
				{

					input_list.remove(j);

					j--;

				}

			}

		}

		if (count > 1)
		{

			frequency.pushBack(count);

		}

		else
		{

			input_list.remove(i);
			i--;

		}

	}

	length = input_list.getLength();

	for (int i = 0; i < length; i++)
	{

		for (int j = 0; j < length - 1; j++)
		{

			if (frequency[j] < frequency[j + 1])
			{

				int tmp				= input_list[j];
				input_list[j]		= input_list[j + 1];
				input_list[j + 1]	= tmp;

				int tmp2			= frequency[j];
				frequency[j]		= frequency[j + 1];
				frequency[j + 1]	= tmp2;

			}

		}

	}

	std::cout << std::endl;

	for (int i = 0; i < length; i++)
	{

		if (i % 5 == 0)
		{

			std::cout << std::endl;

		}

		std::cout << "Число" << std::setw(4) << std::right << input_list[i] << " появилось " << frequency[i] << "   ";

	}

	std::cout << std::endl;

}

void main()
{

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	srand(time(NULL));

	List list;

	int length{};

	InputWidth(length);
	InputList(list, length);
	ShowList(list);
	commandFunction(list);
	GetFrequency(list);

}