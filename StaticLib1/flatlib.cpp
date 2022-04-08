/**
* \file flatlib.cpp
* \author Чихичин Станислав Сергеевич
* \version 1.0
* \date 10.01.2022
* \brief Файл cpp, который отвечает за чтение файла home.txt
* \details Данный файл содержит функции, которые осуществляют
* ввод данных из файла home.txt
*/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <assert.h>
#include "flat.h"
using namespace std;

/**
* \brief Функция для получения количества квартир в доме
* \details Функция обращается к файлу taxes.txt и собирает 1 значение -
* - количество квартир в доме.
* \exception Имеется исключение для flats - значение не может быть
* равным 0
* \return Возвращает переменную flats
*/
int numberFlatsInput()
{
	FILE* inf1 = fopen("home.txt", "r");
	fscanf(inf1, "%d", &flats);
	assert((flats) && "Значение переменной flats равно 0");
	return flats;
	fclose(inf1);
}

/**
* \brief Функция для получения суммарной площади всех жилых и нежилых помещений
* \details Функция обращается к файлу taxes.txt, пропускает 1 значение flats и
* собирает информацию о суммарной площади всех жилых и нежилых помещений.
* \exception Имеется исключение для s_sum - значение не может быть
* равным 0
* \return Возвращает переменную s_sum
*/
int allSquareInput()
{
	int w;
	FILE* inf1 = fopen("home.txt", "r");
	fscanf(inf1, "%d %d", &w, &s_sum);
	assert((s_sum) && "Значение переменной s_sum равно 0");
	return s_sum;
	fclose(inf1);
}

/**
* \brief Функция для получения информации о площади каждой квартиры и количества жителей в ней
* \details Функция обращается к файлу taxes.txt, пропускает 2 значения flats и s_sum,
* собирает информацию о площади каждой квартиры и количества жителей в ней.
* \exception Имеется 2 исключения для flati[i].sflat - значение не может быть
* равным 0 и flati[i].ncitizen - значение не может быть равным 0
* \return Возвращает структуру flati
*/
flatinf* flatsSquareInput()
{
	int q, e;
	FILE* inf1 = fopen("home.txt", "r");
	fscanf(inf1, "%d %d", &q, &e);
	for (int i = 0; i < flats; i++)
	{
		fscanf(inf1, "%d %d", &flati[i].sflat, &flati[i].ncitizen);
		assert(flati[i].sflat);
		assert(flati[i].ncitizen);
	}
	return flati;
	fclose(inf1);
}

