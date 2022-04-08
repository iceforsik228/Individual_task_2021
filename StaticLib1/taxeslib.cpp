/**
* \file taxeslib.cpp
* \author Чихичин Станислав Сергеевич
* \version 1.0
* \date 10.01.2022
* \brief Файл cpp, который отвечает за чтение файла taxes.txt
* \details Данный файл содержит функции, которые осуществляют
* ввод данных из файла taxes.txt
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <assert.h>
#include "taxes.h"
using namespace std;

/**
* \brief Функция для получения количества наименований ресурсов
* \details Функция обращается к файлу taxes.txt и собирает 1 значение -
* - количество наименований ресурсов
* \exception Имеется исключение для Q - значение не может быть
* равным 0
* \return Возвращает переменную Q
*/
int numberResourceInput()
{
	FILE* inf2 = fopen("taxes.txt", "r");
	fscanf(inf2, "%d", &Q);
	assert((Q) && "Значение переменной Q равно 0");
	return Q;
	fclose(inf2);
}

/**
* \brief Функция для получения всех данных о каждом ресурсе
* \details Функция обращается к файлу taxes.txt, пропускает 1 значение Q и
* собирает всю информацию о ресурсах: наименовании, месячном тарифе за ресурс,
* зарезервированном значении k
* \return Возвращает структуру resi
*/
resource* resourceInput()
{
	int q;
	FILE* inf2 = fopen("taxes.txt", "r");
	fscanf(inf2, "%d", &q);
	for (int i = 0; i < Q; i++)
	{
		fscanf(inf2, "%s", &res1[i].res);
		fscanf(inf2, "%d %d", &res1[i].tarif, &res1[i].k);
	}
	return res1;
	fclose(inf2);
}

